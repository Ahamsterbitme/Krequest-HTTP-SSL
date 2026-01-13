cmake_minimum_required(VERSION 3.24)
project(AsioLearning CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(krequest_app
  ../src/method/method_model.h
  ../src/request/Krequest_request.h
  ../src/Krequest.h
  ../test/main.cpp
)

target_include_directories(
    krequest_app PRIVATE
    &{Boost_INCLUDE_DIRS}
)
target_link_libraries(krequest_app PRIVATE
    boost_filesystem
    boost_thread
    boost_regex
    ssl
    crypto
    pthread
)