cmake_minimum_required(VERSION 3.14)
project(bank)

set(CMAKE_CXX_STANDARD 17)

# BankAccount library
add_library(bank_account
     src/bank_account.cpp
)

target_include_directories(bank_account PUBLIC
     ${PROJECT_SOURCE_DIR}/src
)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
   googletest
   URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Tests
enable_testing()

add_executable(test_bank
     tests/test_bank_account.cpp
)
# ... (Keep your existing BankAccount config) ...

# 1. Add LRUCache Test
add_executable(test_lru tests/test_lru.cpp)
target_link_libraries(test_lru gtest_main gtest --coverage)
add_test(NAME LRUCacheTest COMMAND test_lru)

# 2. Add ThreadPool Test
add_executable(test_threadpool tests/test_threadpool.cpp)
# Note: "pthread" is required for threading support
target_link_libraries(test_threadpool gtest_main gtest --coverage pthread)
add_test(NAME ThreadPoolTest COMMAND test_threadpool)

target_link_libraries(test_bank
     bank_account
     gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_bank)
