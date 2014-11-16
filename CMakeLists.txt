cmake_minimum_required(VERSION 2.8)
project(zenai)

#Общие настройки проекта
#option (MAKE_ZLIB "Use custom ZLib sources" ON) 
option (MAKE_TESTS "Make test projects" ON)
option (MAKE_FOR_IOS "Bild library for IOS" OFF)

#Включаем группирование проектов
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

add_definitions(-DHAVE_USLEEP)

IF(MAKE_FOR_IOS)
	add_definitions(-DIOS_BUILD)
	set(MAKE_TESTS OFF FORCE CACHE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
ELSE()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

#Подключение dirent для WIN32
SET(MORE_INCLUDES "")
IF(WIN32)
	message(STATUS "Making for WIN")
	add_definitions(-DWIN -D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN)
	SET(MORE_INCLUDES libs/dirent)
ENDIF()

IF(APPLE)
	message(STATUS "Making for MAC OS X")
	add_definitions(-DMAC_OS_X)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-cxa-atexit -pthread -fPIC")
	SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fuse-cxa-atexit -ldl -fPIC" )
	add_definitions(-DC_GCC -DLINUX)
ENDIF()

#Версия RDC_CORE
#set(RDC_LIBVERSION "1.0.0")

#подключение zlib
SET(ZLIB_INCLUDES "")
#IF(MAKE_ZLIB)
#	message(STATUS "Making zlib from sources")
#	set(ZLIB_INCLUDES libs/zlib ${CMAKE_CURRENT_BINARY_DIR}/libs/zlib)
#ENDIF()

include_directories(
	src/include
	libs/loki/include 
	libs/json 
	libs/libuuid 
	libs/mongoose 
	libs/sha1
	libs/gtest
	libs/gtest/include
	${ZLIB_INCLUDES}
	${MORE_INCLUDES})

add_subdirectory(libs)
add_subdirectory(src)

################################################
##	создание make uninstall
################################################

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

################################################
##	Сборка тестов
################################################
if(MAKE_TESTS)
	message(STATUS "Making unit tests")

	file(GLOB TEST_SOURCES "src/tests/unit_tests/*.cpp")
	foreach(TEST_FILE ${TEST_SOURCES})
	  get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
	  message(STATUS "Processing file: ${TEST_FILE_NAME}.cpp")

	  add_executable(${TEST_FILE_NAME} ${TEST_FILE})
	  set(TLB "")
	  if(WIN32)
	  	set(TLB WS2_32.lib)
	  endif()
	  target_link_libraries(${TEST_FILE_NAME} rdc gtest gtest_main ${TLB})

	  #Кладем проект в папку решения
	  SET_PROPERTY(TARGET ${TEST_FILE_NAME} PROPERTY FOLDER "Tests/UnitTests")
	endforeach()
ENDIF()
