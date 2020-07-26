cmake_minimum_required(VERSION 3.10)
project(GraphStore LANGUAGES CXX)
add_executable(graphStoreTest store.cpp lib/JasmineGraphIncrementalStore.cpp lib/NodeBlock.cpp lib/NodeManager.cpp)
add_executable(cppTest cppTesting.cpp)

target_compile_options(graphStoreTest PRIVATE -std=c++11)
message(STATUS "DEBUG enabled")
target_compile_options(graphStoreTest PRIVATE -g)