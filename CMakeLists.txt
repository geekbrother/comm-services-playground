cmake_minimum_required(VERSION 3.0.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

project(testapp VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(testapp main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

find_package(folly CONFIG REQUIRED)
find_package(amqpcpp CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(unofficial-libuv CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)

target_link_libraries(testapp PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
target_link_libraries(testapp PRIVATE amqpcpp cryptopp-static unofficial::libuv::libuv glog::glog)

find_package(aws-cpp-sdk-core REQUIRED)
find_package(aws-cpp-sdk-dynamodb REQUIRED)
find_package(aws-cpp-sdk-s3 REQUIRED)
target_include_directories(testapp PRIVATE aws-cpp-sdk-core aws-cpp-sdk-dynamodb aws-cpp-sdk-s3)
target_link_libraries(testapp PRIVATE aws-cpp-sdk-core aws-cpp-sdk-dynamodb aws-cpp-sdk-s3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
