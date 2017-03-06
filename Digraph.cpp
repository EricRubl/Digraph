//
// Created by Eric on 02.03.2017.
//

#include "Digraph.hpp"

namespace Graph
{
    Edge::Edge(void) : source(), destination(), cost() {};

    Edge::Edge(int source_c, int destination_c, int cost_c) : source(source_c), destination(destination_c), cost(cost_c) {};

    Edge::Edge(const Edge& other) : source(other.source), destination(other.destination), cost(other.cost) {};

    Edge& Edge::operator=(Edge other)
    {
        if(this != &other)
        {
            std::swap(source, other.source);
            std::swap(destination, other.destination);
            std::swap(cost, other.cost);
        }
        return (*this);
    }

    Edge& Edge::operator=(int new_value)
    {
        cost = new_value;
        return (*this);
    }

    
}