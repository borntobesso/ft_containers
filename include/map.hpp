/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:15:12 by soyoungjung       #+#    #+#             */
/*   Updated: 2022/12/12 12:00:02 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional> // std::less
#include <memory>
#include "pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"

namespace ft
{

	enum Color
	{
		RED,
		BLACK,
		DBLACK
	};

	template <typename T>
	struct RBnode
	{

		typedef T value_type;
		typedef Color color_type;

		value_type value;
		RBnode *parent;
		RBnode *left;
		RBnode *right;
		color_type color;

		RBnode() : value(), parent(NULL), left(NULL), right(NULL), color(RED) {}
		RBnode(const value_type &val, RBnode *parent = NULL, RBnode *left = NULL,
			   RBnode *right = NULL, color_type color = RED)
			: value(val), parent(parent), left(left), right(right), color(color) {}
		RBnode(const RBnode &rhs)
			: value(rhs.value), parent(rhs.parent), left(rhs.left), right(rhs.right), color(rhs.color) {}
		virtual ~RBnode() {}

		RBnode &operator=(const RBnode &rhs)
		{
			if (this == &rhs)
				return (*this);
			this->value = rhs.value;
			this->parent = rhs.parent;
			this->left = rhs.left;
			this->right = rhs.right;
			this->color = rhs.color;
			return (*this);
		}

		bool operator==(const RBnode &rhs)
		{
			return (this->value == rhs.value ? true : false);
		}

		bool operator!=(const RBnode &rhs)
		{
			return (!(*this == rhs));
		}
	}; // struct RBnode

	template <typename Key, typename T,
			  typename Compare = std::less<Key>,
			  typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef RBnode<value_type> node_type;

		/* binary_function struct serves as a base for classes that define
		a member function of the operator() */
		struct binary_function
		{
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
		};

		/* Provides a function object that can compare the elements of a map by
		comparing the values of their keys to determine their relative order in the map */
		class value_compare : public binary_function
		{
		public:
			key_compare comp;
			bool operator()(const value_type &left, const value_type &right) const
			{
				return (comp(left.first, right.first));
			}
			value_compare(key_compare c) : comp(c) {}
		};

	public:
		typedef typename allocator_type::template rebind<node_type>::other node_alloc_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename ft::bidirectional_iterator<value_type, node_type *> iterator;
		typedef typename ft::bidirectional_iterator<const value_type, node_type *> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// member variables
	private:
		key_compare _comp;
		allocator_type _alloc;
		size_type _size;
		node_alloc_type _node_alloc;
		node_type *_super_root;

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _size(0), _node_alloc(node_alloc_type()), _super_root(NULL)
		{
			_super_root = _node_alloc.allocate(1);
			_node_alloc.construct(_super_root, node_type());
		}

		template <typename InputIterator>
		map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _size(0), _node_alloc(node_alloc_type()), _super_root(NULL)
		{
			_super_root = _node_alloc.allocate(1);
			_node_alloc.construct(_super_root, node_type());
			insert(first, last);
		}

		map(const map &other)
			: _comp(other._comp), _alloc(other._alloc), _size(0), _node_alloc(other._node_alloc)
		{
			_super_root = _node_alloc.allocate(1);
			_node_alloc.construct(_super_root, node_type());
			_copyTree(other._getRoot());
		}

		~map()
		{
			clear();
			if (_super_root != NULL)
			{
				_node_alloc.destroy(_super_root);
				_node_alloc.deallocate(_super_root, 1);
			}
		}

		map &operator=(const map &rhs)
		{
			this->clear();
			this->_comp = rhs._comp;
			this->_alloc = rhs._alloc;
			this->_node_alloc = rhs._node_alloc;
			_copyTree(rhs._getRoot());
			this->_size = rhs._size;
			return (*this);
		}

		allocator_type get_allocator() const { return (this->_node_alloc); }

	private:
		// post-order delete-node
		void _deleteTree(node_type *node)
		{
			if (node != NULL)
			{
				_deleteTree(node->left);
				_deleteTree(node->right);
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}
		}

		// pre-order value-insert
		void _copyTree(node_type *node)
		{
			if (node != NULL)
			{
				_insertValue(node->value);
				_copyTree(node->left);
				_copyTree(node->right);
			}
		}

		node_type *_minValueNode(node_type *node) const
		{
			if (node == NULL)
				return (node);
			while (node->left != NULL)
				node = node->left;
			return (node);
		}

		node_type *_getRoot(void) const
		{
			return (_super_root->left);
		}

		void _setRoot(node_type *node) const
		{
			_super_root->left = node;
			_super_root->right = node;
			if (node != NULL)
				node->parent = _super_root;
		}

	public:
		// member function : Element access
		mapped_type &operator[](const key_type &key)
		{
			return (insert(ft::make_pair(key, mapped_type())).first->second);
		}

		mapped_type &at(const key_type &key)
		{
			iterator it = lower_bound(key);

			if (it == end() || _comp(key, (*it).first))
				throw(std::out_of_range("map::at"));
			return ((*it).second);
		}

		const mapped_type &at(const key_type &key) const
		{
			const_iterator it = lower_bound(key);

			if (it == end() || _comp(key, (*it).first))
				throw(std::out_of_range("map::at"));
			return ((*it).second);
		}

		// member function : Iterators
		iterator begin() { return (iterator(_minValueNode(_super_root))); }
		const_iterator begin() const { return (const_iterator(_minValueNode(_super_root))); }
		iterator end() { return (iterator(_super_root)); }
		const_iterator end() const { return (const_iterator(_super_root)); }
		reverse_iterator rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

		// member function : Capacity
		bool empty() const { return (this->_size == 0); }
		size_type size() const { return (this->_size); }
		size_type max_size() const { return (this->_node_alloc.max_size()); }

		// member function : Observers
		key_compare key_comp() const { return (this->_comp); }
		value_compare value_comp() const { return (value_compare(key_compare())); }

		// member function : Lookup
		size_type count(const key_type &key) const
		{
			const_iterator tmp = this->find(key);
			return (tmp == this->end() ? 0 : 1);
		}

		iterator find(const key_type &key)
		{
			node_type *tmp = _getRoot();
			while (tmp != NULL)
			{
				if (!_comp(tmp->value.first, key) && !_comp(key, tmp->value.first))
					break;
				else if (_comp(tmp->value.first, key))
					tmp = tmp->right;
				else
					tmp = tmp->left;
			}
			if (tmp == NULL)
				return (iterator(_super_root));
			return (iterator(tmp));
		}

		const_iterator find(const key_type &key) const
		{
			node_type *tmp = _getRoot();
			while (tmp != NULL)
			{
				if (!_comp(tmp->value.first, key) && !_comp(key, tmp->value.first))
					break;
				else if (_comp(tmp->value.first, key))
					tmp = tmp->right;
				else
					tmp = tmp->left;
			}
			if (tmp == NULL)
				return (const_iterator(_super_root));
			return (const_iterator(tmp));
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
		}

		iterator lower_bound(const key_type &key)
		{
			iterator it1 = begin();
			iterator it2 = end();

			while (it1 != it2)
			{
				if (_comp(it1->first, key) == false)
					break;
				++it1;
			}
			return (it1);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator it1 = begin();
			const_iterator it2 = end();

			while (it1 != it2)
			{
				if (_comp(it1->first, key) == false)
					break;
				++it1;
			}
			return (it1);
		}

		iterator upper_bound(const key_type &key)
		{
			iterator it1 = begin();
			iterator it2 = end();

			while (it1 != it2)
			{
				if (_comp(key, it1->first) == true)
					break;
				++it1;
			}
			return (it1);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator it1 = begin();
			const_iterator it2 = end();

			while (it1 != it2)
			{
				if (_comp(key, it1->first) == true)
					break;
				++it1;
			}
			return (it1);
		}

		// member function : Modifiers
		void clear()
		{
			_deleteTree(_getRoot());
			_setRoot(NULL);
			this->_size = 0;
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			return (_insertValue(val));
		}

		iterator insert(iterator pos, const value_type &val)
		{
			(void)pos;
			return (_insertValue(val).first);
		}

		template <typename InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				++first;
			}
		}

		void erase(iterator pos)
		{
			_eraseValue(pos->first);
		}

		void erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last;)
				erase(it++);
		}

		size_type erase(const key_type &key)
		{
			return (_eraseValue(key));
		}

		void swap(map &rhs)
		{
			node_alloc_type tmp_node_alloc = this->_node_alloc;
			key_compare tmp_comp = this->_comp;
			size_type tmp_size = this->_size;
			node_type *tmp_super_root = this->_super_root;

			this->_node_alloc = rhs._node_alloc;
			this->_comp = rhs._comp;
			this->_size = rhs._size;
			this->_super_root = rhs._super_root;

			rhs._node_alloc = tmp_node_alloc;
			rhs._comp = tmp_comp;
			rhs._size = tmp_size;
			rhs._super_root = tmp_super_root;
		}

	private:
		ft::pair<iterator, bool> _insertValue(const value_type &val)
		{
			node_type *node = _node_alloc.allocate(1);
			_node_alloc.construct(node, node_type(val));
			ft::pair<iterator, bool> ret = _insertNode(node);

			if (ret.second == false)
			{
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}
			else
			{
				this->_size++;
				_remedyDoubleRed(node);
			}
			return (ret);
		}

		ft::pair<iterator, bool> _insertNode(node_type *node)
		{
			node_type *tmp = _getRoot();
			node_type *parent;

			if (tmp == NULL)
			{
				_setRoot(node);
				return (ft::make_pair(iterator(node), true));
			}
			while (tmp)
			{
				if (_comp(tmp->value.first, node->value.first))
				{
					parent = tmp;
					tmp = tmp->right;
				}
				else if (_comp(node->value.first, tmp->value.first))
				{
					parent = tmp;
					tmp = tmp->left;
				}
				else
				{
					return (ft::make_pair(iterator(tmp), false));
				}
			}
			if (_comp(parent->value.first, node->value.first))
			{
				parent->right = node;
				node->parent = parent;
			}
			else
			{
				parent->left = node;
				node->parent = parent;
			}
			return (ft::make_pair(iterator(node), true));
		}

		/* insertion 4 scenarios :
			1. node == root
			2. node.uncle == RED
			3. node.uncle == BLACK, triangle
			4. node.uncle == BLACK, line
		*/
		void _remedyDoubleRed(node_type *node)
		{
			node_type *parent;
			node_type *grandparent;
			node_type *uncle;

			while (node != _getRoot() && _getColor(node) == RED && _getColor(_getParent(node)) == RED)
			{
				parent = _getParent(node);
				grandparent = _getGrandparent(node);
				uncle = _getUncle(node);

				if (_getColor(uncle) == RED) // case 2
					_redUncle(node);
				else if (grandparent->left == parent)
				{
					if (parent->right == node) // case 3
						_blackUncleTri(node, parent);
					_blackUncleLine(node, parent, grandparent); // case 4
				}
				else if (grandparent->right == parent)
				{
					if (parent->left == node) // case 3
						_blackUncleTri(node, parent);
					_blackUncleLine(node, parent, grandparent); // case 4
				}
			}
			_setColor(_getRoot(), BLACK); // case 1
		}

		// case 2 solution : recolor parent, uncle & grand-parent
		void _redUncle(node_type *&node)
		{
			_setColor(_getParent(node), BLACK);
			_setColor(_getUncle(node), BLACK);
			_setColor(_getGrandparent(node), RED);
			node = _getGrandparent(node);
		}

		// case 3 solution : rotate node's parent so that node takes its place
		void _blackUncleTri(node_type *&node, node_type *&parent)
		{
			if (parent == _getGrandparent(node)->left)
			{
				_rotateLeft(parent);
				node = parent;
				parent = _getParent(node);
			}
			else if (parent == _getGrandparent(node)->right)
			{
				_rotateRight(parent);
				node = parent;
				parent = _getParent(node);
			}
		}

		/* case 4 solution : rotate node's grand-parent in the opposite dir. of node
			so that node's parent takes place of node's grand-parent & recolor */
		void _blackUncleLine(node_type *&node, node_type *parent, node_type *grandparent)
		{
			if (parent == grandparent->left)
				_rotateRight(grandparent);
			else if (parent == grandparent->right)
				_rotateLeft(grandparent);
			std::swap(parent->color, grandparent->color);
			node = parent;
		}

		void _rotateLeft(node_type *&node)
		{
			node_type *rightChild = node->right; // set y

			if (rightChild == NULL)
				return;
			node->right = rightChild->left; // turn y's left-subtree into x's right-subtree
			if (node->right != NULL)
				node->right->parent = node;
			rightChild->parent = node->parent; // link x's parent to y's parent
			if (_getParent(node) == NULL)	   // in case x is root, set y to root
				_setRoot(rightChild);
			else if (node == node->parent->left) // else link node's parent's child to y
				node->parent->left = rightChild;
			else
				node->parent->right = rightChild;
			rightChild->left = node;   // finally, link y's left to x
			node->parent = rightChild; // and link x's parent to y
		}

		void _rotateRight(node_type *&node)
		{
			node_type *leftChild = node->left;

			if (leftChild == NULL)
				return;
			node->left = leftChild->right;
			if (node->left != NULL)
				node->left->parent = node;
			leftChild->parent = node->parent;
			if (_getParent(node) == NULL)
				_setRoot(leftChild);
			else if (node == node->parent->right)
				node->parent->right = leftChild;
			else
				node->parent->left = leftChild;
			leftChild->right = node;
			node->parent = leftChild;
		}

		size_type _eraseValue(const key_type &val)
		{
			node_type *target = _transplant(_getRoot(), val);
			if (target == NULL)
				return (0);
			_remedyDoubleBlack(target);
			this->_size--;
			return (1);
		}

		node_type *_transplant(node_type *node, const key_type &val)
		{
			if (node == NULL)
				return (node);
			// find delete position
			if (_comp(node->value.first, val))
				return (_transplant(node->right, val));
			else if (_comp(val, node->value.first))
				return (_transplant(node->left, val));
			/* delete 3 scenarios :
				1. left child is NULL
				2. right child is NULL
				3. neither child is NULL */
			if (node->left == NULL || node->right == NULL)
				return (node);
			// else : find the successor of Z
			node_type *successor = _minValueNode(node->right);
			// successor = node->right
			if (successor->parent == node)
			{
				if (node->parent && node->parent->left == node)
					node->parent->left = successor;
				else if (node->parent && node->parent->right == node)
					node->parent->right = successor;
				successor->left = node->left;
				node->left->parent = successor;
				node->left = NULL;
				successor->parent = node->parent;
				node->parent = successor;
				node->right = successor->right;
				successor->right = node;
				std::swap(successor->color, node->color);
			}
			else
			{
				if (node->parent && node->parent->left == node)
					node->parent->left = successor;
				else if (node->parent && node->parent->right == node)
					node->parent->right = successor;
				if (successor->parent->left == successor)
					successor->parent->left = node;
				else if (successor->parent->right == successor)
					successor->parent->right = node;
				node_type *x = successor->parent;
				node->right->parent = successor;
				successor->parent = node->parent;
				node->parent = x;
				successor->left = node->left;
				node->left->parent = successor;
				node->left = NULL;
				node_type *y = successor->right;
				successor->right = node->right;
				node->right = y;
				std::swap(successor->color, node->color);
			}
			return (_transplant(successor->right, val));
		}
		/*
		types of remedy double black
		1. w(z's sibling) is RED
		2. w is BLACK, and w.left & w.right are BLACK
		3. w is BLACK, and w.left is RED and w.right is BLACK
		4. w is BLACK, and w.right is RED
		-> it's not exclusive, may do more than one fix per invocation
		*/
		void _remedyDoubleBlack(node_type *node)
		{
			if (node == NULL)
				return;
			else if (node == _getRoot())
			{
				_eraseRootCase(node);
				return;
			}
			if (_getColor(node) == RED || _getColor(node->left) == RED || _getColor(node->right) == RED)
			{
				_eraseRedCase(node);
				return;
			}
			// w : sibling of Z, p : parent of Z
			node_type *w = NULL;
			node_type *p = NULL;
			node_type *z = node;

			_setColor(z, DBLACK);
			while (z != _getRoot() && _getColor(z) == DBLACK)
			{
				p = z->parent;
				w = (z == p->left) ? p->right : p->left;
				// type 1: sibling W is RED
				if (_getColor(w) == RED)
					_redSibling(w, p);
				// type 2 : w.right & w.left are all BLACK
				else if (_getColor(w->left) == BLACK && _getColor(w->right) == BLACK)
					_doubleBlackNephew(w, p, z);
				else
				{
					// type 3 : w.right is BLACK, w.left is RED
					if ((z == p->left && _getColor(w->right) == BLACK) || (z == p->right && _getColor(w->left) == BLACK))
						_blackRightNephew(w, p);
					// type 4 : w.right is RED
					_redRightNephew(w, p);
					break;
				}
			}
			if (node == node->parent->left)
				node->parent->left = NULL;
			else
				node->parent->right = NULL;
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			_setColor(_getRoot(), BLACK);
		}

		void _eraseRootCase(node_type *root)
		{
			if (root->right)
				_setRoot(root->right);
			else
				_setRoot(root->left);
			_node_alloc.destroy(root);
			_node_alloc.deallocate(root, 1);
			_setColor(_getRoot(), BLACK);
		}

		void _eraseRedCase(node_type *&node)
		{
			node_type *child = (node->left != NULL) ? node->left : node->right;
			if (node == node->parent->left)
				node->parent->left = child;
			else
				node->parent->right = child;
			if (child != NULL)
				child->parent = node->parent;
			_setColor(child, BLACK);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}

		// type 1 : sibling w is RED
		void _redSibling(node_type *&w, node_type *&p)
		{
			if (w == p->right)
				_rotateLeft(p);
			else if (w == p->left)
				_rotateRight(p);
			_setColor(w, BLACK);
			_setColor(p, RED);
		}

		// type 2 : w is BLACK, and w.left & w.right are BLACK
		void _doubleBlackNephew(node_type *w, node_type *p, node_type *&node)
		{
			_setColor(w, RED);
			if (_getColor(p) == RED)
				_setColor(p, BLACK);
			else
				_setColor(p, DBLACK);
			node = p;
		}

		// type 3 : w is BLACK, and w.left is RED and w.right is BLACK
		void _blackRightNephew(node_type *&w, node_type *&p)
		{
			if (w == p->right)
			{
				_rotateRight(w);
				_setColor(w->left, BLACK);
				_setColor(w, RED);
				w = p->right;
			}
			else if (w == p->left)
			{
				_rotateLeft(w);
				_setColor(w->right, BLACK);
				_setColor(w, RED);
				w = p->left;
			}
		}

		// type 4 : w is BLACK, and w.right is RED
		void _redRightNephew(node_type *&w, node_type *&p)
		{
			if (w == p->right)
			{
				_rotateLeft(p);
				_setColor(w, _getColor(p));
				_setColor(p, BLACK);
				_setColor(w->right, BLACK);
			}
			else if (w == p->left)
			{
				_rotateRight(p);
				_setColor(w, _getColor(p));
				_setColor(p, BLACK);
				_setColor(w->left, BLACK);
			}
		}

		node_type *_getParent(node_type *node) const
		{
			if (node == NULL)
				return (NULL);
			else if (node->parent == this->_super_root)
				return (NULL);
			return (node->parent);
		}

		node_type *_getGrandparent(node_type *node)
		{
			node_type *p = _getParent(node);

			if (p == NULL)
				return (NULL);
			return (_getParent(p));
		}

		node_type *_getUncle(node_type *node)
		{
			node_type *p = _getParent(node);

			if (p == NULL)
				return (NULL);
			return (_getSibling(p));
		}

		node_type *_getSibling(node_type *node)
		{
			node_type *p = _getParent(node);

			if (p == NULL)
				return (NULL);
			return ((node == p->left) ? p->right : p->left);
		}

		Color _getColor(node_type *node)
		{
			if (node == NULL)
				return (BLACK);
			return (node->color);
		}

		void _setColor(node_type *node, Color color)
		{
			if (node == NULL)
				return;
			node->color = color;
		}
	}; // class map

	// non-member functions
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs > rhs));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
