cmake_minimum_required(VERSION 3.17)
project(MyLife)

set(CMAKE_CXX_STANDARD 20)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_definitions(-DBOOST_UUID_FORCE_AUTO_LINK)

option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

find_package(SqliteOrm CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(CAF REQUIRED COMPONENTS core io)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(date CONFIG REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE TEST_SRC_LIST "test/*.cpp")
file(GLOB_RECURSE GTD_SRC_LIST "GTD_Service/*.cpp")
add_executable(MyLife main.cpp ${GTD_SRC_LIST} ${TEST_SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE sqlite_orm::sqlite_orm)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_include_directories(${PROJECT_NAME} PRIVATE ${CAF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CAF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CAF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} PRIVATE date::date date::date-tz)


add_test(Test MyLifeTests)
enable_testing()