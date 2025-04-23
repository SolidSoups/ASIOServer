# NetCommon/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASIO_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../libs/asio-1.30.2/include)

add_library(NetCommon STATIC
  NetCommon.cpp
  net_common.h 
  net_message.h
  net_tsqueue.h
  net_server.h
  net_connection.h
  olc_net.h
)

target_include_directories(NetCommon 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ASIO_INCLUDE_PATH}
)

# Configure ASIO
target_compile_definitions(NetCommon 
  PUBLIC 
    ASIO_STANDALONE
    # _WIN32_WINNT=0x0A00  # Windows 10
)

if(WIN32)
  target_link_libraries(NetCommon PUBLIC ws2_32 wsock32)
endif()
