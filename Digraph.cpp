//
// Created by Eric on 02.03.2017.
//

#include "Digraph.hpp"

namespace Graph {
    Edge::Edge(void) : source(), destination(), cost() {}

    Edge::Edge(int source_c, int destination_c, int cost_c) : source(source_c), destination(destination_c),
                                                              cost(cost_c) {}

    Edge::Edge(const Edge &other) : source(other.source), destination(other.destination), cost(other.cost) {}

    Edge &Edge::operator=(Edge other)
    {
        if (this != &other) {
            std::swap(source, other.source);
            std::swap(destination, other.destination);
            std::swap(cost, other.cost);
        }
        return (*this);
    }

    Edge &Edge::operator=(int new_value)
    {
        cost = new_value;
        return (*this);
    }

    Edge &Edge::operator++(void)
    {
        ++cost;
        return (*this);
    }

    Edge Edge::operator++(int)
    {
        Edge *old = this;
        ++(*this);
        return (*old);
    }

    Edge &Edge::operator--(void)
    {
        --cost;
        return (*this);
    }

    Edge Edge::operator--(int)
    {
        Edge *old = this;
        --(*this);
        return (*old);
    }

    Edge &Edge::operator+=(int num)
    {
        cost += num;
        return (*this);
    }

    Edge &Edge::operator-=(int num)
    {
        cost -= num;
        return (*this);
    }

    bool operator==(Edge a, Edge b)
    {
        return (a.source == b.source && a.destination == b.destination && a.cost == b.cost);
    }

    Vertex::Vertex() : in(), out() {}

    Vertex::Vertex(const Vertex& other) : in(other.in), out(other.out) {}

    Digraph::Digraph(void) : edges(), vertices() {}

    Digraph::Digraph(const Digraph& other) : edges(other.edges), vertices(other.vertices) {}

    int Digraph::get_vertices() const
    {
        return (int)vertices.size();
    }

    bool Digraph::is_edge(Vertex a, Vertex b) const
    {
        for(auto out : a.out)
            if(std::find(b.in.begin(), b.in.end(), out) != b.in.end())
                return true;

        return false;
    }

    InOutDegree Digraph::get_degree(int vertex) const
    {
        InOutDegree deg;
        deg.first = (int)vertices[vertex].in.size();
        deg.second = (int)vertices[vertex].out.size();
        return deg;
    }

    std::vector::iterator Digraph::outbound_iterator(int vertex) const
    {
        std::vector<int> destinations;
        for(auto edge : edges)
            if(edge.source == vertex)
                destinations.push_back(edge.destination);

        return destinations.begin();
    }

    std::vector::iterator Digraph::inbound_edge(int vertex) const
    {
        std::vector<int> sources;
        for(auto edge : edges)
            if(edge.destination == vertex)
                sources.push_back(edge.source);

        return sources.begin();
    }

    int Digraph::get_cost(Edge e)
    {
        for(auto edge : edges)
            if(edge == e)
                return edge.cost;

        throw "Edge does not exist!";
    }

    void Digraph::add_edge(Edge e)
    {
        if(std::find(edges.begin(), edges.end(), e) != edges.end())
            throw "Edge already exists!";
        edges.push_back(e);
    }

    void Digraph::remove_edge(Edge e)
    {
        ptrdiff_t pos = std::find(edges.begin(), edges.end(), e) - edges.begin();
        if(pos >= edges.size())
            throw "Edge does not exist!";
        edges.erase(edges.begin() + pos);
        return;
    }
}
