cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(CGProjeto)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the output directory for generated files
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/generated")

file(GLOB UTILS_SOURCES "src/utils/*.cpp")

# Engine specific source files
set(ENGINE_SOURCES
		src/engine/parser.cpp
		src/engine/tinyxml2.cpp
		src/engine/animations.cpp
		include/draw.hpp
		include/ponto.hpp
		include/algebra.hpp
		include/cena.hpp
		include/tinyxml2.h
		include/parser.hpp
		include/animations.hpp


)
# Generator specific source files
set(GENERATOR_SOURCES
		src/generator/plane.cpp
		src/generator/box.cpp
		src/generator/sphere.cpp
		src/generator/cone.cpp
		src/generator/ring.cpp
		src/generator/bezier.cpp
		include/algebra.hpp
		include/draw.hpp
		include/ponto.hpp
)

# Executable for the engine
add_executable(engine src/engine/main.cpp ${ENGINE_SOURCES} ${UTILS_SOURCES})

# Executable for the generator
add_executable(generator src/generator/main.cpp ${GENERATOR_SOURCES} ${UTILS_SOURCES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS} include)
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(DevIL REQUIRED)
link_libraries(${IL_LIBRARIES} )
include_directories(ยง{IL_INCLUDE_DIR})

if(NOT OPENGL_FOUND)
	message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(WIN32)
	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")

	include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
	target_link_libraries(generator ${OPENGL_LIBRARIES}
			${TOOLKITS_FOLDER}/glut/glut32.lib)
	target_link_libraries(engine ${OPENGL_LIBRARIES}
			${TOOLKITS_FOLDER}/glut/glut32.lib)

	if(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll" AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll" AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else(WIN32) # Linux and Mac

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	find_package(GLEW 2.0 REQUIRED)
	include_directories(${GLEW_INCLUDE_DIRS})

	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
	target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
	if(NOT GLUT_FOUND)
		message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)
