cmake_minimum_required(VERSION 3.17)
project(MyLife)

set(CMAKE_CXX_STANDARD 20)

find_package(SqliteOrm CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(CAF REQUIRED COMPONENTS core io)

add_executable(MyLife main.cpp database/database.cpp database/database.h database/tables.h)

target_link_libraries(${PROJECT_NAME} PRIVATE sqlite_orm::sqlite_orm)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_include_directories(${PROJECT_NAME} PRIVATE ${CAF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CAF_LIBRARIES})