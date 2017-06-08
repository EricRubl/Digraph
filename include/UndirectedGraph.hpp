//
// Created by Eric on 13.04.2017.
//

#ifndef DIGRAPH_UNDIRECTEDGRAPH_HPP
#define DIGRAPH_UNDIRECTEDGRAPH_HPP


#include <fstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <string>
#include "Graph.hpp"

#define INF 0x3f3f3f3f

namespace Graph
{
    template <typename key_type, typename edge_cost_type, typename vertex_cost_type>
    class UndirectedGraph : IGraph<key_type, edge_cost_type, vertex_cost_type>
    {
        using IGraphT = IGraph<key_type, edge_cost_type, vertex_cost_type>;

    private:
        int find(std::vector<int> parent, int i)
        {
            if(parent[i] == -1)
                return i;
            return find(parent, parent[i]);
        }


        // AM PUS REFERINTA            v            FARA ASTA NU MERGEA VECI, GRIJA LA DIFERENTELE
        // DINTRE int parent[] ca parametru ( parent e pointer spre primul element ) si std::array<> parent !!!!!!!!!!!
        // std::array e obiect si daca nu il dai prin referinta se face copie si pierzi modificarea
        // atentie Eric
        // ATENTIE!!!
        // ACUMA MERGE~!!!!!!!!!!!@#@*() :&
        void Union(std::vector<int>& parent, int x, int y)
        {
            int xset = find(parent, x);
            int yset = find(parent, y);
            parent[xset] = yset;
        }

    public:
        UndirectedGraph() : IGraph<key_type, edge_cost_type, vertex_cost_type>()
        {}

        UndirectedGraph(const UndirectedGraph& other) : IGraph<key_type, edge_cost_type, vertex_cost_type>(other)
        {}

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
            for(Edge<key_type, edge_cost_type> e : this->edges){
                if((e.get_source() == source and e.get_destination() == destination) or
                   (e.get_source() == destination and e.get_destination() == source)){
                    this->vertices[source].remove_out(destination);
                    this->vertices[source].remove_in(destination);
                    this->vertices[destination].remove_in(source);
                    this->vertices[destination].remove_out(destination);
                    ptrdiff_t pos = std::find(this->edges.begin(), this->edges.end(), e) - this->edges.begin();
                    auto it = std::find(this->edges.begin(), this->edges.end(), e);
                    if(it == this->edges.end()){
                        Edge<key_type, edge_cost_type> e2(e.get_destination(), e.get_source(), e.get_cost());
                        pos = std::find(this->edges.begin(), this->edges.end(), e2) - this->edges.begin();
                    }
                    this->edges.erase(this->edges.begin() + pos);

                    return;
                }
            }
            throw "Edge does not exist!";
        }

        virtual bool is_edge(const key_type& source, const key_type& destination) const override
        {
            for(Edge<key_type, edge_cost_type> e : this->edges){
                if((e.get_source() == source and e.get_destination() == destination) or
                   (e.get_source() == destination and e.get_destination() == source))
                    return true;
            }
            return false;
        }

        virtual void read_from_file(std::string filename) override
        {
            std::ifstream graph_reader(filename);
            if(graph_reader.is_open()){
                this->edges.clear();
                this->vertices.clear();
                int vertices_count, edge_count;
                graph_reader >> vertices_count;
                for(int i = 0; i < vertices_count; ++i) //TODO typename for key
                    this->add_vertex(i, i);
                graph_reader >> edge_count;
                for(int i = 0; i < edge_count; ++i){
                    key_type s, d;
                    edge_cost_type c;
                    graph_reader >> s >> d >> c;
                    add_edge(s, d, c);
                }
                return;
            }
            throw "File does not exists!";
        }

