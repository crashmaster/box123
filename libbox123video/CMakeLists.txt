project (box123_libbox123video)

include_directories(.)

FILE(GLOB all_source_files "*.cpp")

add_library(libbox123video_static STATIC ${all_source_files})
add_library(libbox123video_shared SHARED ${all_source_files})

target_link_libraries(libbox123video_static ${OPENGL_LIBRARIES})
target_link_libraries(libbox123video_shared ${OPENGL_LIBRARIES})

target_link_libraries(libbox123video_static ${SDL_LIBRARY})
target_link_libraries(libbox123video_shared ${SDL_LIBRARY})
