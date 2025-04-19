cmake_minimum_required(VERSION 3.16)
project(NetClient)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include NetCommon from relative path
set(ASIO_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../libs/asio-1.30.2/include)
add_subdirectory(../NetCommon ${CMAKE_CURRENT_BINARY_DIR}/NetCommonBuild)

# Source files
set(SOURCES
  SimpleClient.cpp
)

# Static library for NetClient
add_library(NetClient STATIC ${SOURCES})

target_include_directories(NetClient 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${ASIO_INCLUDE_PATH}
)

target_link_libraries(NetClient
  PUBLIC NetCommon
)

# Executable for testing NetClient on its own
add_executable(NetClientTest SimpleClient.cpp)

target_link_libraries(NetClientTest
  PRIVATE NetClient
)
