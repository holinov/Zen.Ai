cmake_minimum_required(VERSION 2.8)
project(jsoncpp)
#add_definitions( "-Wall" )
#ADD_DEFINITIONS(-DUNICODE)
#ADD_DEFINITIONS(-D_UNICODE)

include_directories(.)

file(GLOB SourceFiles "*.cpp")
file(GLOB HeaderFiles "json/*.h")
add_library(json STATIC ${SourceFiles} ${HeaderFiles})


INSTALL(FILES ${HeaderFiles} DESTINATION include/json)
INSTALL(TARGETS json DESTINATION install)