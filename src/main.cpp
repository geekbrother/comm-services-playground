#include <iostream>
#include <string>
#include <glog/logging.h>

#include <folly/concurrency/ConcurrentHashMap.h>
#include <folly/concurrency/UnboundedQueue.h>
#include <folly/MPMCQueue.h>

#include <grpcpp/grpcpp.h>

#include "protos/helloworld.grpc.pb.h"
#include "protos/helloworld.pb.h"

class GreeterServiceImpl final : public helloworld::Greeter::Service
{
  grpc::Status SayHello(grpc::ServerContext *context, const helloworld::HelloRequest *request,
                        helloworld::HelloReply *reply) override
  {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return grpc::Status::OK;
  }
};

// Testing gRPC simple server
void testGrpcServer()
{
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
};

// Testing UMPMCQueue inside the ConcurrentHashMap
void testMPMQueue()
{
  folly::ConcurrentHashMap<
      std::string,
      std::unique_ptr<folly::UMPMCQueue<std::string, true>>>
      messagesMap;
  messagesMap.insert("testId", std::make_unique<folly::UMPMCQueue<std::string, true>>());
  // Producer
  folly::UMPMCQueue<std::string, true> *b = messagesMap.find("testId")->second.get();
  b->enqueue("value1");
  messagesMap.find("testId")->second->enqueue("value2");
  // Consumer
  std::string response;
  messagesMap.find("testId")->second->dequeue(response);
  LOG(INFO) << "Dequeue 1: " << response;
  b->dequeue(response);
  LOG(INFO) << "Dequeue 2 from b: " << response;
};

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  testMPMQueue();
  testGrpcServer();
};
