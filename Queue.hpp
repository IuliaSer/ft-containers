#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include "List.hpp"
#include <deque>

namespace ft
{
    template <class T, class Container = std::deque<T> >
    class queue
    {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        private:
            container_type      _ctnr;
        public:
            explicit queue (const container_type& ctnr = container_type())
            {
                _ctnr = ctnr;
            }

            queue(const queue& x) : _ctnr(x._ctnr) {}
                
            ~queue() {}
            //_______________________Member_functions____________________________//

            bool empty() const
            {
                return _ctnr.empty();
            }

            size_type size() const
            {
                return _ctnr.size();
            }

            value_type& front()
            {
                return _ctnr.front();
            }

            const value_type& front() const
            {
                return _ctnr.front();
            }

            value_type& back()
            {
                return _ctnr.back();
            }

            const value_type& back() const
            {
                return _ctnr.back();
            }

            void push (const value_type& val)
            {
                return _ctnr.push_back(val);
            }

            void pop()
            {
                return _ctnr.pop_front();
            }
            //__________________________No_member_functions________________________________________//

            friend bool operator==(const queue& lhs, const queue& rhs)
            {
                return lhs._ctnr == rhs._ctnr;
            }
            friend bool operator!=(const queue& lhs, const queue& rhs)
            {   
                return lhs._ctnr != rhs._ctnr;
            }
            friend bool operator<(const queue& lhs, const queue& rhs)
            {
                return lhs._ctnr < rhs._ctnr;
            }
            friend bool operator<=(const queue& lhs, const queue& rhs)
            {   
                return lhs._ctnr <= rhs._ctnr;
            }
            friend bool operator>(const queue& lhs, const queue& rhs)
            {   
                return lhs._ctnr > rhs._ctnr;
            }
            friend bool operator>=(const queue& lhs, const queue& rhs)
            {   
                return lhs._ctnr >= rhs._ctnr;
            }

            private:
        
            template <typename U>
            void swap(U& a, U& b)
            {
                U tmp(a);
                a = b;
                b = tmp;
            }
    };
}

#endif