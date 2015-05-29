project (box123_libbox123eventlogic)

include_directories(.)
include_directories (${box123_include_SOURCE_DIR})

FILE(GLOB all_source_files "*.cpp")

add_library(libbox123eventlogic_static STATIC ${all_source_files})
add_library(libbox123eventlogic_shared SHARED ${all_source_files})

target_link_libraries(libbox123eventlogic_static ${SDL2_LIBRARY})
target_link_libraries(libbox123eventlogic_shared ${SDL2_LIBRARY})
