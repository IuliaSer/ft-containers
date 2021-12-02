#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <memory>
#include "List_iterator.hpp"
#include "AddStructs.hpp"

namespace ft
{
    template <typename T, class Alloc = std::allocator<T> >
    class list
    {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef value_type const *const_pointer;
        typedef size_t size_type;
        typedef node<T> node;
        typedef typename allocator_type::template rebind<node>::other node_alloc;
        typedef typename node_alloc::pointer                node_ptr;
        typedef typename ft::ListIterator<T>                iterator;
        typedef typename ft::ConstListIterator<T>           const_iterator;
        typedef typename ft::ReverseListIterator<T>         reverse_iterator;
        typedef typename ft::ConstReverseListIterator<T>    const_reverse_iterator;
    private:
        allocator_type _alloc;
        size_type _size;
        node* _tail;
        node_alloc _node_alloc;

    public:
        //___________________________Helper_functions__________________________//
        node *new_node(const value_type &val)
        {
            node *tmp = _node_alloc.allocate(1);
            _alloc.construct(&tmp->content, val);
            tmp->prev = tmp;
            tmp->next = tmp;
            return (tmp);
        }

        node *new_node()
        {
            node *tmp = _node_alloc.allocate(1);
            tmp->prev = tmp;
            tmp->next = tmp;
            return (tmp);
        }
        //_____________________Constructors, destructor and assignment operator________________//
        explicit list(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0)
        {
            _tail = new_node();
        }

        explicit list(size_type n, const value_type &val = value_type(),
                      const allocator_type &alloc = allocator_type())
        {
            _tail = new_node(0);
            _alloc = alloc;
            for (size_t i = 0; i < n; i++)
                push_back(val);
            _size = n;
        }

        template <class InputIterator>
            list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
        {
            _tail = new_node(0);
            size_type i = 0;
            _alloc = alloc;
            while(first != last)
            {
                push_back(*first);
                first++;
                i++;
            }
            _size = i;
        }
        
        list (const list& x)
        {
            _tail = new_node(0);
            _size = 0;
            _alloc = x._alloc;
            for (const_iterator it = x.begin(); it != x.end(); ++it)
                push_back(*it);
        }

        list& operator= (const list& x)
        {
            list copy(x);
            this->swap(copy);
            return *this;
        }
        ~list()
        {
            if(_size > 0)
            {
                node *tmp = _tail->next;
                while(tmp != _tail)
                {
                    _alloc.destroy(&tmp->content);
                    _node_alloc.deallocate(tmp, 1);
                    tmp = tmp->next;
                }
            }
            _node_alloc.deallocate(_tail, 1);
        }
        
        
        //_____________________Modifiers____________________________//

        void push_back(const value_type &val)
        {
            node *node = new_node(val);
            node->next = _tail;
            node->prev = _tail->prev;
            _tail->prev->next = node;
            _tail->prev = node;
            _size++;
        }

        void push_front(const value_type &val)
        {
            node *node = new_node(val);
            node->next = _tail->next;
            node->prev = _tail;
            _tail->next->prev = node;
            _tail->next = node;
            _size++;
        }

        void pop_front()
        {
            if (_size--)
            {
                node *tmp = _tail;
                _tail = _tail->next;
                _tail->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                _node_alloc.deallocate(tmp, 1);
            }
        }

        void pop_back()
        {
            if (_size--)
            {
                node *tmp = _tail->prev;
                _tail->prev->prev->next = _tail;
                _tail->prev = _tail->prev->prev;
                
                _alloc.destroy(&tmp->content);
                _node_alloc.deallocate(tmp, 1);
            }
        }

        void clear()
        {
            while(_size)
                pop_back();
            _tail->next = _tail;
            _tail->prev = _tail;
        }

