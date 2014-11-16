cmake_minimum_required(VERSION 2.8)
project(uuid)
#add_definitions( "-Wall" )
#ADD_DEFINITIONS(-DUNICODE)
#ADD_DEFINITIONS(-D_UNICODE)

include_directories(.)

file(GLOB SourceFiles "*.c")
file(GLOB HeaderFiles "*.h")

if(WIN32)
	LIST(REMOVE_ITEM HeaderFiles "${CMAKE_CURRENT_SOURCE_DIR}/all-io.h" "${CMAKE_CURRENT_SOURCE_DIR}/c.h" "${CMAKE_CURRENT_SOURCE_DIR}/randutils.h")
	LIST(REMOVE_ITEM SourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/randutils.c")

	MESSAGE(STATUS "Sources:")
	foreach(FILE ${SourceFiles})
	  MESSAGE(STATUS "File: ${FILE} ")
	endforeach()

	MESSAGE(STATUS "Headers:")
	foreach(FILE ${HeaderFiles})
	  MESSAGE(STATUS "File: ${FILE} ")
	endforeach()
endif()

add_library(myuuid STATIC ${SourceFiles} ${HeaderFiles})


INSTALL(FILES ${HeaderFiles} DESTINATION include)
INSTALL(TARGETS myuuid DESTINATION install)