#include <iostream>
#include "Digraph.hpp"
#include <windows.h>

int main()
{
    auto test_graph = Graph::Digraph();

    try
    {
        test_graph.read_graph_from_file(".\\graf.txt");
        std::cout << test_graph.get_vertices() << '\n';
        test_graph.remove_edge(0, 0);
        if(test_graph.is_edge(0, 0))
            std::cout << "Este" << '\n';
        test_graph.add_edge(0, 0, 1);
        if(test_graph.is_edge(0, 0))
            std::cout << "Este" << '\n';

        auto deg = test_graph.get_degree(3);
        std::cout << deg.first << " " << deg.second << '\n';

    }
    catch (const char* ex)
    {
        std::cout << ex;
    }

    system("pause");
    return 0;
}