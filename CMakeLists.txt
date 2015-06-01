cmake_minimum_required (VERSION 2.8)

project (box123)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
   MESSAGE("OpenGL found.")
else (OPENGL_FOUND)
   MESSAGE("OpenGL missing.")
endif (OPENGL_FOUND)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SDL2 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/lib)

add_subdirectory(include)
add_subdirectory(libbox123logger)
add_subdirectory(libbox123eventlogic)
add_subdirectory(box123)
add_subdirectory(unit_test)
