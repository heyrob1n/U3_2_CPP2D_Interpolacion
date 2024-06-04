cmake_minimum_required(VERSION 3.16)
project(Shooter2D LANGUAGES CXX)

#folder raiz del projecto
add_compile_definitions(ROOT_FOLDER="${CMAKE_SOURCE_DIR}")


set(SRC ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_HPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		"${SRC}/*.hpp*" "${SRC}/*.h*")
file(GLOB_RECURSE SRC_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		"${SRC}/*.cpp*")


#folder de donde se ejecuta el bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

#set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -DMI_DEBUG)
add_compile_definitions("DEBUG=$<CONFIG:Debug>")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#buscar la libreria sfml
#WINDOWS
if(MSVC)
	include(FetchContent)
	FetchContent_Declare(SFML
			GIT_REPOSITORY https://github.com/SFML/SFML.git
			GIT_TAG 2.6.x)
	FetchContent_MakeAvailable(SFML)
else() #linux & mac
	find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
	include_directories(${SFML_INCLUDE_DIRS})
endif()  


add_executable(${PROJECT_NAME}  ${SRC_CPP} ${SRC_HPP})

target_include_directories(
		${PROJECT_NAME}
		PUBLIC ${SRC}
)

#link librerias
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
#dadd_compile_options(/Oy)

#windows copiar los dll
if(MSVC)
	add_custom_command(
			TARGET ${PROJECT_NAME}
			COMMENT "Copy OpenAL DLL"
			PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
			VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
