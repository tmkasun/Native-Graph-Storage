cmake_minimum_required(VERSION 3.10)
project(GraphStore LANGUAGES CXX)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(graphStoreTest store.cpp lib/internal/JasmineGraphIncrementalStore.cpp lib/internal/PropertyLink.cpp lib/internal/RelationBlock.cpp lib/internal/NodeBlock.cpp lib/internal/NodeManager.cpp)
add_executable(cppTest testing/storeTesting.cpp util/logger/Logger.cpp testing/utils/loader.cpp lib/internal/JasmineGraphIncrementalStore.cpp lib/internal/PropertyLink.cpp lib/internal/RelationBlock.cpp lib/internal/NodeBlock.cpp lib/internal/NodeManager.cpp)
add_executable(workerTesting testing/store_worker.cpp util/logger/Logger.cpp testing/utils/loader.cpp lib/internal/JasmineGraphIncrementalStore.cpp lib/internal/PropertyLink.cpp lib/internal/RelationBlock.cpp lib/internal/NodeBlock.cpp lib/internal/NodeManager.cpp)

target_include_directories(cppTest PUBLIC "lib/external/spdlog-1.8.1/include") # For logging library
target_link_libraries(cppTest Threads::Threads) # For above logging library to run in multi thread mode

target_include_directories(workerTesting PUBLIC "lib/external/spdlog-1.8.1/include") # For logging library
target_link_libraries(workerTesting Threads::Threads) # For above logging library to run in multi thread mode
target_include_directories(workerTesting PUBLIC "lib/external/json-3.9.1/include") # For logging library

target_compile_options(graphStoreTest PRIVATE -std=c++11)
message(STATUS "DEBUG enabled")
target_compile_options(graphStoreTest PRIVATE -g)