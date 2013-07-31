cmake_minimum_required (VERSION 2.8)

#MESSAGE("${CMAKE_BUILD_TYPE}")
#IF(DEFINED CMAKE_BUILD_TYPE)
#    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
#    build, options are: Debug Release RelWithDebInfo.")
#    MESSAGE("IF: ${CMAKE_BUILD_TYPE}")
#ELSE()
#    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build,
#    options are: Debug Release RelWithDebInfo.")
#    MESSAGE("ELSE: ${CMAKE_BUILD_TYPE}")
#ENDIF()

project (box123)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/lib)

add_subdirectory(include)
add_subdirectory(libbox123logger)
add_subdirectory(libbox123video)
add_subdirectory(box123)
add_subdirectory(unit_test)
