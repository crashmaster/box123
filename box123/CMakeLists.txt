project (box123_executable)

include_directories (${box123_include_SOURCE_DIR})

FILE(GLOB all_source_files "*.cpp")

add_executable(box123 ${all_source_files})

target_link_libraries(box123 libbox123logger_shared)
target_link_libraries(box123 libbox123eventlogic_shared)
target_link_libraries(box123 ${OPENGL_LIBRARIES})
target_link_libraries(box123 ${SDL2_LIBRARY})
