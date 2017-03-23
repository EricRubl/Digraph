//
// Created by Eric on 23.03.2017.
//

#ifndef DIGRAPH_DIRECTEDGRAPH_HPP
#define DIGRAPH_DIRECTEDGRAPH_HPP

#include "Graph.hpp"
#include <fstream>
#include <algorithm>


namespace Graph
{
    template <typename key_type, typename edge_cost_type, typename vertex_cost_type>
    class DirectedGraph : IGraph<key_type, edge_cost_type, vertex_cost_type>
    {

        using IGraphT = IGraph<key_type, edge_cost_type, vertex_cost_type>;

    public:
        DirectedGraph() : IGraph<key_type, edge_cost_type, vertex_cost_type>() {}
        DirectedGraph(const DirectedGraph& other) : IGraph<key_type, edge_cost_type, vertex_cost_type>(other) {}
        virtual ~DirectedGraph() = default;

        virtual void add_edge(const key_type& source, const key_type& destination, const edge_cost_type& cost) override
        {
            Edge<key_type, edge_cost_type> e(source, destination, cost);
            if(std::find(this->edges.begin(), this->edges.end(), e) != this->edges.end())
                throw "Edge already exists!";
            this->edges.push_back(e);
            this->vertices[source].add_out(destination);
            this->vertices[destination].add_in(source);
        }

        virtual void remove_edge(const key_type& source, const key_type& destination) override
        {
            for(Edge<key_type, edge_cost_type> e : this->edges)
            {
                if(e.get_source() == source and e.get_destination() == destination);
                {
                    this->vertices[source].remove_out(destination);
                    this->vertices[destination].remove_in(source);
                    ptrdiff_t pos = std::find(this->edges.begin(), this->edges.end(), e) - this->edges.begin();
                    this->edges.erase(this->edges.begin() + pos);
                    return;
                }
            }
            throw "Edge does not exist!";
        }

        virtual bool is_edge(const key_type& source, const key_type& destination) const override
        {
            for (Edge<key_type, edge_cost_type> e : this->edges)
            {
                if (e.get_source() == source and e.get_destination() == destination)
                    return true;
            }
            return false;
        }

        virtual void read_from_file(std::string filename) override
        {
            std::ifstream graph_reader(filename);
            if(graph_reader.is_open())
            {
                this->edges.clear();
                this->vertices.clear();
                int vertices_count, edge_count;
                graph_reader >> vertices_count;
                for(int i = 0; i < vertices_count; ++i) //TODO typename for key
                    this->add_vertex(i);
                graph_reader >> edge_count;
                for(int i = 0; i < edge_count; ++i)
                {
                    key_type s, d;
                    edge_cost_type c;
                    graph_reader >> s >> d >> c;
                    add_edge(s, d, c);
                }
                return;
            }
            throw "File does not exists!";
        }

        virtual unsigned long long get_vertices_count() const
        {
            IGraphT::get_vertices_count();
        }

        virtual std::vector<Graph::Edge<key_type, edge_cost_type>> get_edges() const
        {
            IGraphT::get_edges();
        }

        virtual std::map<key_type, Graph::Vertex<key_type, vertex_cost_type>> get_vertices() const
        {
            IGraphT::get_vertices();
        }

        virtual void add_vertex(const key_type& key, const vertex_cost_type& value = 0)
        {
            IGraphT::add_vertex(key, value);
        }

        virtual void remove_vertex(const key_type& key)
        {
            IGraphT::remove_vertex(key);
        }

        virtual InOutDegree get_degree(const key_type& key)
        {
            IGraphT::get_degree(key);
        }

        virtual void change_cost(const key_type& source, const key_type& destination, const edge_cost_type& new_value)
        {
            IGraphT::change_cost(source, destination, new_value);
        }

        virtual edge_cost_type get_edge_cost(const key_type& source, const key_type& destination)
        {
            IGraphT::get_edge_cost(source, destination);
        }
    };
}

#endif //DIGRAPH_DIRECTEDGRAPH_HPP
