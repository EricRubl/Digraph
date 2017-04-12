//
// Created by Eric on 22.03.2017.
//

#ifndef DIGRAPH_GRAPH_HPP
#define DIGRAPH_GRAPH_HPP

#include <map>
#include <vector>
#include <utility>
#include "Edge.hpp"
#include "Vertex.hpp"

namespace Graph
{
    using InOutDegree = std::pair<int, int>;

    template <typename key_type, typename edge_cost_type, typename vertex_cost_type>
    class IGraph
    {
    protected:
        std::vector<Graph::Edge<key_type, edge_cost_type>> edges;
        std::map<key_type, Graph::Vertex<key_type, vertex_cost_type>> vertices;

    public:
        IGraph() : edges(), vertices() {}
        IGraph(const IGraph& other) : edges(other.get_edges()), vertices(other.get_vertices()) {}
        virtual ~IGraph() = 0;

        virtual std::vector<Graph::Edge<key_type, edge_cost_type>> get_edges() const
        {
            return this->edges;
        }
        virtual std::map<key_type, Graph::Vertex<key_type, vertex_cost_type>> get_vertices() const
        {
            return this->vertices;
        }


        virtual void add_edge(const key_type& source, const key_type& destination, const edge_cost_type& cost) = 0;

        virtual void remove_edge(const key_type& source, const key_type& destination) = 0;

        virtual void add_vertex(const key_type& key, const vertex_cost_type& value = 0)
        {
            if(vertices.find(key) != vertices.end())
                throw "Duplicate vertex!";
            vertices.insert(std::pair<key_type, Graph::Vertex<key_type, vertex_cost_type>> (key, Vertex<key_type, vertex_cost_type>(value)));
        }

        virtual void remove_vertex(const key_type& key)
        {
            if(vertices.find(key) == vertices.end())
                throw "Vertex does not exist!";
            vertices.erase(key);
        }

        virtual unsigned long long get_vertices_count() const
        {
            return this->vertices.size();
        }

        virtual bool is_edge(const key_type& source, const key_type& destination) const = 0;

        virtual InOutDegree get_degree(const key_type& key)
        {
            InOutDegree deg(std::make_pair(this->vertices[key].get_in(), this->vertices[key].get_out()));
            return deg;
        }

        virtual void change_cost(const key_type& source, const key_type& destination, const edge_cost_type& new_value)
        {
            for(Edge<key_type, edge_cost_type> e : edges)
                if(e.get_source() == source and e.get_destination() == destination)
                {
                    ptrdiff_t pos = std::find(this->edges.begin(), this->edges.end(), e) - this->edges.begin();
                    *(pos + this->edges.begin()) = new_value;
                    return;
                }
            throw "Edge does not exist!";
        }

        virtual void read_from_file(std::string filename) = 0;

        virtual edge_cost_type get_edge_cost(const key_type& source, const key_type& destination)
        {
            for(Edge<key_type, edge_cost_type> e : edges)
                if(e.get_source() == source and e.get_destination() == destination)
                    return e.get_cost();

            throw "Edge does not exist!";
        }
    };

    template <typename key_type, typename edge_cost_type, typename vertex_cost_type>
    inline IGraph<key_type, edge_cost_type, vertex_cost_type>::~IGraph() {}
}

#endif //DIGRAPH_GRAPH_HPP
