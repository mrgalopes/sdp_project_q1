
add_executable(color_prog
        main.cpp
)
target_link_libraries(color_prog PRIVATE core)

if (MSVC)
    target_link_libraries(color_prog PRIVATE getopt)
endif()
