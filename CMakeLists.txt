cmake_minimum_required(VERSION 3.20)
project(sdp_project_q1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>)

configure_file(${PROJECT_SOURCE_DIR}/dist/graphs/rgg_n_2_15_s0.graph
               ${PROJECT_BINARY_DIR}/dist/graphs/rgg_n_2_15_s0.graph
               COPYONLY)

enable_testing()

add_subdirectory(src)

add_subdirectory(externals)

