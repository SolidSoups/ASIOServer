cmake_minimum_required(VERSION 3.16)

project(ASIOServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(
  NetCommon
  NetClient
)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    NetCommon
    NetClient
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    libs/asio-1.30.2/include
)
