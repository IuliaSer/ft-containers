#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <memory>
#include "Map_iterator.hpp"
#include "AddStructs.hpp"
#include <utility>

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<Key, T> > > 
        class map
        {
            public:
                typedef Key                                                         key_type;
                typedef T                                                           mapped_type;
                typedef std::pair<key_type, mapped_type>                            value_type;
                typedef Compare                                                     key_compare;
                typedef Alloc                                                       allocator_type;
                typedef T&                                                          reference;
                typedef const T&                                                    const_reference;
                typedef T*                                                          pointer;
                typedef const T*                                                    const_pointer;
                typedef typename allocator_type::template rebind <node<value_type> >::other       node_alloc;
                typedef typename ft::MapIterator<value_type>                        iterator;
                typedef typename ft::ConstMapIterator<value_type>                   const_iterator;
                typedef typename ft::ReverseMapIterator<value_type>                 reverse_iterator;
                typedef typename ft::ConstReverseMapIterator<value_type>            const_reverse_iterator;
                typedef long int                                                    difference_type;
                typedef size_t                                                      size_type;
                typedef node<value_type>*                                           nodeptr;

                class value_compare
                {
                    friend class map;
                    protected:
                        key_compare comp;
                        value_compare(Compare c) : comp(c) {}
                    public:
                        typedef bool        result_type;
                        typedef value_type  first_argument_type;
                        typedef value_type  second_argument_type;
                        bool operator()(const value_type& x, const value_type& y) const
                        {
                            return comp(x.first, y.first);
                        }
                };
            private:
                size_type       _size;
                nodeptr         _root;
                nodeptr         _last;
                allocator_type  _alloc;
                node_alloc      _node_alloc;
                key_compare     _comp;
                
            public:
            //___________________________Helper_functions__________________________//
            nodeptr new_node(const value_type &val = value_type())
            {
                nodeptr tmp = _node_alloc.allocate(1);
                _alloc.construct(&tmp->content, val);
                tmp->left = NULL;
                tmp->right = NULL;
                tmp->parent = NULL;
                tmp->color = 1;
                return (tmp);
            }

            void leftRotate(nodeptr x)
            {
                nodeptr y = x->right;
                x->right = y->left;
                if (y->left != NULL)
                    y->left->parent = x;
                y->parent = x->parent;
                if (x->parent == nullptr)
                    this->_root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
            }

            void rightRotate(nodeptr x) {
                nodeptr y = x->left;
                x->left = y->right;
                if (y->right != NULL)
                    y->right->parent = x;
                y->parent = x->parent;
                if (x->parent == nullptr)
                    this->_root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
                y->right = x;
                x->parent = y;
            }
            
            nodeptr insertNode(const value_type& val)
            {
                if(_size > 0)
                {
                    iterator it = find(val.first);
                    if (it != end())
                        return it.getNode();
                }
                nodeptr node;
                node = new_node(val);
                nodeptr y = nullptr;
                nodeptr x = _root;
                while (x != NULL && x != _last)
                {
                    y = x;
                    if (node->content.first < x->content.first)
                        x = x->left;
                    else
                        x = x->right;
                }
                node->parent = y;
                if (y == nullptr)
                {
                    _root = node;
                    y = node;
                    y->right = _last;
                    _last->parent = y;
                }
                else if (node->content.first < y->content.first)
                {
                    y->left = node;
                    y = y->left;
                }
                else
                {
                    y->right = node;
                    y = y->right;
                    if(y && y->content.first > _last->parent->content.first)
                    {
                        y->right = _last;
                        _last->parent = y;
                    }
                }
                _size++;
                node->color = 1;
                return node;
            }

            nodeptr insertNode(const value_type& val, nodeptr x)
            {
                if(_size > 0)
                {
                    iterator it = find(val.first);
                    if (it != end())
                        return it.getNode();
                }
                nodeptr node;
                node = new_node(val);
                nodeptr y = nullptr;
                while (x != NULL && x != _last)
                {
                    y = x;
                    if (node->content.first < x->content.first)
                        x = x->left;
                    else
                        x = x->right;
                }
                node->parent = y;
                if (y == nullptr)
                {
                    _root = node;
                    y = node;
                    y->right = _last;
                    _last->parent = y;
                }
                else if (node->content.first < y->content.first)
                {
                    y->left = node;
                    y = y->left;
                }
                else
                {
                    y->right = node;
                    y = y->right;
                    if(y && y->content.first > _last->parent->content.first)
                    {
                        y->right = _last;
                        _last->parent = y;
                    }
                }
                _size++;
                node->color = 1;
                return node;
            }
            void insertFix(nodeptr k)
            {
                nodeptr u;
                while (_size > 1 && k->parent && k->parent->color == 1)
                {
                    if (k->parent == k->parent->parent->right)
                    {
                        u = k->parent->parent->left;
                        if (u && u->color == 1)
                        {
                            u->color = 0;
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            k = k->parent->parent;
                        } 
                        else
                        {
                            if (k == k->parent->left) 
                            {
                                k = k->parent;
                                rightRotate(k);
                            }
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            leftRotate(k->parent->parent);
                        }
                    } 
                    else 
                    {
                        u = k->parent->parent->right;
                        if (u->color == 0)
                        {
                            u->color = 0;
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            k = k->parent->parent;
                        }
                        else
                        {
                            if (k == k->parent->right)
                            {
                                k = k->parent;
                                leftRotate(k);
                            }
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            rightRotate(k->parent->parent);
                        }
                    }
                    if (k == _root)
                        break;
                }
                _root->color = 0;
            }

            void change_ptrs(nodeptr u, nodeptr v) 
            {
                if (u->parent == nullptr)
                    _root = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;
                if (v != NULL)
                    v->parent = u->parent;
            }

            void deleteFix(nodeptr x) 
            {
                nodeptr s;
                while (x != _root && x->color == 0) 
                {
                    if (x == x->parent->left) 
                    {
                        s = x->parent->right;
                        if (s->color == 1) 
                        {
                            s->color = 0;
                            x->parent->color = 1;
                            leftRotate(x->parent);
                            s = x->parent->right;
                        }
                        if (s->left->color == 0 && s->right->color == 0) 
                        {
                            s->color = 1;
                            x = x->parent;
                        } 
                        else 
                        {
                            if (s->right->color == 0) 
                            {
                                s->left->color = 0;
                                s->color = 1;
                                rightRotate(s);
                                s = x->parent->right;
                            }
                            s->color = x->parent->color;
                            x->parent->color = 0;
                            s->right->color = 0;
                            leftRotate(x->parent);
                            x = _root;
                        }
                    } 
                    else 
                    {
                        s = x->parent->left;
                        if (s->color == 1) 
                        {
                            s->color = 0;
                            x->parent->color = 1;
                            rightRotate(x->parent);
                            s = x->parent->left;
                        }

                        if (s->right->color == 0 && s->right->color == 0) 
                        {
                            s->color = 1;
                            x = x->parent;
                        } 
                        else 
                        {
                            if (s->left->color == 0) 
                            {
                                s->right->color = 0;
                                s->color = 1;
                                leftRotate(s);
                                s = x->parent->left;
                            }

                            s->color = x->parent->color;
                            x->parent->color = 0;
                            s->left->color = 0;
                            rightRotate(x->parent);
                            x = _root;
                        }
                    }
                }
                x->color = 0;
            }
            void deleteNode(nodeptr node)
            {
                if (node == NULL)
                    return;
                mapped_type key = node->content.first;
                nodeptr z = NULL;
                nodeptr x, y;
                while (node != NULL)
                {
                    if (node->content.first == key)
                        z = node;
                    if (node->content.first <= key)
                        node = node->right;
                    else 
                        node = node->left;
                }
                if (z == NULL)
                    return;
                y = z;
                int y_original_color = y->color;
                if (z->left == NULL) 
                {
                    x = z->right;
                    change_ptrs(z, z->right);
                } 
                else if (z->right == NULL) 
                {
                    x = z->left;
                    change_ptrs(z, z->left);
                } 
                else 
                {
                    y = z->right;
                    while(y->left != NULL)
                        y = y->left;
                    y_original_color = y->color;
                    x = y->right;
                    if (y->parent == z)
                        x->parent = y;
                    else 
                    {
                        change_ptrs(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    change_ptrs(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                    if (y_original_color == 0)
                        deleteFix(x);
                }
                _node_alloc.deallocate(z, 1);
                _size--;
            }

            
            //_____________________Constructors, destructor and assignment operator________________//
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                _last = new_node();
                _root = NULL;
                _comp = comp;
                _alloc = alloc;
                _size = 0;
            }

            template <class InputIterator>
                map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type())
            {
                _last = new_node();
                _root = NULL;
                _comp = comp;
                _alloc = alloc;
                _size = 0;
                insert(first, last);
            }

            map (const map& x)
            {
                _last = new_node();
                _root = NULL;
                _comp = x._comp;
                _alloc = x._alloc;
                _size = 0;
                for (const_iterator it = x.begin(); it != x.end(); ++it)
                    insert(*it);
            }

            map& operator=(const map& x)
            {
                map tmp(x);
                this->swap(tmp);
                return *this;
            }

            ~map()
            {
                if (_size > 0)
                    erase(begin(), end());
                _node_alloc.deallocate(_last, 1);
            }

            //__________________________Element_access__________________________________//

            mapped_type& operator[] (const key_type& key)
            {  
                return (*((this->insert(std::make_pair(key, mapped_type()))).first)).second;
            }

            //_____________________Modifiers____________________________//

            std::pair<iterator, bool> insert (const value_type& val)
            {
                nodeptr node;
                node = insertNode(val, _root);
                insertFix(node);
                return(std::make_pair<iterator, bool>(iterator(node), true));
            }
            
            iterator insert (iterator position, const value_type& val)
            {
                if (position != begin() && position->first > val.first)
                {
                    iterator prev(position);
                    --prev;
                    while (prev != begin() && prev->first >= val.first)
                    {
                        --position;
                        --prev;
                    }
                }
                else if (position != end() && position->first < val.first)
                {
                    iterator next(position);
                    ++next;
                    while (next != end() && next->first <= val.first)
                    {
                        ++position;
                        ++next;
                    }
                }
                nodeptr node = insertNode(val, position.getNode());
                insertFix(node);
                return(iterator(node));
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
            {
                while (first != last)
                    insert(*first++);
            }

            void erase (iterator position)
            {
                deleteNode(position.getNode());
            }

            size_type erase (const key_type& k)
            {
                iterator it = find(k);
                if (it != end())
                {
                    deleteNode(it.getNode());
                    return 1;
                }
                return 0;
            }

            void erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    deleteNode(first.getNode());
                    ++first;
                }
            }

            void swap (map& x)
            {
                if (this != &x)
                {
                    nodeptr tmp = _root;
                    size_type tmp_size = this->_size;
                    allocator_type tmp_alloc = this->_alloc;
                    node_alloc tmp_node_alloc = this->_node_alloc;
                    nodeptr tmp_last = _last;
                    key_compare tmp_comp = _comp;
                    this->_root = x._root;
                    this->_size = x._size;
                    this->_alloc = x._alloc;
                    this->_node_alloc = x._node_alloc;
                    this->_last = x._last;
                    this->_comp = x._comp;
                    x._root = tmp;
                    x._size = tmp_size;
                    x._alloc = tmp_alloc;
                    x._node_alloc = tmp_node_alloc;
                    x._last = tmp_last;
                    x._comp = tmp_comp;
                }
            }

            void clear()
            {
                if(_size != 0)
                    erase(begin(), end());
            }
            //____________________________Operations________________________________//

            size_type count (const key_type& k) const
            {
                iterator it = begin();
                iterator ite = end();
                while(it != ite)
                {
                    if(it.getNode()->content.first == k)
                        return 1;
                    ++it;
                }
                return 0;
            }

            iterator lower_bound (const key_type& k)
            {
                iterator it = begin();
                while(it != end())
                {
                    if(!_comp(it->first, k))
                        return(it);
                    ++it;
                }
                return(it);
            }

            const iterator lower_bound (const key_type& k) const
            {
                const_iterator it = begin();
                while(it != end())
                {
                    if(!_comp(it->first, k))
                        return(it);
                    ++it;
                }
                return(it);
            }

            iterator upper_bound (const key_type& k)
            {
                iterator it = begin();
                while(it != end())
                {
                    if(_comp(k, it->first))
                        return(it);
                    ++it;
                }
                return(it);
            }

            const_iterator upper_bound (const key_type& k) const
            {
                const_iterator it = begin();
                while(it != end())
                {
                    if(_comp(k, it->first))
                        return(it);
                    ++it;
                }
                return(it);
            }
            
            std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                const_iterator it = lower_bound(k);
                const_iterator it2 = upper_bound(k);
                return std::make_pair<const_iterator, const_iterator>(it, it2);
            }
            std::pair<iterator,iterator>             equal_range (const key_type& k)
            {
                iterator it = lower_bound(k);
                iterator it2 = ++it;
                return std::make_pair<iterator, iterator>(it, it2);
            }

            iterator find (const key_type& k)
            {
                iterator it = begin();
                iterator ite = end();
                while(it != ite)
                {
                    if(it.getNode()->content.first == k)
                        return it;
                    ++it;
                }
                return ite;
            }
            const iterator find (const key_type& k) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while(it != ite)
                {
                    if(it.getNode()->content.first == k)
                        return it;
                    ++it;
                }
                return ite;
            }
            //_____________________________Capacity_________________________________//

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

            //_______________________________Observers__________________________________//

            key_compare key_comp() const        { return _comp; }

            value_compare value_comp() const    { return value_compare(_comp); }

            //_______________________________Iterators__________________________________//

            iterator begin()
            {
                nodeptr node = _root;
                while(node && node->left)
                    node = node->left;
                return (iterator(node)); 
            }

            const_iterator begin() const
            {
                nodeptr node = _root;
                while(node->left)
                    node = node->left;
                return (const_iterator(node)); 
            }

            iterator end() { return iterator(_last); }

            const_iterator  end() const  { return const_iterator(_last); }

            reverse_iterator rbegin()
            {
                iterator it = end();
                return reverse_iterator(it); 
            }

            const_reverse_iterator rbegin() const
            {
                iterator it = end();
                return const_reverse_iterator(it.getNode()); 
            }

            reverse_iterator rend()                 
            {
                reverse_iterator rit = begin();
                return (rit);
            }

            const_reverse_iterator rend() const     
            {
                const_reverse_iterator rit = begin();
                return (rit);
            }
        };
}

#endif