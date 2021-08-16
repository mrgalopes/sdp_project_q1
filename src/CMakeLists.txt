include_directories(.)

set_property(DIRECTORY APPEND PROPERTY
    COMPILE_DEFINITIONS $<$<CONFIG:Debug>:_DEBUG> $<$<NOT:$<CONFIG:Debug>>:NDEBUG>)

if (MSVC)
    set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "" FORCE)

    add_compile_options(
        /W3
        /MP
    )
    if (NOT USE_CCACHE)
        add_compile_options(
            /Zi
            /Zo
        )
    endif()
else()
    add_compile_options(
        -Wall
    )
endif()

add_subdirectory(color_prog)
add_subdirectory(core)
add_subdirectory(tests)
