project (box123_libbox123video)

include_directories(.)

FILE(GLOB all_source_files "*.cpp")

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
   MESSAGE("OpenGL found.")
else (OPENGL_FOUND)
   MESSAGE("OpenGL missing.")
endif (OPENGL_FOUND)

find_package(SDL REQUIRED)
if (SDL_FOUND)
    MESSAGE("SDL found.")
else (SDL_FOUND)
    MESSAGE("SDL missing.")
endif (SDL_FOUND)

add_library(libbox123video_static STATIC ${all_source_files})
add_library(libbox123video_shared SHARED ${all_source_files})

target_link_libraries(libbox123video_static ${OPENGL_LIBRARIES})
target_link_libraries(libbox123video_shared ${OPENGL_LIBRARIES})

target_link_libraries(libbox123video_static ${SDL_LIBRARY})
target_link_libraries(libbox123video_shared ${SDL_LIBRARY})
