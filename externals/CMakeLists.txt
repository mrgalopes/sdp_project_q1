
find_package(Catch2 3 QUIET)
if (NOT Catch2_FOUND)
    message("Catch not found, using submodule")
    add_subdirectory(Catch)
endif()

# getopt
if (MSVC)
    add_subdirectory(getopt)
endif()
