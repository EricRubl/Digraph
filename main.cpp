#include <iostream>
#include "include/DirectedGraph.hpp"
#include <windows.h>

int main()
{
    Graph::DirectedGraph<int, int, int> test_graph;

    try
    {
        test_graph.read_from_file(".\\graf.txt");
        std::cout << test_graph.get_vertices_count() << '\n';
        test_graph.remove_edge(0, 0);
        if(test_graph.is_edge(0, 0))
            std::cout << "Este1" << '\n';
        test_graph.add_edge(0, 0, 1);
        if(test_graph.is_edge(0, 0))
            std::cout << "Este2" << '\n';

        Graph::InOutDegree deg = test_graph.get_degree(0);
        std::cout << (int)deg.first << " " << (int)deg.second;
        std::cout << std::endl << test_graph.is_edge(4, 0) << " " << test_graph.is_edge(0,1) << '\n' << test_graph.get_edge_cost(1, 3);
        test_graph.change_cost(1, 3, 69);
        std::cout <<  " " << test_graph.get_edge_cost(1, 3);

    }
    catch (const char* ex)
    {
        std::cout << ex;
    }

    char c;
    std::cin >> c;

    return 0;
}