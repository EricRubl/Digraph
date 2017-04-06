//
// Created by Eric on 02.03.2017.
//

#ifndef DIGRAPH_DIGRAPH_HPP
#define DIGRAPH_DIGRAPH_HPP

#include <set>

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
        //TODO
        Edge& operator+=(int);
        Edge& operator-=(int);
        Edge& operator--(void);
        Edge operator--(int);
        Edge& operator++(void);
        Edge operator++(int);
    };

    //non-member non-friend operators
    //TODO
    bool operator==(Edge, Edge);
    bool operator!=(Edge, Edge);

    /*******************************************************
                         DEFINES
    *******************************************************/

    using EdgeSet = std::set<Edge>;

    /*******************************************************
                         DIGRAPH CLASS
    *******************************************************/
    class Digraph
    {
    public:
        Digraph(void); //Constructor
        Digraph(const Digraph&); //Constructor for copying
    private:
        EdgeSet edges;



    };
}



#endif //DIGRAPH_DIGRAPH_HPP
