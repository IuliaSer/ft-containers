#include "Map.hpp"

namespace ft
{
    template<class T>
    struct node
    {
        T                        content;
        node*                    parent;
        node*                    left;
        node*                    right;
        size_t                   color;
        node() {}
        node(const node &A) 
        {
            this->parent = A.parent;
            this->left = A.left;
            this->right = A.right;
            this->content = A.content;
        }
    };

    template<class T>
    class MapIterator
    {

        public:
            typedef T                                       value_type;
            typedef MapIterator<value_type>                 iterator;
            typedef T&                                      reference;
            typedef T*                                      pointer;
            typedef node<T>*                                nodeptr;
        protected:
            nodeptr     _node;
        public:
            MapIterator(nodeptr node = 0) : _node(node) {}
            MapIterator(MapIterator const &copy) {*this = copy;}

            MapIterator &operator=(MapIterator const &copy) 
            {
                _node = copy._node;
                return(*this);
            }
            ~MapIterator() {}
            
            nodeptr getNode() const      { return _node; }

            MapIterator operator++(int) //post increment
            {
                MapIterator res(*this);
                operator++();
                return(res);
            }
            MapIterator operator--(int) //post decrement
            {
                MapIterator res(*this);
                operator--();
                return(res);
            }

            MapIterator &operator++() //pre increment
            {
                if(_node->right)
                {
                    _node = _node->right;
                    while (_node->left)
						_node = _node->left;
                }
                else
                {
                    while (_node->parent && _node->parent->parent && _node == _node->parent->right)
						 _node = _node->parent;
                    _node = _node->parent;
                }
                return(*this);
            }

            MapIterator &operator--()
            {
                if(_node->left)
                {
                    _node = _node->left;
                    while (_node->right)
						 _node = _node->right;
                }
                else 
                {
					while (_node->parent && _node == _node->parent->left)
						_node = _node->parent;
					_node = _node->parent;
                }   
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

            bool operator!=(const MapIterator &other) const 
            {
                return (_node != other._node);
            }
            bool operator==(const MapIterator &other) const 
            {
                return (_node == other._node);
            }
    };

        template <class T>
	        class ConstMapIterator : public MapIterator<T>
            {
                public:
                    typedef T                                       value_type;
                    typedef T&                                      reference;
                    typedef T*                                      pointer;
                    typedef node<T>*                                nodeptr;
                    ConstMapIterator(nodeptr node = 0) : MapIterator<T>(node) {}
                    ConstMapIterator(ConstMapIterator const &copy) : MapIterator<T>(copy) {}
                    ConstMapIterator(MapIterator<T> const &copy) : MapIterator<T>(copy) {}
                    ConstMapIterator &operator=(ConstMapIterator const &copy) 
                    {
                        this->_node = copy._node;
                        return(*this);
                    }
                    ~ConstMapIterator() {}
                    const value_type &operator*() const
                    {
                        return(this->_node->content);
                    }
            };

//___________________________referse_iterator__________________________//
    template<typename T>
    class ReverseMapIterator : public MapIterator<T>
    {
        protected:
            MapIterator<T> it;
        public:
            typedef node<T>*    nodeptr;
            typedef T           value_type;
            typedef T&          reference;
            typedef T*          pointer;
            ReverseMapIterator() {}
            ReverseMapIterator(MapIterator<T> it) { this->it = it; }
            ReverseMapIterator(ReverseMapIterator const &copy)
            {
                *this = copy;
            }
            
            ReverseMapIterator &operator=(ReverseMapIterator const &copy) 
            {
                this->_node = copy._node;
                this->it = copy.it;
                return(*this);
            }
            ~ReverseMapIterator() {}
            
            ReverseMapIterator operator++(int) //post increment
            {
                ReverseMapIterator temp = *this;
                this->operator++();
                return temp;
            }
            ReverseMapIterator operator--(int) //post decrement
            {
                ReverseMapIterator temp = *this;
                this->operator--();
                return temp;
            }
            ReverseMapIterator &operator++()
            {
                this->it--;
                return (*this);
            }
            ReverseMapIterator &operator--()
            {
                this->it++;
                return(*this);
            }

            reference operator*() const 
            {
                MapIterator<T> tmp = this->it;
                return (*(--tmp));
            }

            pointer operator->() const
            {
                return(&(this->operator*()));
            }

            bool operator!=(const ReverseMapIterator &other) const 
            {
                return (it != other.it);
            }
            bool operator==(const ReverseMapIterator &other) const 
            {
                return (it == other.it);
            }
        };
            

        template <class T>
	        class ConstReverseMapIterator : public ReverseMapIterator<T>
            {
                public:
                    typedef T           value_type;
                    typedef T&          reference;
                    typedef T*          pointer;
                    typedef ptrdiff_t 	difference_type;
                    ConstReverseMapIterator() {}
                    ConstReverseMapIterator(node<T> * ptr) : ReverseMapIterator<T>(ptr) {}
                    ConstReverseMapIterator(ConstReverseMapIterator const &copy) : ReverseMapIterator<T>(copy) {}
                    ConstReverseMapIterator(ReverseMapIterator<T> const &copy) : ReverseMapIterator<T>(copy) {}
                    ConstReverseMapIterator(ConstMapIterator<T> const &copy) : ReverseMapIterator<T>(copy) {}
                    ConstReverseMapIterator &operator=(ConstReverseMapIterator const &copy) 
                    {
                        this->_node = copy._node;
                        this->it = copy.it;
                        return(*this);
                    }
                    ~ConstReverseMapIterator() {}
                    const value_type &operator*() const
                    {
                        MapIterator<T> tmp = this->it;
                        return (*(--tmp));
                    }
            };
}