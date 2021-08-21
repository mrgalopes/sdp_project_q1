add_library(getopt
    getopt.c
    getopt.h
)

target_compile_definitions(getopt PUBLIC STATIC_GETOPT)
target_include_directories(getopt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
