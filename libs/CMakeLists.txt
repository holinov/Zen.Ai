cmake_minimum_required(VERSION 2.8)
add_subdirectory(loki)
add_subdirectory(json)

IF(WIN32)
	MESSAGE(STATUS "Not making libuuid")
ELSE()
	add_subdirectory(libuuid)
ENDIF()

#add_subdirectory(mongoose)
#add_subdirectory(sha1)

if(MAKE_TESTS)
	add_subdirectory(gtest)
endif()

#Возможно стоит собирать только если не найдена системная
IF(MAKE_ZLIB)
	add_subdirectory(zlib)
ENDIF()


#SET_PROPERTY(TARGET zlib PROPERTY FOLDER "Libs/zlib")
#SET_PROPERTY(TARGET zlibstatic PROPERTY FOLDER "Libs/zlib")
#SET_PROPERTY(TARGET zlibstatic PROPERTY FOLDER "Libs/zlib")
#SET_PROPERTY(TARGET minigzip PROPERTY FOLDER "Libs/zlib")
#SET_PROPERTY(TARGET example PROPERTY FOLDER "Libs/zlib")

#SET_PROPERTY(TARGET mongoose PROPERTY FOLDER "Libs")
#SET_PROPERTY(TARGET my_sha1 PROPERTY FOLDER "Libs")
#SET_PROPERTY(TARGET json PROPERTY FOLDER "Libs")
#SET_PROPERTY(TARGET loki PROPERTY FOLDER "Libs")
#SET_PROPERTY(TARGET gtest PROPERTY FOLDER "Libs/gtest")
#SET_PROPERTY(TARGET gtest_main PROPERTY FOLDER "Libs/gtest")