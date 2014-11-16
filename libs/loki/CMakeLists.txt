cmake_minimum_required(VERSION 2.8)
project(loki)

file(GLOB LOKI_SRC src/*.cpp)
file(GLOB LOKI_INCLUDE include/loki/*.h)
#file(GLOB LOKI_INCLUDE include/loki/*.h)

include_directories(libs/loki/include)

add_library(loki STATIC ${LOKI_SRC} ${LOKI_INCLUDE})

INSTALL(FILES ${LOKI_INCLUDE} DESTINATION include/loki)
INSTALL(TARGETS loki DESTINATION install)
