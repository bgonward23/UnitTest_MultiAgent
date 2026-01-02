cmake_minimum_required(VERSION 3.10)
project(MultiAgentUnitTest)

# Standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage Flags (Optimized to merge templates back to ~87 lines)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O1 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O1 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Dependencies
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

include_directories(src)
add_library(bank_account src/bank_account.cpp)

# ==========================================
# DEFINING THE SWITCHES
# ==========================================
option(BUILD_COPILOT "Build Copilot Baseline Tests" OFF)
option(BUILD_GPT4O   "Build GPT-4o Agent Tests"   OFF)
option(BUILD_QWEN    "Build Qwen Agent Tests"     OFF)

# ==========================================
# 1. COPILOT (Baseline)
# ==========================================
if(BUILD_COPILOT)
    message(STATUS "🏗️  BUILDING TARGET: COPILOT BASELINE")
    add_executable(test_bank tests/test_bank_account.cpp)
    target_link_libraries(test_bank PRIVATE bank_account gtest_main)
    gtest_discover_tests(test_bank)

    add_executable(test_lru tests/test_lru.cpp)
    target_include_directories(test_lru PRIVATE src)
    target_link_libraries(test_lru PRIVATE gtest_main gtest)
    gtest_discover_tests(test_lru)

    add_executable(test_threadpool tests/test_threadpool.cpp)
    target_include_directories(test_threadpool PRIVATE src)
    target_link_libraries(test_threadpool PRIVATE gtest_main gtest pthread)
    gtest_discover_tests(test_threadpool)
endif()

# ==========================================
# 2. GPT-4o (3-Agent)
# ==========================================
if(BUILD_GPT4O)
    message(STATUS "🏗️  BUILDING TARGET: GPT-4o AGENTS")
    add_executable(test_bank_3agent tests/test_bank_account_3agent_gpt4o.cpp)
    target_link_libraries(test_bank_3agent PRIVATE bank_account gtest_main)
    gtest_discover_tests(test_bank_3agent)

    add_executable(test_lru_3agent tests/test_lru_3agent_gpt4o.cpp)
    target_include_directories(test_lru_3agent PRIVATE src)
    target_link_libraries(test_lru_3agent PRIVATE gtest_main gtest)
    gtest_discover_tests(test_lru_3agent)

    add_executable(test_threadpool_3agent tests/test_threadpool_3agent_gpt4o.cpp)
    target_include_directories(test_threadpool_3agent PRIVATE src)
    target_link_libraries(test_threadpool_3agent PRIVATE gtest_main gtest pthread)
    gtest_discover_tests(test_threadpool_3agent)
endif()

# ==========================================
# 3. QWEN (3-Agent)
# ==========================================
if(BUILD_QWEN)
    message(STATUS "🏗️  BUILDING TARGET: QWEN AGENTS")
    add_executable(test_bank_qwen tests/test_bank_account_3agent_qwen.cpp)
    target_link_libraries(test_bank_qwen PRIVATE bank_account gtest_main)
    gtest_discover_tests(test_bank_qwen)

    add_executable(test_lru_qwen tests/test_lru_3agent_qwen.cpp)
    target_include_directories(test_lru_qwen PRIVATE src)
    target_link_libraries(test_lru_qwen PRIVATE gtest_main gtest)
    gtest_discover_tests(test_lru_qwen)

    add_executable(test_threadpool_qwen tests/test_threadpool_3agent_qwen.cpp)
    target_include_directories(test_threadpool_qwen PRIVATE src)
    target_link_libraries(test_threadpool_qwen PRIVATE gtest_main gtest pthread)
    gtest_discover_tests(test_threadpool_qwen)
endif()
