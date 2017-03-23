//
// Created by Eric on 22.03.2017.
//

#ifndef DIGRAPH_EDGE_HPP
#define DIGRAPH_EDGE_HPP

namespace Graph
{


    template <typename key_t, typename cost_t>
    class Edge
    {
    private:
        key_t source;
        key_t destination;
        cost_t cost;

    public:
        Edge(void) : source(), destination(), cost() {}
        Edge(const Edge<key_t, cost_t>& other) : source(other.get_source()), destination(other.get_destination()), cost(other.get_cost()) {}
        Edge(const key_t& source, const key_t& destination, const cost_t& cost) : source(source), destination(destination), cost(cost) {}
        ~Edge() = default;

        key_t get_source() const
        {
            return this->source;
        }

        key_t get_destination() const
        {
            return this->destination;
        }

        cost_t get_cost() const
        {
            return this->cost;
        }

        void set_source(const key_t& source)
        {
            this->source = source;
        }

        void set_destination(const key_t& destination)
        {
            this->destination = destination;
        }

        void set_cost(const cost_t& cost)
        {
            this->cost = cost;
        }

        Edge& operator=(const Edge& other)
        {
            if(this != &other)
            {
                this->source = other.get_source();
                this->destination = other.get_destination();
                this->cost = other.get_cost();
            }
            return *this;
        }

        Edge& operator=(const cost_t& value)
        {
            this->cost = value;
            return *this;
        }

        Edge& operator+=(const cost_t& value)
        {
            this->cost += value;
            return *this;
        }

        Edge& operator-=(const cost_t& value)
        {
            this->cost -= value;
            return *this;
        }

        Edge& operator++(void)
        {
            ++(this->cost);
            return *this;
        }

        Edge operator++(int)
        {
            Edge old = *this;
            ++(*this);
            return old;
        }

        Edge& operator--(void)
        {
            --(this->cost);
            return *this;
        }

        Edge operator--(int)
        {
            Edge old = *this;
            --(*this);
            return old;
        }
    };

    template <typename key_t, typename cost_t>
    inline bool operator==(const Edge<key_t, cost_t>& a, const Edge<key_t, cost_t>& b)
    {
        return (a.get_source() == b.get_source() and a.get_destination() == b.get_destination() and a.get_cost() == b.get_cost());
    }

    template <typename key_t, typename cost_t>
    inline bool operator!=(const Edge<key_t, cost_t>& a, const Edge<key_t, cost_t>& b)
    {
        return not (a.get_source() == b.get_source() and a.get_destination() == b.get_destination() and a.get_cost() == b.get_cost());
    }

}



#endif //DIGRAPH_EDGE_HPP
