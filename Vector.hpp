#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <memory>
#include "Vector_iterator.hpp"
#include "AddStructs.hpp"

namespace ft
{
    template<typename T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T 					                        value_type;
            typedef Alloc 				                        allocator_type;
            typedef value_type& 		                        reference;
            typedef const value_type& 	                        const_reference;
            typedef value_type* 		                        pointer;
            typedef value_type const * 	                        const_pointer;
            typedef ptrdiff_t 			                        difference_type;
            typedef size_t 				                        size_type;
            typedef typename ft::VectorIterator<T>              iterator;
            typedef typename ft::ConstVectorIterator<T>         const_iterator;
            typedef typename ft::ReverseVectorIterator<T>       reverse_iterator;
            typedef typename ft::ConstReverseVectorIterator<T>  const_reverse_iterator;
        private:
            allocator_type	_alloc;
            pointer   		_vector;
            size_type 		_capacity;
            size_type 		_size;
			
        public:
            //_____________________Constructors, destructor and assignment operator________________//
            vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _vector(NULL), _capacity(0), _size(0)  {}

            vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
            {
                _capacity = n;
                _size = n;
                if (n != 0)
                    _vector = _alloc.allocate(_capacity);
                else 
                    _vector = NULL;
                for(size_t i = 0; i < _size; i++)
                    _alloc.construct(&_vector[i], val);
            }
            vector (const vector& x)
            {
                pointer temp_vect = _alloc.allocate(x._capacity);
				for (size_t i = 0; i < x._size; i++)
					_alloc.construct(&temp_vect[i], x[i]);
				_vector = temp_vect;
                _size = x._size;
                _capacity = x._capacity;
                _alloc = x._alloc;
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : _alloc(alloc)
            {
                difference_type diff = last - first;
                _size = diff;
                _capacity = _size;
                size_type i = 0;
                _vector = _alloc.allocate(_capacity);
				while(first != last)
                {
					_alloc.construct(&_vector[i], *first);
                    first++;
                    i++;
                }
            }
            ~vector()
            {
                for(size_type i = 0; i < _size; i++)
                    _alloc.destroy(&_vector[i]);
                if (_vector != NULL)
                    _alloc.deallocate(_vector, _capacity);
            }

            vector& operator= (vector& x)
            {
                this->~vector();
                pointer _vector = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&_vector[i], x[i]);
                _size = x._size;
                _capacity = x._capacity;
                _alloc = x._alloc;
                return(*this);
            }

