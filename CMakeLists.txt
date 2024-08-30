cmake_minimum_required(VERSION 3.28)
project(Dynamic_BackDoor)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(Dynamic_BackDoorServer server.cpp)
add_executable(Dynamic_BackDoorClient client.cpp)

target_link_libraries(Dynamic_BackDoorServer ws2_32)
target_link_libraries(Dynamic_BackDoorClient ws2_32)