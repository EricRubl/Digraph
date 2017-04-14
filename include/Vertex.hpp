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
        Vertex(const Vertex<key_t, value_t>& other) : value(other.get_value()), in(other.get_in_v()), out(other.get_out_v()) {}
        ~Vertex() = default;



        std::vector<key_t> get_in_v() const
        {
            return this->in;
        }

        std::vector<key_t> get_out_v() const
        {
            return this->out;
        }

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

        typename std::vector<key_t>::iterator get_outbound_iterator()
        {
            return typename std::vector<key_t>::iterator();
        }

        typename std::vector<key_t>::iterator get_outbound_begin()
        {
            return this->out.begin();
        }

        typename std::vector<key_t>::iterator get_outbound_end()
        {
            return this->out.end();
        }

        typename std::vector<key_t>::iterator get_inbound_iterator()
        {
            return std::vector<key_t>::iterator();
        }

        typename std::vector<key_t>::iterator get_inbound_begin()
        {
            return this->in.begin();
        }

        typename std::vector<key_t>::iterator get_inbound_end()
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
            return this->value == rhs.get_value() and this->in == rhs.get_in_v() and this->out == rhs.get_out_v();

        }

        bool operator!=(const Vertex<key_t, value_t>& rhs) const
        {
            return not (rhs.get_value() == this->get_value());
        }


        Vertex<key_t, value_t>& operator=(const Vertex<key_t, value_t>& other)
        {
            this->value = other.get_value();
            this->in = other.get_in_v();
            this->out = other.get_out_v();
            return *this;
        };

    };
}

#endif //DIGRAPH_VERTEX_HPP
