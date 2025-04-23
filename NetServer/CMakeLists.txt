cmake_minimum_required(VERSION 3.16)
project(NetServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASIO_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../libs/asio-1.30.2/include)
set(NETCOMMON_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../NetCommon)

# Source files
set(SOURCES
  NetServer.cpp
)

# Create the NetServer library
add_library(NetServer STATIC ${SOURCES})

target_include_directories(NetServer 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${ASIO_INCLUDE_PATH}
    ${NETCOMMON_INCLUDE_PATH}
)

# Link against NetCommon library
target_link_libraries(NetServer PRIVATE NetCommon)

if(WIN32)
  # Add required Windows libraries for ASIO
  target_link_libraries(NetServer PRIVATE ws2_32 wsock32)
endif()

# Create test executable
add_executable(NetServerTest NetServer.cpp)
target_include_directories(NetServerTest 
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ASIO_INCLUDE_PATH}
    ${NETCOMMON_INCLUDE_PATH}
)
target_link_libraries(NetServerTest 
  PRIVATE 
    NetServer
    NetCommon
    ws2_32
    wsock32
)
