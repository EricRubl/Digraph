//
// Created by Eric on 02.03.2017.
//

#ifndef DIGRAPH_DIGRAPH_HPP
#define DIGRAPH_DIGRAPH_HPP

#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>
#include <string>
#include <fstream>

namespace Graph
{
    /*******************************************************
                       EDGE CLASS
     *******************************************************/
    struct Edge
    {
        int source;
        int destination;
        int cost;

        Edge(void);
        Edge(const Edge&);
        Edge(int, int, int);
        Edge& operator=(int);
        Edge& operator=(Edge);

        Edge& operator+=(int);
        Edge& operator-=(int);
        Edge& operator--(void);
        Edge operator--(int);
        Edge& operator++(void);
        Edge operator++(int);
    };

    struct Vertex
    {
    public:
        std::vector<int> in;
        std::vector<int> out;

        Vertex(void);
        Vertex(const Vertex&);
    };

    //non-member non-friend operators
    bool operator==(Edge, Edge);
    bool operator!=(Edge, Edge);

    /*******************************************************
                         DEFINES
    *******************************************************/

    using EdgeSet = std::vector<Edge>;
    using VertexSet = std::vector<Vertex>;
    using InOutDegree = std::pair<int, int>;

    /*******************************************************
                         DIGRAPH CLASS
    *******************************************************/
    class Digraph
    {
    private:
        int vertex_count;
        int edge_count;
        EdgeSet edges;
        VertexSet vertices;
        void generate_vertices();
    public:
        Digraph(void); //Constructor
        Digraph(const Digraph&); //Constructor for copying
        inline virtual ~Digraph() {};

        void read_graph_from_file(std::string filename);
        void add_edge(int source, int destination, int cost);
        void remove_edge(int source, int destination);
        int get_vertices(void) const;
        bool is_edge(int source, int destination) const;
        InOutDegree get_degree(int vertex) const;
        std::vector<int>::iterator outbound_iterator(int vertex) const;
        std::vector<int>::iterator inbound_iterator(int vertex) const;
        Edge& get_cost(Edge e);
    };


}



#endif //DIGRAPH_DIGRAPH_HPP