        void assign (size_type n, const value_type& val)
        {
            node* tmp = _tail->next;
            size_type i = 0;
            for (; i < n; i++)
            {
                if (i < _size)
                {
                    _alloc.destroy(&tmp->content);
                    _alloc.construct(&tmp->content, val);
                }
                else
                    push_back(val);
                tmp = tmp->next;
            }
            while (_size > i)
                pop_back();
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
        {
            node *tmp = _tail->next;
            size_type i = 0;
            size_type j = 0;
            while (first != last)
            {
                if (i < _size)
                {
                    _alloc.destroy(&tmp->content);
                    _alloc.construct(&tmp->content, *first);
                }
                else
                    push_back(*first);
                tmp = tmp->next;
                first++;
                j++;
            }
            while (_size > j)
                pop_back();
        }

        void resize(size_type n, value_type val = value_type())
        {
            node *tmp = _tail->prev;
            size_type i = 0;
            if (_size > n)
            {
                while (i < _size - n)
                {
                    _alloc.destroy(&tmp->content);
                    _node_alloc.deallocate(tmp, 1);
                    tmp = tmp->prev;
                    i++;
                }
                tmp->next = _tail;
                _tail->prev = tmp;
                _size = n;
            }
            else if (_size < n)
            {
                size_type c = n - _size;
                for(size_type i = 0; i < c; i++)
                    push_back(val);
            }
        }

        iterator insert(iterator position, const value_type &val)
        {
            node *tmp = new_node(val);

            position.getNode()->prev->next = tmp;
            tmp->prev = position.getNode()->prev;
            position.getNode()->prev = tmp;
            tmp->next = position.getNode();
            _size++;
            return (iterator(--position));
        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            for(size_type i = 0; i < n; i++)
                position = insert(position, val);
        }

        template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
        {
            while(first != last)
            {
                position = insert(position, *first);
                first++;
            }
        }

        iterator erase (iterator position)
        {
            if (position.getNode() == _tail)
                return position;
            iterator tmp = position;
            tmp++;
            position.getNode()->prev->next = position.getNode()->next;
            position.getNode()->next->prev = position.getNode()->prev;
            _alloc.destroy(&position.getNode()->content);
            _node_alloc.deallocate((position).getNode(), 1);
            _size--;
            return iterator(tmp);
        }

        iterator erase (iterator first, iterator last)
        {
            size_type i = 0;
            first.getNode()->prev->next = last.getNode();
            last.getNode()->prev = first.getNode()->prev;
            while(first != last)
            {
                _node_alloc.deallocate(first.getNode(), 1);
                first++;
                i++;
            }
            _size -= i;
            return iterator(first);
        }

        void swap (list& x)
        {
            if (this != &x)
                {
                    node *tmp = _tail;
                    size_type tmp_size = this->_size;
                    allocator_type tmp_alloc = this->_alloc;
                    this->_tail = x._tail;
                    this->_size = x._size;
                    this->_alloc = x._alloc;
                    x._tail = tmp;
                    x._size = tmp_size;
                    x._alloc = tmp_alloc;
                }
        }
        //_____________________Operations___________________________//

        void remove (const value_type& val)
        {
            node *tmp = _tail->next;
            while(tmp != _tail)
            {
                if(tmp->content == val)
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    _alloc.destroy(&tmp->content);
                    _node_alloc.deallocate(tmp, 1);
                    _size--;
                }
                tmp = tmp->next;
            }
        }

        template <class Predicate>
            void remove_if (Predicate pred)
        {
            node *tmp = _tail->next;
            while(tmp != _tail)
            {
                if(pred(tmp->content))
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    _alloc.destroy(&tmp->content);
                    _node_alloc.deallocate(tmp, 1);
                    _size--;
                }
                tmp = tmp->next;
            }
        }
        void unique()
        {
            node *tmp = _tail->next;
            while(tmp != _tail)
            {
                if (tmp->content == tmp->next->content)
                {
                    node *tmp2 = tmp;
                    tmp = tmp->next;
                    while (tmp2->content == tmp->content && tmp != _tail)
                    {
                        _alloc.destroy(&tmp->content);
                        _node_alloc.deallocate(tmp, 1); //?
                        tmp = tmp->next;
                        _size--;
                    }
                    tmp2->next = tmp;
                    tmp->prev = tmp2;
                }
                else
                    tmp = tmp->next;
            }
        }

        template <class BinaryPredicate>
            void unique (BinaryPredicate binary_pred)
        {
            node *tmp = _tail->next;
            while(tmp != _tail)
            {
                if (binary_pred(tmp->content, tmp->next->content))
                {
                    node *tmp2 = tmp;
                    tmp = tmp->next;
                    while (tmp2->content == tmp->content)
                    {
                        _alloc.destroy(&tmp->content);
                        _node_alloc.deallocate(tmp, 1);
                        tmp = tmp->next;
                        _size--;
                    }
                    tmp2->next = tmp;
                    tmp->prev = tmp2;
                }
                else
                    tmp = tmp->next;
            }
        }

