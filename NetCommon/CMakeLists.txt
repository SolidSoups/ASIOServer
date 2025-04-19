# NetCommon/CMakeLists.txt

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASIO_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../libs/asio-1.30.2/include)

add_library(NetCommon STATIC
  NetCommon.cpp
  net_common.h 
  net_message.h
)



target_include_directories(NetCommon 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ASIO_INCLUDE_PATH}
)
