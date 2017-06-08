#include <iostream>
#include "include/DirectedGraph.hpp"
#include "include/UndirectedGraph.hpp"
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

        Graph::InOutDegree deg = test_graph.get_degree(0);
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

    ////////////////////////////////////////////////////////////////////////////////
    //                                LAB 2                                       //
    ////////////////////////////////////////////////////////////////////////////////

    std::cout << "\n\n\nLAB 2\n\n\n";


    Graph::UndirectedGraph<int, int, int> test_graph_bfs;

    try
    {
        test_graph_bfs.read_from_file("..\\grafn.txt");
    }
    catch(const char* ex)
    {
        std::cout << ex;
    }

    std::vector<bool> fr(test_graph_bfs.get_vertices_size());

    int ctr = 0;
    for(auto it = test_graph_bfs.get_vertices_begin(); it not_eq test_graph_bfs.get_vertices_end(); ++it)
    {
        if ( !fr[it->first] )
        {
            auto a = test_graph_bfs.BFS(it->first);
            std::cout << "\nGroup " << ctr << ":\n";
            for (int i = 0; i < a.size(); ++i)
            {
                std::cout << a[i] << ' ';
                fr[a[i]] = true;
            }
            std::cout << '\n';
        }
        ctr++;
    }

    std::cout << test_graph_bfs.Djikstra(0, 4) << '\n'; // adaugat newline


    auto mst = test_graph_bfs.minimumSpanningTree();

    auto ham = test_graph_bfs.Hamiltonian();

    char c;
    std::cin >> c;

    return 0;
}