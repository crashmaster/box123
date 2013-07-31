project (box123_libbox123logger)

include_directories(.)

FILE(GLOB all_source_files "*.cpp")

add_library(libbox123logger_static STATIC ${all_source_files})

add_library(libbox123logger_shared SHARED ${all_source_files})
