//
// Created by Eric on 13.04.2017.
//

#ifndef DIGRAPH_UNDIRECTEDGRAPH_HPP
#define DIGRAPH_UNDIRECTEDGRAPH_HPP

#include <fstream>
#include <algorithm>
#include <queue>
#include "Graph.hpp"


namespace Graph
{
    template <typename key_type, typename edge_cost_type, typename vertex_cost_type>
    class UndirectedGraph : IGraph<key_type, edge_cost_type, vertex_cost_type>
    {
        using IGraphT = IGraph<key_type, edge_cost_type, vertex_cost_type>;

    public:
        UndirectedGraph() : IGraph<key_type, edge_cost_type, vertex_cost_type>() {}
        UndirectedGraph(const UndirectedGraph& other) : IGraph<key_type, edge_cost_type, vertex_cost_type>(other) {}
        ~UndirectedGraph() = default;

        virtual void add_edge(const key_type& source, const key_type& destination, const edge_cost_type& cost) override
        {
            Edge<key_type, edge_cost_type> e(source, destination, cost);
            Edge<key_type, edge_cost_type> e2(destination, source, cost);

           // if(std::find(this->edges.begin(), this->edges.end(), e) != this->edges.end())
               // throw "Edge already exists!";

            //if(std::find(this->edges.begin(), this->edges.end(), e2) != this->edges.end())
                //throw "Edge already exists!";

            this->edges.push_back(e);
            this->vertices[source].add_out(destination);
            this->vertices[source].add_in(destination);
            this->vertices[destination].add_in(source);
            this->vertices[destination].add_out(source);
        }

        virtual void remove_edge(const key_type& source, const key_type& destination) override
        {
            for(Edge<key_type, edge_cost_type> e : this->edges)
            {
                if((e.get_source() == source and e.get_destination() == destination) or (e.get_source() == destination and e.get_destination() == source));
                {
                    this->vertices[source].remove_out(destination);
                    this->vertices[source].remove_in(destination);
                    this->vertices[destination].remove_in(source);
                    this->vertices[destination].remove_out(destination);
                    ptrdiff_t pos = std::find(this->edges.begin(), this->edges.end(), e) - this->edges.begin();
                    this->edges.erase(this->edges.begin() + pos);
                    Edge<key_type, edge_cost_type> e2(destination, source, e.get_cost());
                    ptrdiff_t pos2 = std::find(this->edges.begin(), this->edges.end(), e2) - this->edges.begin();
                    this->edges.erase(this->edges.begin() + pos2);
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
                    this->add_vertex(i, i);
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

        virtual typename std::map<key_type, Graph::Vertex<key_type, vertex_cost_type>>::iterator get_vertices_begin()
        {
            IGraphT ::get_vertices_begin();
        }

        virtual typename  std::map<key_type, Graph::Vertex<key_type, vertex_cost_type>>::iterator get_vertices_end()
        {
            IGraphT::get_vertices_end();
        }

        virtual size_t get_vertices_size()
        {
            IGraphT::get_vertices_size();
        }

        std::vector<key_type> BFS(key_type start)
        {
            std::queue<Vertex<key_type, vertex_cost_type>> bfs;
            std::vector<key_type> vk;
            std::vector<bool> viz(this->vertices.size());
            typename std::vector<key_type>::iterator it;

            viz[start] = true;

            for (it = this->vertices[start].get_outbound_begin(); it not_eq this->vertices[start].get_outbound_end(); ++it)
                bfs.push(this->vertices[*it]);

            while (!bfs.empty())
            {
                Vertex<key_type, vertex_cost_type> cur = bfs.front();
                viz[cur.get_value()] = true;

                for (it = cur.get_outbound_begin(); it not_eq cur.get_outbound_end(); ++it)
                    if ( viz[*it] == false )
                        bfs.push(this->vertices[*it]);

                bfs.pop();
            }
            for (int i = 0; i < viz.size(); ++i)
            {
                if ( viz[i] == true )
                    vk.push_back(i);
            }
            return vk;
        }

    };
}


#endif //DIGRAPH_UNDIRECTEDGRAPH_HPP
