#include <iostream>
#include "include/DirectedGraph.hpp"
#include <windows.h>

int main()
{
    Graph::DirectedGraph<int, int, int> test_graph;

    try
    {
        test_graph.read_from_file("..\\graf.txt");
        std::cout << "Number of vertices: " << test_graph.get_vertices_count() << '\n';
        test_graph.remove_edge(0, 0);
        std::cout << "\nRemoving edge from 0 to 0!\n";
        if(test_graph.is_edge(0, 0))
            std::cout << "\nEdge (0, 0) exists!\n";
        test_graph.add_edge(0, 0, 1);
        std::cout << "\nAdding edge from 0 to 0 with cost 1!\n";
        if(test_graph.is_edge(0, 0))
            std::cout << "\nEdge (0, 0) exists!\n";

        Graph::InOutDegree deg = test_graph.get_de gree(0);
        std::cout << "\nIn degree of vertex 0: " << deg.first << " | Out degree of vertex 0: " << deg.second;
        std::cout << std::endl << "\nIs edge from 4 to 0: " << test_graph.is_edge(4, 0) << " | Is edge from 0 to 1: " << test_graph.is_edge(0,1) << '\n';
        std::cout << "\nCost of edge from 1 to 3: " << test_graph.get_edge_cost(1, 3) << '\n';
        test_graph.change_cost(1, 3, 69);
        std::cout << "\nChanging cost of (1, 3) to 69\n";
        std::cout <<  "\nCost of edge from 1 to 3: " << test_graph.get_edge_cost(1, 3) << '\n';
    }
    catch (const char* ex)
    {
        std::cout << ex;
    }

    char c;
    std::cin >> c;

    return 0;
}