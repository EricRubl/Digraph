//
// Created by Eric on 02.03.2017.
//

#include "Digraph.hpp"

namespace Graph
{
    Edge::Edge(void) : source(), destination(), cost() {};

    Edge::Edge(int source_c, int destination_c, int cost_c) : source(source_c), destination(destination_c), cost(cost_c) {};

    Edge::Edge(const Edge& other) : source(other.source), destination(other.destination), cost(other.cost) {};


}