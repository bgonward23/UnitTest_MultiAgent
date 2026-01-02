cmake_minimum_required(VERSION 3.10)
project(MultiAgentUnitTest)

# Standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 1. STANDARD COVERAGE FLAGS
# ==========================================
# Using -O0 (Standard Debug) to match Copilot/GPT-4o runs.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# ==========================================
# 2. GOOGLETEST DEPENDENCY
# ==========================================
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ==========================================
# 3. SOURCE FILES
# ==========================================
include_directories(src)
add_library(bank_account src/bank_account.cpp)

# ==========================================
# 4. QWEN TARGETS (The Only Ones Active)
# ==========================================

# Bank Account (Qwen)
add_executable(test_bank_qwen tests/test_bank_account_3agent_qwen.cpp)
target_link_libraries(test_bank_qwen PRIVATE bank_account gtest_main)
gtest_discover_tests(test_bank_qwen)

# LRU Cache (Qwen)
add_executable(test_lru_qwen tests/test_lru_3agent_qwen.cpp)
target_include_directories(test_lru_qwen PRIVATE src)
target_link_libraries(test_lru_qwen PRIVATE gtest_main gtest)
gtest_discover_tests(test_lru_qwen)

# Thread Pool (Qwen)
add_executable(test_threadpool_qwen tests/test_threadpool_3agent_qwen.cpp)
target_include_directories(test_threadpool_qwen PRIVATE src)
target_link_libraries(test_threadpool_qwen PRIVATE gtest_main gtest pthread)
gtest_discover_tests(test_threadpool_qwen)
