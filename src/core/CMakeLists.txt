
add_library(core STATIC
        Vertex.cpp
        Vertex.h
        ColoringStrategy.h
        BasicColoringAlgorithm.cpp
        BasicColoringAlgorithm.h
        Graph.cpp
        Graph.h
        IOMethods.cpp
        IOMethods.h
        LubyColoringAlgorithm.cpp
        LubyColoringAlgorithm.h
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(core PRIVATE Threads::Threads)
