cmake_minimum_required(VERSION 3.6)
project(Digraph)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp include/Edge.hpp include/Vertex.hpp include/Graph.hpp include/DirectedGraph.hpp include/UndirectedGraph.hpp)
add_executable(Digraph ${SOURCE_FILES})