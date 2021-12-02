#include "List.hpp"

namespace ft
{
    template<typename T>
    struct node
            {
                T       content;
                node*   prev;
                node*   next;
            };

    template<typename T>
    class ListIterator
    {
        public:
            typedef T                        value_type;
            typedef T&                       reference;
            typedef T*                       pointer;
            typedef node<T>*                 nodeptr;
        protected:
            nodeptr     _node;
        public:
            ListIterator() {}
            ListIterator(nodeptr ptr) : _node(ptr) {}
            ListIterator(ListIterator const &copy) {*this = copy;}
            ListIterator &operator=(ListIterator const &copy) 
            {
                _node = copy._node;
                return(*this);
            }
            ~ListIterator() {}
            
            nodeptr getNode() const      { return _node; }
            ListIterator operator++(int) //post increment
            {
                ListIterator res(*this);
                _node = _node->next;
                return (res);
            }
            ListIterator operator--(int) //post decrement
            {
                ListIterator res(*this);
                _node = _node->prev;
                return (res);
            }
            ListIterator &operator++()
            {
                _node = _node->next;
                return(*this);
            }
            ListIterator &operator--()
            {
                _node = _node->prev;
                return(*this);
            }
            
            reference operator*() const
            {
                return(_node->content);
            }
            pointer operator->() const
            {
                return(&(_node->content));
            }
            //_______________
            bool operator!=(const ListIterator &other) const 
            {
                return (_node != other._node);
            }
            bool operator==(const ListIterator &other) const 
            {
                return (_node == other._node);
            }
    };

template <class T>
	        class ConstListIterator : public ListIterator<T>
            {
                public:
                    typedef node<T>*    nodeptr;
                    typedef T           value_type;
                    typedef T&          reference;
                    typedef T*          pointer;
                    typedef ptrdiff_t 	difference_type;
                    ConstListIterator() {}
                    ConstListIterator(nodeptr ptr)  {this->_node = ptr;}
                    ConstListIterator(ConstListIterator const &copy) {*this = copy;}
                    ConstListIterator(ListIterator<T> const &copy) : ListIterator<T>(copy) {}
                    ConstListIterator &operator=(ConstListIterator const &copy) 
                    {
                        this->_node = copy._node;
                        return(*this);
                    }
                    ~ConstListIterator() {}
                    const value_type &operator*() const
                    {
                        return(this->_node->content);
                    }
            };
//___________________________referse_iterator__________________________//
    template<typename T>
    class ReverseListIterator : public ListIterator<T>
    {
        public:
            typedef node<T>*    nodeptr;
            typedef T           value_type;
            typedef T&          reference;
            typedef T*          pointer;
            typedef ptrdiff_t 	difference_type;
            ReverseListIterator() {}
            ReverseListIterator(nodeptr ptr) : ListIterator<T>(ptr) {}
            ReverseListIterator(ReverseListIterator const &copy)
            {
                *this = copy;
            }
            
            ReverseListIterator &operator=(ReverseListIterator const &copy) 
            {
                ListIterator<T>::operator=(copy);
                return(*this);
            }
            ~ReverseListIterator() {}
            
            ReverseListIterator operator++(int) //post increment
            {
                ReverseListIterator temp = *this;
                this->_node = this->_node->prev;
                return temp;
            }
            ReverseListIterator operator--(int) //post decrement
            {
                ReverseListIterator temp = *this;
                this->_node = this->_node->next;
                return temp;
            }
            ReverseListIterator &operator++() //pre increment
            {
                this->_node = this->_node->prev;
                return (*this);
            }
            ReverseListIterator &operator--()
            {
                this->_node = this->_node->next;
                return(*this);
            }
            
            reference operator*() const
            {
                return(ListIterator<T>::_node->content);
            }
            pointer operator->() const
            {
                return(&(this->_node->content));
            }
        };
            
        

        template <class T>
	        class ConstReverseListIterator : public ReverseListIterator<T>
            {
                public:
                    typedef node<T>*    nodeptr;
                    typedef T           value_type;
                    typedef T&          reference;
                    typedef T*          pointer;
                    typedef ptrdiff_t 	difference_type;
                    ConstReverseListIterator() {}
                    ConstReverseListIterator(nodeptr ptr)
                    {
                        this->_node = ptr;
                    }
                    ConstReverseListIterator(ConstReverseListIterator const &copy) : ReverseListIterator<T>(copy) {}
                    ConstReverseListIterator(ReverseListIterator<T> const &copy) : ReverseListIterator<T>(copy) {}
                    ConstReverseListIterator &operator=(ConstReverseListIterator const &copy) 
                    {
                        this->_node = copy._node;
                        return(*this);
                    }
                    ~ConstReverseListIterator() {}
                    const value_type &operator*() const
                    {
                        return(this->_node->content);
                    }
            };
}