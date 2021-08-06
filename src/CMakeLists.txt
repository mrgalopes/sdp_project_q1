include_directories(.)

if (MSVC)
    add_compile_options(
        /W3
    )
else()
    add_compile_options(
        -Wall
    )
endif()

add_subdirectory(color_prog)
add_subdirectory(core)
add_subdirectory(tests)
