#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
//#include "Vector.hpp"
#include "List.hpp"
#include <deque>

namespace ft
{
    template <class T, class Container = std::deque<T> >
    class stack
    {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        private:
            container_type      _ctnr;
        public:
            explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr)
            {}

            stack(const stack& x) : _ctnr(x._ctnr) {}
                
            ~stack() {}
            //_______________________Member_functions____________________________//

            bool empty() const
            {
                return _ctnr.empty();
            }

            size_type size() const
            {
                return _ctnr.size();
            }

            value_type& top()
            {
                return _ctnr.back();
            }

            const value_type& top() const
            {
                return _ctnr.back();
            }

            void push (const value_type& val)
            {
                return _ctnr.push_back(val);
            }

            void pop()
            {
                return _ctnr.pop_back();
            }
            //__________________________No_member_functions________________________________________//

            friend bool operator==(const stack& lhs, const stack& rhs)
            {
                return lhs._ctnr == rhs._ctnr;
            }
            friend bool operator!=(const stack& lhs, const stack& rhs)
            {   
                return lhs._ctnr != rhs._ctnr;
            }
            friend bool operator<(const stack& lhs, const stack& rhs)
            {
                return lhs._ctnr < rhs._ctnr;
            }
            friend bool operator<=(const stack& lhs, const stack& rhs)
            {   
                return lhs._ctnr <= rhs._ctnr;
            }
            friend bool operator>(const stack& lhs, const stack& rhs)
            {   
                return lhs._ctnr > rhs._ctnr;
            }
            friend bool operator>=(const stack& lhs, const stack& rhs)
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