cmake_minimum_required(VERSION 2.8)
project(ZenAiCore)

file(GLOB SourceFiles "*.cpp" "*.h" "*.hpp")
add_executable(zenai ${SourceFiles})

#Передать наверх для прповерки
SET(TARGETS_TO_CHECK "zenai ${TARGETS_TO_CHECK}" PARENT_SCOPE)
SET(cpppropgen_exc "" PARENT_SCOPE)
SET(cpppropgen_inc ${SourceFiles} PARENT_SCOPE)

target_link_libraries(zenai json loki ${GUID_LIB} ${GCC_LIBS})


INSTALL(TARGETS zenai DESTINATION bin)

