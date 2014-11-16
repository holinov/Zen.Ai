cmake_minimum_required(VERSION 2.8)
project(testconsole)
add_definitions( "-Wall -g" )

set(SOURCES main.cpp)


include_directories(rdc)
add_executable(console ${SOURCES})
add_subdirectory(rdc)

target_link_libraries(console rdc)

add_executable(t1 test1.cpp)