        void reverse()
        {
            node *tmp = _tail;
            node *tmp2 = _tail->prev;
            size_type n = _size + 1;
            while(n--)
            {
                tmp->prev = tmp->next;
                tmp->next = tmp2;
                tmp = tmp->next;
                tmp2 = tmp->prev;
            }
        }

        void splice (iterator position, list& x)
        {
            position.getNode()->prev->next = x._tail->next;
            x._tail->next->prev = position.getNode()->prev;

            x._tail->prev->next = position.getNode();
            position.getNode()->prev = x._tail->prev;

            x._tail->prev = x._tail;
            x._tail->next = x._tail;
            _size += x._size;
            x._size = 0;
        }

        void splice (iterator position, list& x, iterator i)
        {
            node *tmp = x._tail->next;
            size_type j = 0;
            while (tmp != x._tail)
            {   
                {
                    if (i.getNode() == tmp)
                    {
                        j++;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            if (j == 0)
                return;
            i.getNode()->prev->next = i.getNode()->next;
            i.getNode()->next->prev = i.getNode()->prev;

            position.getNode()->prev->next = i.getNode();
            i.getNode()->prev = position.getNode()->prev;
            i.getNode()->next = position.getNode();
            position.getNode()->prev = i.getNode();

            _size++;
            x._size--;
        }

        void splice (iterator position, list& x, iterator first, iterator last)
        {
            iterator tmp = first;
            size_type i = 0;
            node *tmp_node = first.getNode()->prev;
            node *tmp_node2 = last.getNode();
            while(tmp != last)
            {
                tmp++;
                i++;
            }
            position.getNode()->prev->next = first.getNode();
            first.getNode()->prev = position.getNode()->prev;
            last.getNode()->prev->next = position.getNode();
            position.getNode()->prev = last.getNode()->prev;

            tmp_node->next = tmp_node2;
            tmp_node2->prev = tmp_node;
            _size += i;
            x._size -= i;
        }

        void sort()
        {
            node *tmp;
            node *tmp2;
            node *tmptmp;
            for (size_type i = 0; i < (_size - 1); i++)
            {
                tmp = _tail->next;
                tmp2 = _tail->next->next;
                for (size_type j = 0; j < (_size - 1) - i; j++)
                {
                    if (tmp->content > tmp2->content)
                    {
                        tmptmp = tmp->prev;
                        tmptmp->next = tmp2;

                        tmp->prev = tmp2;
                        tmp->next = tmp2->next;
                        
                        tmp2->next = tmp;
                        tmp2->prev = tmptmp;

                        tmp = tmp->prev;
                        tmp2 = tmp->next;

                        tmp2->next->prev = tmp2;
                    }
                    tmp = tmp->next;
                    tmp2 = tmp2->next;
                }
            }
        }

        template <class Compare>
            void sort (Compare comp)
        {
            node *tmp;
            node *tmp2;
            node *tmptmp;
            for (size_type i = 0; i < (_size - 1); i++)
            {
                tmp = _tail->next;
                tmp2 = _tail->next->next;
                for (size_type j = 0; j < (_size - 1) - i; j++)
                {
                    if (!(comp(tmp->content, tmp2->content)))
                    {
                        tmptmp = tmp->prev;
                        tmptmp->next = tmp2;

                        tmp->prev = tmp2;
                        tmp->next = tmp2->next;
                        
                        tmp2->next = tmp;
                        tmp2->prev = tmptmp;

                        tmp = tmp->prev;
                        tmp2 = tmp->next;

                        tmp2->next->prev = tmp2;
                    }
                    tmp = tmp->next;
                    tmp2 = tmp2->next;
                }
            }
        }

        void merge (list& x)
        {
            if(this->_tail == x._tail)
                return;
            node *tmp = _tail->next;
            node *tmp2 = x._tail->next;
            node *tmp3 = tmp2;
            while(tmp != _tail && tmp2 != x._tail)
            {
                if(tmp->content == tmp2->content || tmp2->content < tmp->content)
                {
                    tmp3 = tmp2->next;

                    tmp2->prev = tmp->prev;
                    tmp->prev->next = tmp2;
                    tmp->prev = tmp2;
                    tmp2->next = tmp;

                    tmp2 = tmp3;
                    _size++;
                }
                else
                    tmp = tmp->next;
            }
            while(tmp2 != x._tail)
            {
                    tmp3 = tmp2->next;

                    tmp2->prev = tmp->prev;
                    tmp->prev->next = tmp2;
                    tmp->prev = tmp2;
                    tmp2->next = tmp;

                    tmp2 = tmp3;
                    _size++;
            }
            x._size = 0;
            x._tail->next = x._tail;
            x._tail->prev = x._tail;
        }

        template <class Compare>
            void merge (list& x, Compare comp)
        {
            if(this->_tail == x._tail)
                return;
            node *tmp = _tail->next;
            node *tmp2 = x._tail->next;
            node *tmp3 = tmp2;
            while(tmp != _tail && tmp2 != x._tail)
            {
                if(tmp->content == tmp2->content || comp(tmp2->content, tmp->content))
                {
                    tmp3 = tmp2->next;

                    tmp2->prev = tmp->prev;
                    tmp->prev->next = tmp2;
                    tmp->prev = tmp2;
                    tmp2->next = tmp;

                    tmp2 = tmp3;
                    _size++;
                }
                else
                    tmp = tmp->next;
            }
            while(tmp2 != x._tail)
            {
                    tmp3 = tmp2->next;

                    tmp2->prev = tmp->prev;
                    tmp->prev->next = tmp2;
                    tmp->prev = tmp2;
                    tmp2->next = tmp;

                    tmp2 = tmp3;
                    _size++;
            }
            x._size = 0;
            x._tail->next = _tail;
            x._tail->prev = _tail;
        }
        //_____________________Element access_______________________//

        reference front()
        {
            return _tail->next->content;
        }

        const_reference front() const
        {
            return _tail->next->content;
        }

        reference back()
        {
            return _tail->prev->content;
        }

        const_reference back() const
        {
            return _tail->prev->content;
        }
        //_________________________Capacity______________________//

        bool empty() const
        {
            return _size == 0;
        }

        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(ft::node<value_type>)));
			};