            //___________________________Helper_functions__________________________//
            void reallocate_vector(size_type new_capacity)
            {
                pointer temp_vect = _alloc.allocate(new_capacity);
                
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&temp_vect[i], _vector[i]);
                if(_capacity != 0)
                    this->~vector();
				_vector = temp_vect;
                _capacity = new_capacity;
            }
            //__________________________Element_access___________________________//
            reference operator[] (size_type n)
            {
                return (_vector[n]);
            }
            const_reference operator[] (size_type n) const
            {
                return (_vector[n]);
            }
            reference at (size_type n)
            {
                if (n >= _size)
                    throw std::exception();
                else 
                    return (_vector[n]);
            }
            const_reference at (size_type n) const
            {
                if (n >= _size)
                    throw std::exception();
                else 
                    return (_vector[n]);
            }
            reference front()
            {
                return(_vector[0]);
            }
            const_reference front() const
            {
                return(_vector[0]);
            }
            reference back()
            {
                return(_vector[_size - 1]);
            }
            const_reference back() const
            {
                return(_vector[_size - 1]);
            }
            //_______________________Member_functions____________________________//
            void push_back (const value_type& val)
            {
                size_type new_capacity = _capacity;
                if (_capacity < _size + 1)
                {
                    if (_capacity == 0)
                        new_capacity = 1;
                    else 
                        new_capacity *= 2;
                    reallocate_vector(new_capacity);
                }
                _alloc.construct(&_vector[_size++], val);
            }

			void pop_back()
			{
				if (_size)
					_alloc.destroy(&_vector[--_size]);
			}
			void clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_vector[i]);
                _size = 0;
			}
            iterator insert (iterator position, const value_type& val)
            {
                difference_type i = position - begin();
                if (_capacity < _size + 1)
                {
                    reallocate_vector(_capacity * 2);
                    position = &_vector[i];
                }
                size_type s = _size;
                while (s > (size_t)i)
                {
                    _alloc.construct(&_vector[s], _vector[s - 1]);
                    _alloc.destroy(&_vector[s - 1]);
                    s--;
                }
                _alloc.construct(&_vector[s], val);
                _size ++;
                return(position);
            }
            
			void insert (iterator position, size_type n, const value_type& val)
			{
                for(size_type i = 0; i < n; i++)
                {
                    position = insert(position, val);
                    position++;
                }
			}

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type * = NULL)
            {
                difference_type i = last - first;
                if(i == 0)
                    return;
                if (_capacity < _size + ((size_type)i))
                {
                    while (first != last)
                    {
                        position = insert(position, *first);
                        first++;
                        position++;
                    }
                }
                else
                {
                    difference_type j = position - begin();
                    size_type s = _size + i;
                    while (s > (size_t)i)
                    {
                        _alloc.construct(&_vector[s - 1], _vector[s - i]);
                        _alloc.destroy(&_vector[s - i]);
                        s--;
                    }
                    first += i;
                    last += i;
                    while (first != last)
                    {
                        _alloc.construct(&_vector[j], _vector[j + i]);
                        j++;
                        first++;
                    }
                    _size += i;
                }
            }
            void assign (size_type n, const value_type& val)
            {
                _size = n;
                if (n > _capacity)
                {
                    this->~vector();
                    _vector = _alloc.allocate(n);
                    for (size_t i = 0; i < n; i++)
                        _alloc.construct(&_vector[i], val);
                    _capacity = n;
                    return;
                }
                for (size_t i = 0; i < n; i++)
                {
                    _alloc.destroy(&_vector[i]);
                    _alloc.construct(&_vector[i], val);
                }
            }
            
            template <class InputIterator>
                void assign (InputIterator first, InputIterator last, 
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type * = NULL)
                {
                    size_type n = static_cast<size_type>(last - first);
                    if (n > _capacity)
                    {
                        this->~vector();
                        _vector = _alloc.allocate(n);
                        for (size_type i = 0; first < last; i++, first++)
                            _alloc.construct(&_vector[i], *first);
                        return;
                    }
                    size_type i = 0;
                    while(i < _size)
                    {
                        _alloc.destroy(&_vector[i]);
                        if(first != last)
                            _alloc.construct(&_vector[i], *first);
                        first++;
                        i++;
                    }
                    _size = n;
                }

            iterator erase (iterator position)
            {
                difference_type i = position - begin();
                _alloc.destroy(&_vector[i]);
                while ((size_t)i < _size)
                {
                    _alloc.construct(&_vector[i], _vector[i + 1]);
                    i++;
                }
                _alloc.destroy(&_vector[_size]);
                _size--;
                return(position);
            }

            iterator erase (iterator first, iterator last)
            {
                difference_type beg = first - begin();
                difference_type end = last - begin();
                difference_type dif = last - first;
                _alloc.destroy(&_vector[beg]);
                while ((size_t)beg < (_size - (size_t)end))
                {
                    _alloc.construct(&_vector[beg], _vector[beg + dif]);
                    beg++;
                    _alloc.destroy(&_vector[beg]);
                }
                _size -= (size_t)dif;
                while (dif--)
                    _alloc.destroy(&_vector[++beg]);
                return(first);
            }

            void swap (vector& x)
            {
                if (this != &x)
                {
                    pointer tmp_vector = this->_vector;
                    size_type tmp_size = this->_size;
                    size_type tmp_capacity = this->_capacity;
                    allocator_type tmp_alloc = this->_alloc;
                    this->_vector = x._vector;
                    this->_size = x._size;
                    this->_capacity = x._capacity;
                    this->_alloc = x._alloc;
                    x._vector = tmp_vector;
                    x._size = tmp_size;
                    x._capacity = tmp_capacity;
                    x._alloc = tmp_alloc;
                }
            }
            
            //_____________________________capacity______________________________//
            size_type size() const
            {
                return(_size);
            }
            size_type capacity() const
            {
                return(_capacity);
            }
            size_type max_size() const
            {
                size_t s;
                s = _alloc.max_size();
                return(s);
            }
            bool empty() const
            {
                return (_size == 0);
            }
            void reserve (size_type n)
            {
                if (_capacity < n)
                    reallocate_vector(n);
            }

            void resize (size_type n, value_type val = value_type())
            {
                if (n > _capacity)
                {
                    reallocate_vector(_capacity * 2);
                    while(_size < n)
                    {
                        _alloc.construct(&_vector[_size], val);
                        _size++;
                    }
                    return;
                }
                while(n < _size)
                    pop_back();
                while(n > _size)
                    push_back(val);
            }
            //_______________________________Iterators__________________________________//

            iterator        begin()                 { return iterator(_vector); }

            const_iterator  begin() const           { return const_iterator(_vector); }
            
            iterator        end()                   { return iterator(_vector + _size); }

            const_iterator  end() const             { return const_iterator(_vector + _size); }

            reverse_iterator rbegin()               { return reverse_iterator(_vector + _size - 1); }

            const_reverse_iterator rbegin() const   { return const_reverse_iterator(_vector + _size - 1); }
            
            reverse_iterator rend()                 { return reverse_iterator(_vector - 1); }
            
            const_reverse_iterator rend() const     { return const_reverse_iterator(_vector - 1); }

    };
        //__________________________No_member_functions________________________________________//

    template <class T, class alloc>
    void swap (ft::vector<T, alloc>& x, ft::vector<T, alloc>& y)
    {
        x.swap(y);
    }
    template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        if (lhs.capacity() != rhs.capacity())
            return false;
        for(size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }
    template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        size_t i = 0;
        while(i < lhs.size() && i < rhs.size())
        {
            if (lhs[i] < rhs[i])
                return true;
            if (lhs[i] > rhs[i])
                return false;
            i++;
        }
        if (lhs.size() < rhs.size())
            return true;
        return false;
    }

    template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs <= rhs);
    }

    template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (lhs < rhs || lhs == rhs);
    }

    template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
