cmake_minimum_required(VERSION 3.16)

project(ASIOServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add subdirectories
add_subdirectory(NetCommon)
add_subdirectory(NetClient)
add_subdirectory(NetServer)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE
    ws2_32
    NetCommon
    NetClient
    NetServer
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    NetCommon
    NetClient
    NetServer
    libs/asio-1.30.2/include
)
