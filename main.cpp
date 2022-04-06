#include <folly/concurrency/ConcurrentHashMap.h>
#include <folly/concurrency/UnboundedQueue.h>
#include <folly/MPMCQueue.h>
#include <glog/logging.h>

#include <iostream>
#include <string>

// Testing UMPMCQueue inside the ConcurrentHashMap
void testMPMQueue(){
    folly::ConcurrentHashMap<
      std::string,
      std::unique_ptr<folly::UMPMCQueue<std::string, true>>>
      messagesMap;
    messagesMap.insert("testId", std::make_unique<folly::UMPMCQueue<std::string, true>>());
    // Producer
    messagesMap.find("testId")->second->enqueue("value1");
    messagesMap.find("testId")->second->enqueue("value2");
    messagesMap.find("testId")->second->enqueue("value3");
    // Consumer
    std::string response;
    messagesMap.find("testId")->second->dequeue(response);
    LOG(INFO) << "Dequeue: " << response;
}

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  testMPMQueue();
}
