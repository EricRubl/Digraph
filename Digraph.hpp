//
// Created by Eric on 02.03.2017.
//

#ifndef DIGRAPH_DIGRAPH_HPP
#define DIGRAPH_DIGRAPH_HPP

#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>

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
    public:
        EdgeSet edges;
        VertexSet vertices;
        Digraph(void); //Constructor
        Digraph(const Digraph&); //Constructor for copying

        void add_edge(Edge e);
        void remove_edge(Edge e);

        int get_vertices(void) const;
        bool is_edge(Vertex a, Vertex b) const;
        InOutDegree get_degree(int vertex) const;
        std::vector::iterator outbound_iterator(int vertex) const;
        std::vector::iterator inbound_edge(int vertex) const;
        int get_cost(Edge e);



    };


}



#endif //DIGRAPH_DIGRAPH_HPP
