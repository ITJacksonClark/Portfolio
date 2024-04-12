cmake_minimum_required(VERSION 3.28)

project(lec04_ex)

LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/lib )
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/bin )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# For multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

find_package(OpenGL REQUIRED )
if (OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OpenGL_LIBRARIES})
endif()	

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
	include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
	link_libraries(${GLUT_LIBRARY})
endif()

set(COMMON_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
set(COMMON_LIBS ${COMMON_LIBS} ${EXTRA_LIBS})

SET(APP_SRCS1
  source/lec04_ex1.cpp
)

SET(APP_SRCS2
  source/lec04_ex2.cpp
)



SET(APP_HDRS
#	include/hearder.h
)

add_executable(lec04_ex1  ${APP_SRCS1} ${APP_HDRS})
add_executable(lec04_ex2  ${APP_SRCS2} ${APP_HDRS})


target_link_libraries(lec04_ex1 ${COMMON_LIBS})
target_link_libraries(lec04_ex2 ${COMMON_LIBS})


ADD_CUSTOM_TARGET(debug ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${project_binary_dir})
ADD_CUSTOM_TARGET(release ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${project_binary_dir})






