# NetCommon/CMakeLists.txt

add_library(NetCommon STATIC
  NetCommon.cpp
  net_common.h 
  net_message.h
)

target_include_directories(NetCommon 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
