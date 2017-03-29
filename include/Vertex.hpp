//
// Created by Eric on 22.03.2017.
//

#ifndef DIGRAPH_VERTEX_HPP
#define DIGRAPH_VERTEX_HPP

#include <vector>
#include <algorithm>
#include "Edge.hpp"


namespace Graph
{
    template <typename key_t, typename value_t>
    class Vertex
    {
    private:
        value_t value;
        std::vector<key_t> in;
        std::vector<key_t> out;
    public:
        Vertex(void) : value(), in(), out() {}
        Vertex(const value_t& value) : value(value), in(), out() {}
        Vertex(const Vertex<key_t, value_t>& other) : value(other.get_value()), in(other.get_in()), out(other.get_out()) {}
        ~Vertex() = default;



        value_t get_value() const
        {
            return this->value;
        }


        unsigned long long get_in() const
        {
            return this->in.size();
        }

        unsigned long long get_out() const
        {
            return this->out.size();
        }

        void set_value(value_t value)
        {
            this->value = value;
        }

        void add_in(key_t key)
        {
            in.push_back(key);
        }

        void remove_in(key_t key)
        {
            for(auto e : in)
                if(e == key)
                {
                    ptrdiff_t pos = std::find(in.begin(), in.end(), e) - in.begin();
                    in.erase(in.begin() + pos);
                    return;
                }
        }

        void remove_out(key_t key)
        {
            for(auto e : out)
                if(e == key)
                {
                    ptrdiff_t pos = std::find(out.begin(), out.end(), e) - out.begin();
                    out.erase(out.begin() + pos);
                    return;
                }
        }

        void add_out(key_t key)
        {
            out.push_back(key);
        }

        std::vector<key_t>::iterator get_outbound_iterator()
        {
            return std::vector<key_t>::iterator();
        }

        std::vector<key_t>::iterator get_outbound_begin()
        {
            return this->out.begin();
        }

        std::vector<key_t>::iterator get_outbound_end()
        {
            return this->out.end();
        }

        std::vector<key_t>::iterator get_inbound_iterator()
        {
            return std::vector<key_t>::iterator();
        }

        std::vector<key_t>::iterator get_inbound_begin()
        {
            return this->in.begin();
        }

        std::vector<key_t>::iterator get_inbound_end()
        {
            return this->in.end();
        }

        bool operator<(const Vertex<key_t, value_t>& rhs) const
        {
            return this->value < rhs.get_value();
        }

        bool operator>(const Vertex<key_t, value_t>& rhs) const
        {
            return rhs.get_value() < this->get_value();
        }

        bool operator<=(const Vertex<key_t, value_t>& rhs) const
        {
            return not (rhs.get_value() < this->get_value());
        }

        bool operator>=(const Vertex<key_t, value_t>& rhs) const
        {
            return not (this->get_value() < rhs.get_value());
        }

        bool operator==(const Vertex<key_t, value_t>& rhs) const
        {
            return this->value == rhs.get_value();
        }

        bool operator!=(const Vertex<key_t, value_t>& rhs) const
        {
            return not (rhs.get_value() == this->get_value());
        }
    };
}

#endif //DIGRAPH_VERTEX_HPP