        //_______________________________Iterators__________________________________//

        iterator begin() { return (iterator(_tail->next)); }

        const_iterator  begin() const           { return const_iterator(_tail->next); }

        iterator end() { return iterator(_tail); }

        const_iterator  end() const             { return const_iterator(_tail); }

        reverse_iterator rbegin()               { return reverse_iterator(_tail->prev); }

        const_reverse_iterator rbegin() const   { return const_reverse_iterator(_tail->prev); }

        reverse_iterator rend()                 { return reverse_iterator(_tail->next); }

        const_reverse_iterator rend() const     { return const_reverse_iterator(_tail->next); }
    };

    //__________________________No_member_functions________________________________________//

    template <class T, class alloc>
    void swap (list<T,alloc>& x, list<T,alloc>& y)
    {
        x.swap(y);
    }
    template <class T, class Alloc>
        bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    { 
        typename ft::list<T>::iterator it = lhs.begin();
        typename ft::list<T>::iterator it2 = rhs.begin();
        typename ft::list<T>::iterator ite = lhs.end();
        if (lhs.size() != rhs.size())
            return false;
        while(it != ite)
        {
            if(it.getNode()->content != it2.getNode()->content)
                return false;
            it++;
            it2++;
        }
        return true;
    }
    template <class T, class Alloc>
        bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
        bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        typename ft::list<T>::iterator it = lhs.begin();
        typename ft::list<T>::iterator it2 = rhs.begin();
        typename ft::list<T>::iterator ite = lhs.end();
        typename ft::list<T>::iterator it2e = lhs.end();
        while(it != ite && it2 != it2e)
        {
            if (it.getNode()->content < it2.getNode()->content)
                return true;
            if (it.getNode()->content > it2.getNode()->content)
                return false;
            it++;
            it2++;
        }
        if (lhs.size() < rhs.size())
            return true;
        return false;
    }

    template <class T, class Alloc>
        bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        return (lhs < rhs || lhs == rhs);
    }

    template <class T, class Alloc>
        bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        return !(lhs <= rhs);
    }

    template <class T, class Alloc>
        bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif