project (box123_unit_test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${box123_SOURCE_DIR}/build_output/${CMAKE_BUILD_TYPE}/unit_test)

include_directories (${box123_include_SOURCE_DIR})

FILE(GLOB all_source_files "*.cpp")

add_executable(box123_unit_test ${all_source_files})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

target_link_libraries(box123_unit_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
