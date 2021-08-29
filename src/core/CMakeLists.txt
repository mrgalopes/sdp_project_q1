
add_library(core STATIC
        Vertex.cpp
        Vertex.h
        coloring_algorithms/ColoringStrategy.h
        coloring_algorithms/BasicColoringAlgorithm.cpp
        coloring_algorithms/BasicColoringAlgorithm.h
        Graph.cpp
        Graph.h
        io/IOMethods.cpp
        io/IOMethods.h
        coloring_algorithms/LubyColoringAlgorithm.cpp
        coloring_algorithms/LubyColoringAlgorithm.h
        coloring_algorithms/JonesPlassmannAlgorithm.cpp coloring_algorithms/JonesPlassmannAlgorithm.h coloring_algorithms/LargestDegreeFirstAlgorithm.cpp coloring_algorithms/LargestDegreeFirstAlgorithm.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(core PRIVATE Threads::Threads)