        virtual const unsigned long long get_vertices_count() const
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
            IGraphT::get_vertices_begin();
        }

        virtual typename std::map<key_type, Graph::Vertex<key_type, vertex_cost_type>>::iterator get_vertices_end()
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

            for(it = this->vertices[start].get_outbound_begin();
                it not_eq this->vertices[start].get_outbound_end(); ++it)
                bfs.push(this->vertices[*it]);

            while(!bfs.empty()){
                Vertex<key_type, vertex_cost_type> cur = bfs.front();
                viz[cur.get_value()] = true;

                for(it = cur.get_outbound_begin(); it not_eq cur.get_outbound_end(); ++it)
                    if(viz[*it] == false)
                        bfs.push(this->vertices[*it]);

                bfs.pop();
            }
            for(int i = 0; i < viz.size(); ++i){
                if(viz[i] == true)
                    vk.push_back(i);
            }
            return vk;
        }

        std::string Djikstra(key_type src, key_type dest)
        {
            std::priority_queue<std::pair<edge_cost_type, key_type>, std::vector<std::pair<edge_cost_type, key_type>>, std::greater<std::pair<edge_cost_type, key_type>>> pq;
            std::vector<edge_cost_type> dist(this->vertices.size(), INT_MAX);
            std::vector<bool> spt(this->vertices.size(), false);
            std::vector<key_type> parent(this->vertices.size(), -1);
            dist[src] = 0;
            pq.push(std::make_pair(0, src));

            while(!pq.empty()){
                key_type u = pq.top().second;
                pq.pop();
                for(auto it = this->vertices[u].get_outbound_begin();
                    it not_eq this->vertices[u].get_outbound_end(); ++it){
                    key_type v = *it;
                    edge_cost_type w = this->get_edge_cost(u, v);

                    if(dist[v] > dist[u] + w){
                        dist[v] = dist[u] + w;
                        pq.push(std::make_pair(dist[v], v));
                    }
                }
            }

            for(auto ctr = 0; ctr < this->get_vertices_count() - 1; ++ctr){
                int u;
                int min = INT_MAX;
                for(int v = 0; v < this->get_vertices_count(); ++v)
                    if(!spt[v] and dist[v] < min){
                        min = dist[v];
                        u = v;
                    }
                spt[u] = true;

                for(auto it = this->vertices[u].get_outbound_begin();
                    it not_eq this->vertices[u].get_outbound_end(); ++it)
                    if(!spt[*it] and dist[*it] >= dist[u] + this->get_edge_cost(u, *it))
                        parent[*it] = u;
            }

            std::string print;
            print += "From vertex " + std::to_string(src) + " to " + std::to_string(dest) + "\n\n";
            std::stack<key_type> path;
            key_type step = dest;
            while((step = parent[step]) not_eq -1)
                path.push(step);
            while(!path.empty()){
                print += std::to_string(path.top()) + " -> ";
                path.pop();
            }

            print += std::to_string(dest);
            return print;
        }


        //Checks for cycle in graph
        bool isCycle(int target_vertices_count)
        {
            std::vector<int> parent(target_vertices_count);
            //std::array<int,  gvc> parent; // edges array
            parent.assign(target_vertices_count, -1);  // initialized with -1

            // for every edge in graph
            for(Edge<int, int> edge : this->edges){
                // find subset of
                int x = find(parent, edge.get_source());       // the source of that edge
                int y = find(parent, edge.get_destination());  // and the destination of that edge

                // if they are the same
                if(x == y)
                    return true; // there is a cycle

                // union of two subsets, in parent
                Union(parent, x, y);
            }
            return false;
        }

        UndirectedGraph minimumSpanningTree()
        {
            // PROBLEMA ESTE CA PENTRU IS_CYCLE
            // NOI INCEPEM CU NODURILE 7 SI 6
            // SI VECTORUL ARE DOAR [0] SI [1] !!!!!!!!!!
            // trebuie
            // REFACTORIZATA
            UndirectedGraph graph;
            std::vector<Edge<key_type, edge_cost_type>> e = this->edges; // trebuie sa fie COPIE
            std::sort(e.begin(), e.end());
            for(Edge<int, int> edge : e){
                if(graph.edges.size() == (this->vertices.size() - 1))
                    break;


                graph.add_edge(edge.get_source(), edge.get_destination(), edge.get_cost());
                if(graph.isCycle(this->get_vertices_count()))
                    graph.remove_edge(edge.get_source(), edge.get_destination());
            }

            return graph;
        }

        // WARNING
        // ALIEN FUNCTION
        // DO NOT ENTER WITHOUT SPACESUIT
        std::stack<key_type> Hamiltonian()
        {
            {;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}{;}
            std::stack<key_type> ham;
            std::vector<int> path;
            for(int i = 0; i < this->get_vertices_count(); ++i)
                path.push_back(i); {;}{;}{;}{;}{;}{;}

            std::sort(path.begin(), path.end());


            {;}{;}{;}{;}{;}{;}{;}{;}{;}{;}
            while(std::next_permutation(path.begin(), path.end()))
            {
                int last = 0;

                {;}{;}{;}{;}{;}{;}{;}{;}
                for(auto i = 0; i < path.size() - 1; ++i)
                    if(!is_edge(path[i], path[i + 1]))
                        goto cifla;
                {;}{;}{;}{;}
                if(is_edge(path.front(), path.back()))
                {
                    for(auto v : path)
                        ham.push(v); {;}{;}
                    return ham;
                }
                cifla:
                    continue;
            }
        }
    };
}


#endif //DIGRAPH_UNDIRECTEDGRAPH_HPP
