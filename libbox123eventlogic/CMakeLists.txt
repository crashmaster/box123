project (box123_libbox123eventlogic)

include_directories(.)

FILE(GLOB all_source_files "*.cpp")

find_package(SDL REQUIRED)
if (SDL_FOUND)
    MESSAGE("SDL found.")
else (SDL_FOUND)
    MESSAGE("SDL missing.")
endif (SDL_FOUND)

add_library(libbox123eventlogic_static STATIC ${all_source_files})
add_library(libbox123eventlogic_shared SHARED ${all_source_files})

target_link_libraries(libbox123eventlogic_static ${SDL_LIBRARY})
target_link_libraries(libbox123eventlogic_shared ${SDL_LIBRARY})
