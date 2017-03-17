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

    Digraph::Digraph(void) : edges(), vertices(), vertex_count(), edge_count() {}

    Digraph::Digraph(const Digraph& other) : edges(other.edges), vertices(other.vertices), vertex_count(other.vertex_count), edge_count(other.edge_count) {}

    int Digraph::get_vertices() const
    {
        return (int)vertices.size();
    }

    bool Digraph::is_edge(int source, int destination) const
    {
        for(auto o : vertices[source].out)
            if(o == destination)
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

    std::vector<int>::iterator Digraph::outbound_iterator(int vertex) const
    {
        std::vector<int> destinations;
        for(auto edge : edges)
            if(edge.source == vertex)
                destinations.push_back(edge.destination);

        return destinations.begin();
    }

    std::vector<int>::iterator Digraph::inbound_iterator(int vertex) const
    {
        std::vector<int> sources;
        for(auto edge : edges)
            if(edge.destination == vertex)
                sources.push_back(edge.source);

        return sources.begin();
    }

    Edge& Digraph::get_cost(Edge e)
    {
        for(auto edge : edges)
            if(edge == e)
                return edge;

        throw "Edge does not exist!";
    }

    void Digraph::add_edge(int source, int destination, int cost)
    {
        auto e = Edge(source, destination, cost);
        if(std::find(edges.begin(), edges.end(), e) != edges.end())
            throw "Edge already exists!";
        edges.push_back(e);
        generate_vertices();
        return;
    }

    void Digraph::remove_edge(int source, int destination)
    {
        for(auto e : edges)
        {
            if(e.source == source and e.destination == destination);
            {
                ptrdiff_t pos = std::find(edges.begin(), edges.end(), e) - edges.begin();
                edges.erase(edges.begin() + pos);
                generate_vertices();
                return;
            }
        }
        throw "Edge does not exist!";
    }

    void Digraph::generate_vertices()
    {

        vertices.clear();
        for(int i = 0; i < vertex_count; ++i)
        {
            auto v = Vertex();
            vertices.push_back(v);
        }

        for(auto edge : edges)
        {
            vertices[edge.source].out.push_back(edge.destination);
            vertices[edge.destination].in.push_back(edge.source);
        }
    }

    void Digraph::read_graph_from_file(std::string filename)
    {
        std::ifstream graph_reader(filename);
        if(graph_reader.is_open())
        {
            edges.clear();
            vertices.clear();
            graph_reader >> vertex_count >> edge_count;
            for(int i = 0; i < edge_count; ++i)
            {
                int s, d, c;
                graph_reader >> s >> d >> c;
                add_edge(s, d, c);
            }
            generate_vertices();
            return;
        }
        throw "File does not exists!";
    }
}
