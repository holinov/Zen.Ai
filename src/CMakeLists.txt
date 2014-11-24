cmake_minimum_required(VERSION 2.8)
project(ZenAiCore)

file(GLOB SourceFiles "*.cpp" "*.h" "*.h")
file(GLOB MainFile "main.cpp")

add_executable(zenai ${SourceFiles})
target_link_libraries(zenai json loki ${GUID_LIB} ${GCC_LIBS})


#Передать наверх для прповерки
SET(TARGETS_TO_CHECK "zenai ${TARGETS_TO_CHECK}" PARENT_SCOPE)
SET(cpppropgen_exc "" PARENT_SCOPE)
SET(cpppropgen_inc ${SourceFiles} PARENT_SCOPE)
INSTALL(TARGETS zenai DESTINATION bin)


#Сборка билиотеки для тестов
if(MAKE_TESTS)
	#Убрать файл с void main()
	list(REMOVE_ITEM SourceFiles ${MainFile})

	#Собрать билиотеку
	add_library(zenai_lib STATIC ${SourceFiles})
	target_link_libraries(zenai_lib json loki ${GUID_LIB} ${GCC_LIBS})
endif()

