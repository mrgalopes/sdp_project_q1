
find_package(Catch2)
if (NOT Catch2_FOUND)
    message("Catch not found, using submodule")
    add_subdirectory(Catch)
endif()
