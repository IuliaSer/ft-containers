#include "Vector.hpp"

namespace ft
{
    template<typename T>
    class VectorIterator
    {
        public:
            typedef T           value_type;
            typedef T&          reference;
            typedef T*          pointer;
            typedef ptrdiff_t 	difference_type;
        protected:
            pointer     _ptr;
        public:
            VectorIterator() {}
            VectorIterator(pointer ptr) : _ptr(ptr) {}
            VectorIterator(VectorIterator const &copy) {*this = copy;}
            VectorIterator &operator=(VectorIterator const &copy) 
            {
                _ptr = copy._ptr;
                return(*this);
            }
            ~VectorIterator() {}
            
            VectorIterator operator++(int) //post increment
            {
                VectorIterator temp = *this;
                _ptr++;
                return temp;
            }
            VectorIterator operator--(int) //post decrement
            {
                VectorIterator temp = *this;
                _ptr--;
                return temp;
            }
            VectorIterator &operator++()
            {
                _ptr++;
                return (*this);
            }
            VectorIterator &operator--()
            {
                _ptr--;
                return(*this);
            }
            VectorIterator operator+(int i) const
            {
                VectorIterator tmp = *this;
                tmp += i;
                return(tmp);
            }

            VectorIterator operator-(int i) const
            {
                VectorIterator tmp = *this;
                tmp -= i;
                return(tmp);
            }
            difference_type operator-(VectorIterator i) const
            {
                return(_ptr - i._ptr);
            }

            VectorIterator &operator-=(int n)
			{
				while (n > 0)
                {
					_ptr--;
                    n--;
                }
				while (n < 0)
                {
					_ptr++;
                    n++;
                }
				return (*this);
			}
            
            VectorIterator &operator+=(int n)
			{
				while (n > 0)
                {
					_ptr++;
                    n--;
                }
				while (n < 0)
                {
					_ptr--;
                    n++;
                }
				return (*this);
			}
            reference operator*() const
            {
                return(*_ptr);
            }
            pointer operator->() const
            {
                return(_ptr);
            }
            reference operator[](int n) const
			{
				return (*(*this + n));
			}
            //________________________compare_iterators_________________//

            bool operator<(const VectorIterator &other)
            {
                return (_ptr < other._ptr);
            }
            bool operator>(const VectorIterator &other) const
            {
                return (_ptr > other._ptr);
            }
            bool operator<=(const VectorIterator &other) const
            {
                return (_ptr <= other._ptr);
            }
            bool operator>=(const VectorIterator &other) const
            {
                return (_ptr >= other._ptr);
            }
            bool operator==(const VectorIterator &other) const
            {
                return (_ptr == other._ptr);
            }
            bool operator!=(const VectorIterator &other) const 
            {
                return (_ptr != other._ptr);
            }
    };

    template <class T>
	        class ConstVectorIterator : public VectorIterator<T>
            {
                public:
                    typedef T           value_type;
                    typedef T&          reference;
                    typedef T*          pointer;
                    typedef ptrdiff_t 	difference_type;
                    ConstVectorIterator() {}
                    ConstVectorIterator(pointer ptr) : VectorIterator<T>(ptr) {}
                    ConstVectorIterator(VectorIterator<T> const &copy) : VectorIterator<T>(copy) {}
                    ConstVectorIterator(ConstVectorIterator const &copy) : VectorIterator<T>(copy) {}
                    ConstVectorIterator &operator=(ConstVectorIterator const &copy) 
                    {
                        this->_ptr = copy._ptr;
                        return(*this);
                    }
                    ~ConstVectorIterator() {}
                    const value_type &operator*() const
                    {
                        return(*(this->_ptr));
                    }
                    const value_type &operator[](int n) const
                    {
                        return (*(*this + n));
                    }
            };
//___________________________referse_iterator__________________________//
    template<typename T>
    class ReverseVectorIterator : public VectorIterator<T>
    {
        public:
            typedef T           value_type;
            typedef T&          reference;
            typedef T*          pointer;
            typedef ptrdiff_t 	difference_type;
            ReverseVectorIterator() {}
            ReverseVectorIterator(pointer ptr) : VectorIterator<T>(ptr) {}
            ReverseVectorIterator(ReverseVectorIterator const &copy)
            {
                *this = copy;
            }
            ReverseVectorIterator &operator=(ReverseVectorIterator const &copy) 
            {
                VectorIterator<T>::operator=(copy);
                return(*this);
            }
            ~ReverseVectorIterator() {}
            
            ReverseVectorIterator operator++(int) //post increment
            {
                ReverseVectorIterator temp = *this;
                VectorIterator<T>::_ptr--;
            
                return temp;
            }
            ReverseVectorIterator operator--(int) //post decrement
            {
                ReverseVectorIterator temp = *this;
                VectorIterator<T>::_ptr++;
                return temp;
            }
            ReverseVectorIterator &operator++()
            {
                this->_ptr--;
                return (*this);
            }
            ReverseVectorIterator &operator--()
            {
                this->_ptr++;
                return(*this);
            }
            ReverseVectorIterator operator+(int i) const
            {
                ReverseVectorIterator tmp = *this;
                tmp += i;
                return(tmp);
            }

            ReverseVectorIterator operator-(int i) const
            {
                ReverseVectorIterator tmp = *this;
                tmp -= i;
                return(tmp);
            }
            difference_type operator-(ReverseVectorIterator i) const
            {
                return(VectorIterator<T>::_ptr - i._ptr);
            }

            ReverseVectorIterator &operator-=(int n)
			{
				while (n > 0)
                {
					this->_ptr++;
                    n--;
                }
				while (n < 0)
                {
                    this->_ptr--;
                    n++;
                }
				return (*this);
			}
            
            ReverseVectorIterator &operator+=(int n)
			{
				while (n > 0)
                {
                    this->_ptr--;
                    n--;
                }
				while (n < 0)
                {
					VectorIterator<T>::_ptr++;
                    n++;
                }
				return (*this);
			}
            reference operator*() const
            {
                return(*VectorIterator<T>::_ptr);
            }
            pointer operator->() const
            {
                return(VectorIterator<T>::_ptr);
            }
            reference operator[](int n) const
			{
				return (*(*this + n));
			}
        };

        template <class T>
	        class ConstReverseVectorIterator : public ReverseVectorIterator<T>
            {
                public:
                    typedef T           value_type;
                    typedef T&          reference;
                    typedef T*          pointer;
                    typedef ptrdiff_t 	difference_type;
                    ConstReverseVectorIterator() {}
                    ConstReverseVectorIterator(pointer ptr) : ReverseVectorIterator<T>(ptr) {}
                    ConstReverseVectorIterator(ConstReverseVectorIterator const &copy) {*this = copy;}
                    ConstReverseVectorIterator(ReverseVectorIterator<T> const &copy)  : ReverseVectorIterator<T>(copy) {}
                    ConstReverseVectorIterator &operator=(ConstReverseVectorIterator const &copy) 
                    {
                        this->_ptr = copy._ptr;
                        return(*this);
                    }
                    ~ConstReverseVectorIterator() {}
                    const value_type &operator*() const
                    {
                        return(*(this->_ptr));
                    }
                    const value_type &operator[](int n) const
                    {
                        return (*(*this + n));
                    }
            };
}