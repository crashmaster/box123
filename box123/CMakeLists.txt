project (box123_executable)

include_directories (${box123_executable_SOURCE_DIR})
include_directories (${box123_include_internal_SOURCE_DIR})
include_directories (${box123_include_external_SOURCE_DIR})
include_directories (${box123_libbox123logger_SOURCE_DIR})
include_directories (${box123_libbox123video_SOURCE_DIR})
include_directories (${box123_libbox123eventlogic_SOURCE_DIR})

FILE(GLOB all_source_files "*.cpp")

add_executable(box123 ${all_source_files})

target_link_libraries(box123 libbox123logger_shared)
target_link_libraries(box123 libbox123eventlogic_shared)
target_link_libraries(box123 ${OPENGL_LIBRARIES})
target_link_libraries(box123 ${SDL_LIBRARY})
