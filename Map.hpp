/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:05:15 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/26 12:52:48 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

namespace ft {

	template <class Key, class T, class Cmp, class Alloc>
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef Cmp key_compare;
			typedef Alloc allocator_type;
			typedef std::pair<const key_type, mapped_type> value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;

			class value_compare
			{
				private:
					value_compare() {}
					key_compare comp;
				public:
					typedef bool result_type;
					typedef std::pair<const Key, T> first_argument_type;
					typedef std::pair<const Key, T> second_argument_type;
					value_compare(const value_compare &o) : comp(o.comp) {}
					value_compare(const key_compare &c) : comp(c) {}
					value_compare &operator=(const value_compare &other) 
					{
						comp = other.comp;
						return *this;
					}
					~value_compare() {}
					bool operator()(const std::pair<const Key, T>& a, const std::pair<const Key, T>& b) const
					{
						return comp(a.first, b.first);
					}
			};
			
		protected:
		
			typedef ft::map_node<value_type> Node;
						
			typedef typename Alloc::template rebind<Node>::other node_alloc;

			template <typename U, bool is_const>
			class avl_iterator : public base_avl_iterator<U, is_const>
			{
				protected:
					using base_avl_iterator<U, is_const>::ptr;
					using base_avl_iterator<U, is_const>::get;
					using base_avl_iterator<U, is_const>::get_next;
					using base_avl_iterator<U, is_const>::get_prev;
				public:
					typedef U value_type;
					typedef typename choose<is_const, const U&, U&>::type reference;
					typedef typename choose<is_const, const U*, U*>::type pointer;
					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;
					typedef typename remove_const<U>::type non_const_type;
					typedef avl_iterator<non_const_type, false> non_const_iterator;
					
					avl_iterator() : base_avl_iterator<U, is_const>() {}
					avl_iterator(Node* ptr, Node* const* tree)
						: base_avl_iterator<U, is_const>(ptr, tree) {}
					avl_iterator(const base_avl_iterator<non_const_type, false>& it)
						: base_avl_iterator<U, is_const>(it.ptr) {}
					avl_iterator(const non_const_iterator& target)
						: base_avl_iterator<U, is_const>(target) {}
					using base_avl_iterator<U, is_const>::operator=;
					~avl_iterator() {}
			};
			
			template <typename I>
			class avl_reverse_iterator : public base_reverse_iterator<I>
			{
				private:
					using base_reverse_iterator<I>::itbase;
					typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;
				public:
					avl_reverse_iterator()
						: base_reverse_iterator<I>() {}
					avl_reverse_iterator(const avl_reverse_iterator<non_const_iterator>& it)
						: base_reverse_iterator<I>(it) {}
					avl_reverse_iterator(const base_reverse_iterator<I>& rev_it)
						: base_reverse_iterator<I>(rev_it.itbase) {}
					using base_reverse_iterator<I>::operator=;
					~avl_reverse_iterator() {}
			};

			template <typename U, bool is_const>
			inline const base_avl_iterator<U, is_const>& bcast(const avl_iterator<U, is_const>& it) const
			{
				return *(base_avl_iterator<U, is_const>*)&it;
			}
			
		public:
		
			typedef avl_iterator<value_type, false> iterator;
			typedef avl_iterator<const value_type, true> const_iterator;
			typedef avl_reverse_iterator<iterator> reverse_iterator;
			typedef avl_reverse_iterator<const_iterator> const_reverse_iterator;
			
			explicit map(const key_compare& comp = key_compare());
			template <typename I>
			map(I first, I last, const key_compare& comp = key_compare());
			map(const map& other);
			map<Key, T, Cmp, Alloc>& 	operator=(const map<Key, T, Cmp, Alloc>& target);
			~map();

			const_iterator								begin() const;
			iterator									begin();

			const_iterator								end() const;
			iterator									end();

			const_reverse_iterator						rbegin() const;
			reverse_iterator							rbegin();

			const_reverse_iterator 						rend() const;
			reverse_iterator							rend();

			std::pair<iterator,bool>					insert (const value_type& val);
			iterator									insert (iterator position, const value_type& val);
			template <class I>
			void insert (I first, I last);

			void										erase(iterator position);
			size_type									erase(const key_type& k);
			void										erase(iterator first, iterator last);

			bool										empty() const;
			size_type									size() const;
			size_type									max_size() const;

			void										swap(map<Key, T, Cmp, Alloc>& x);

			void										clear();

			key_compare									key_comp() const;
			value_compare								value_comp() const;

			iterator									find(const key_type& k);
			const_iterator								find(const key_type& k) const;

			size_type									count(const key_type& k) const;

			iterator									lower_bound (const key_type& k);
			const_iterator								lower_bound (const key_type& k) const;

			iterator									upper_bound (const key_type& k);
			const_iterator								upper_bound (const key_type& k) const;

			std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
			std::pair<iterator,iterator>             	equal_range (const key_type& k);

			mapped_type&								operator[](const key_type& key);
			
		protected:

			Node*						tree;
			size_type					m_size;
			key_compare					m_comp;
			allocator_type				m_alloc;

			const Node*					get();
			bool						key_equal(Key lhs, Key rhs) const;
			Node*						find_node(Node* root, const key_type& key) const;
			mapped_type&				get_mapped(Node* root, const key_type& key, bool force);

			void						link_left(Node* parent, Node* child);
			void						link_right(Node* parent, Node* child);
			int							set_heights(Node* root);
			std::pair<iterator, bool> 	insert_node(Node* root, Key key, T val, bool force = false);
			std::pair<Node*, bool>		recursive_insert(Node* root, Key key, T val, bool force = false);
			size_type					delete_node(Key key);
			Node*						recursive_extract(Node* parent, Node* root, Key key);
			int							readjust_heights(Node* node, Key key);
			void						update_node_height(Node* node);
			void						rebalance_tree(Node* parent, Node* node, Key key);
			void						left_rotate(Node* root, Node* node, Key key);
			void						right_rotate(Node* root, Node* node, Key key);
			bool						is_balanced(Node* root);

			void						print();
			void						print_root(const Node* root);
			void						free_tree(Node*& root);
	};
	

	



	//  dP""b8 888888  dP"Yb  88""Yb    dP 8888b.  888888  dP"Yb  88""Yb 
	// dP   `"   88   dP   Yb 88__dP   dP   8I  Yb   88   dP   Yb 88__dP 
	// Yb        88   Yb   dP 88"Yb   dP    8I  dY   88   Yb   dP 88"Yb  
	//  YboodP   88    YbodP  88  Yb dP    8888Y"    88    YbodP  88  Yb
	

	template <class Key, class T, class Cmp, class Alloc>
	map<Key, T, Cmp, Alloc>::map(const key_compare& comp)
		: tree(nullptr), m_size(0), m_comp(comp), m_alloc(allocator_type()) {}

	template <class Key, class T, class Cmp, class Alloc>
	template <typename I>
	map<Key, T, Cmp, Alloc>::map(I first, I last, const key_compare& comp)
		:  tree(nullptr), m_size(0), m_comp(comp), m_alloc(allocator_type())
	{
		for (I it = first; it != last; ++it)
			insert_node(tree, it->first, it->second, false);
	}

	template <class Key, class T, class Cmp, class Alloc>
	map<Key, T, Cmp, Alloc>::map(const map& other)
		: tree(nullptr), m_size(0), m_comp(other.m_comp), m_alloc(other.m_alloc)
	{
		*this = other;
	}

	template <class Key, class T, class Cmp, class Alloc>
	map<Key, T, Cmp, Alloc>& 	map<Key, T, Cmp, Alloc>::operator=(const map<Key, T, Cmp, Alloc>& target)
	{
		free_tree(tree);
		m_size = 0;
		m_comp = target.m_comp;
		for (map<Key, T, Cmp, Alloc>::const_iterator it = target.begin(); it != target.end(); ++it)
			insert_node(tree, it->first, it->second, false);
		return (*this);
	}

	template <class Key, class T, class Cmp, class Alloc>
	map<Key, T, Cmp, Alloc>::~map() { free_tree(tree); }
	
	


	// 8b    d8 888888 8b    d8 88""Yb 888888 88""Yb     888888 88   88 88b 88  dP""b8 .dP"Y8 
	// 88b  d88 88__   88b  d88 88__dP 88__   88__dP     88__   88   88 88Yb88 dP   `" `Ybo." 
	// 88YbdP88 88""   88YbdP88 88""Yb 88""   88"Yb      88""   Y8   8P 88 Y88 Yb      o.`Y8b 
	// 88 YY 88 888888 88 YY 88 88oodP 888888 88  Yb     88     `YbodP' 88  Y8  YboodP 8bodP' 


	// BEGIN
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_iterator	map<Key, T, Cmp, Alloc>::begin() const
	{
		Node* it = tree;
		while (it && it->left)
			it = it->left;
		return (const_iterator(it, &tree));
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::iterator	map<Key, T, Cmp, Alloc>::begin()
	{
		Node* it = tree;
		while (it && it->left)
			it = it->left;
		return (iterator(it, &tree));
	}

	// END
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_iterator	map<Key, T, Cmp, Alloc>::end() const
	{
		return (const_iterator(nullptr, &tree));
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::iterator	map<Key, T, Cmp, Alloc>::end()
	{
		return (iterator(nullptr, &tree));
	}

	// RBEGIN
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_reverse_iterator map<Key, T, Cmp, Alloc>::rbegin() const
	{
		return const_reverse_iterator(end());
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::reverse_iterator map<Key, T, Cmp, Alloc>::rbegin()
	{
		return reverse_iterator(end());
	}

	// REND
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_reverse_iterator	map<Key, T, Cmp, Alloc>::rend() const
	{
		return const_reverse_iterator(begin());
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::reverse_iterator	map<Key, T, Cmp, Alloc>::rend()
	{
		return reverse_iterator(begin());
	}

	// INSERT
	template <class Key, class T, class Cmp, class Alloc>
	std::pair<typename map<Key, T, Cmp, Alloc>::iterator, bool>
	map<Key, T, Cmp, Alloc>::insert(const typename map<Key, T, Cmp, Alloc>::value_type& val)
	{
		return insert_node(tree, val.first, val.second, false);
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::iterator
	map<Key, T, Cmp, Alloc>::insert(typename map<Key, T, Cmp, Alloc>::iterator position,
									const typename map<Key, T, Cmp, Alloc>::value_type& val)
	{
		Node* pos_ptr = bcast(position).ptr;
		iterator nextpos(ft::fwd(position, 1));
		bool current_next_is_end = (nextpos == end());
		// 3 cases:
		// -> position is a valid hint and would directly precede val: insert from position node down to optimize
		// -> val key = successor's key, just return the successor
		// -> otherwise insert and return the iterator
		if (pos_ptr && m_comp(position->first, val.first)
			&& (current_next_is_end || m_comp(val.first, nextpos->first)))
			return insert_node(pos_ptr, val.first, val.second, false).first;
		else if (!current_next_is_end && key_equal(val.first, nextpos->first))
			return nextpos;
		else
			return insert(val).first;
	}

	template <class Key, class T, class Cmp, class Alloc>
	template <class I>
	void map<Key, T, Cmp, Alloc>::insert(I first, I last)
	{
		for (I it = first; it != last; ++it)
			insert_node(tree, it->first, it->second, false);
	}

	// ERASE
	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::erase(iterator position)
	{
		delete_node(position->first);
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::size_type		map<Key, T, Cmp, Alloc>::erase(const key_type& k)
	{
		return delete_node(k);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::erase(iterator first, iterator last)
	{
		iterator it = first;
		while (it != last)
		{
			iterator successor = ft::fwd(it, 1);
			erase(it);
			it = successor;
		}
	}

	// EMPTY
	template <class Key, class T, class Cmp, class Alloc>
	bool	map<Key, T, Cmp, Alloc>::empty() const
	{
		return (!m_size);
	}

	// SIZE
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::size_type		map<Key, T, Cmp, Alloc>::size() const
	{
		return (m_size);
	}

	// MAX SIZE
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::size_type		map<Key, T, Cmp, Alloc>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(Node));
	}

	// SWAP
	template <class Key, class T, class Cmp, class Alloc>
	void map<Key, T, Cmp, Alloc>::swap(map<Key, T, Cmp, Alloc>& x)
	{
		std::swap(tree, x.tree);
		std::swap(m_size, x.m_size);
	}

	// CLEAR
	template <class Key, class T, class Cmp, class Alloc>
	void map<Key, T, Cmp, Alloc>::clear()
	{
		free_tree(tree);
		m_size = 0;
	}

	// KEY_COMP
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::key_compare	map<Key, T, Cmp, Alloc>::key_comp() const
	{
		return (m_comp);
	}

	// VALUE_COMP
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::value_compare map<Key, T, Cmp, Alloc>::value_comp() const
	{
		return (value_compare(m_comp));
	}

	// FIND
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::iterator map<Key, T, Cmp, Alloc>::find(const key_type& k)
	{
		Node* node = find_node(tree, k);
		
		if (node)
			return iterator(node, &tree);
		else
			return end();
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_iterator map<Key, T, Cmp, Alloc>::find(const key_type& k) const
	{
		Node* node = find_node(tree, k);
		
		if (node)
			return const_iterator(node, &tree);
		else
			return end();
	}

	// COUNT
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::size_type map<Key, T, Cmp, Alloc>::count(const key_type& k) const
	{
		Node* node = find_node(tree, k);
		return (node ? 1 : 0);
	}

	// LOWER BOUND
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::iterator map<Key, T, Cmp, Alloc>::lower_bound (const key_type& k)
	{
		iterator beg = this->begin();
		iterator end = this->end();
		for (iterator it = beg; it != end; ++it)
			if (!m_comp(it->first, k))
				return it;
		return end;
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_iterator map<Key, T, Cmp, Alloc>::lower_bound(const key_type& k) const
	{
		const_iterator beg(this->begin());
		const_iterator end(this->end());
		for (const_iterator it = beg; it != end; ++it)
			if (!m_comp(it->first, k))
				return it;
		return end;
	}

	// UPPER BOUND
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::iterator map<Key, T, Cmp, Alloc>::upper_bound(const key_type& k)
	{
		iterator beg = this->begin();
		iterator end = this->end();
		for (iterator it = beg; it != end; ++it)
			if (m_comp(k, it->first))
				return it;
		return end;
	}
	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::const_iterator map<Key, T, Cmp, Alloc>::upper_bound(const key_type& k) const
	{
		const_iterator beg = this->begin();
		const_iterator end = this->end();
		for (const_iterator it = beg; it != end; ++it)
			if (m_comp(k, it->first))
				return it;
		return end;
	}

	// EQUAL RANGE
	template <class Key, class T, class Cmp, class Alloc>
	std::pair<typename map<Key, T, Cmp, Alloc>::const_iterator, typename map<Key, T, Cmp, Alloc>::const_iterator>
	map<Key, T, Cmp, Alloc>::equal_range(const key_type& k) const
	{
		return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
	template <class Key, class T, class Cmp, class Alloc>
	std::pair<typename map<Key, T, Cmp, Alloc>::iterator, typename map<Key, T, Cmp, Alloc>::iterator>
	map<Key, T, Cmp, Alloc>::equal_range(const key_type& k)
	{
		return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::mapped_type&	map<Key, T, Cmp, Alloc>::operator[](const key_type& k)
	{
		Node* find = find_node(tree, k);
		if (!find)
			return insert_node(tree, k, mapped_type(), true).first->second;
		else
			return find->pair.second;
	}
	

	// 88 888888 888888 88""Yb    db    888888  dP"Yb  88""Yb .dP"Y8 
	// 88   88   88__   88__dP   dPYb     88   dP   Yb 88__dP `Ybo." 
	// 88   88   88""   88"Yb   dP__Yb    88   Yb   dP 88"Yb  o.`Y8b 
	// 88   88   888888 88  Yb dP""""Yb   88    YbodP  88  Yb 8bodP' 
	


	// 888888  dP"Yb   dP"Yb  88     .dP"Y8 
	//   88   dP   Yb dP   Yb 88     `Ybo.
	//   88   Yb   dP Yb   dP 88       `Y8b 
	//   88    YbodP   YbodP  88ood8 8bodP' 


	template <class Key, class T, class Cmp, class Alloc>
	void					map<Key, T, Cmp, Alloc>::link_left
	(typename map<Key, T, Cmp, Alloc>::Node* parent, typename map<Key, T, Cmp, Alloc>::Node* child)
	{
		if (parent)
			parent->left = child;
		if (child)
			child->parent = parent;
	}
	
	template <class Key, class T, class Cmp, class Alloc>
	void					map<Key, T, Cmp, Alloc>::link_right
	(typename map<Key, T, Cmp, Alloc>::Node* parent, typename map<Key, T, Cmp, Alloc>::Node* child)
	{
		if (parent)
			parent->right = child;
		if (child)
			child->parent = parent;
	}

	template <class Key, class T, class Cmp, class Alloc>
	bool					map<Key, T, Cmp, Alloc>::key_equal(Key lhs, Key rhs) const
	{
		return (!m_comp(lhs, rhs) && !m_comp(rhs, lhs));
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::Node*	map<Key, T, Cmp, Alloc>::find_node(Node* root, const key_type& key) const
	{
		if (!root)
			return nullptr;
		if (key_equal(root->pair.first, key))
			return root;
		if (m_comp(key, root->pair.first))
			return find_node(root->left, key);
		else
			return find_node(root->right, key);
	}

	template <class Key, class T, class Cmp, class Alloc>
	std::pair<typename map<Key, T, Cmp, Alloc>::Node*, bool>
	map<Key, T, Cmp, Alloc>::recursive_insert(Node* root, Key key, T val, bool force)
	{
		if (!root)
		{
			Node* new_node = node_alloc(m_alloc).allocate(1);
			node_alloc(m_alloc).construct(new_node, Node(std::pair<const Key, T>(key, val)));
			return std::pair<Node*, bool>(new_node, true);
		}

		if (m_comp(key, root->pair.first))
		{
			if (!root->left)
			{
				std::pair<Node*, bool> pair(recursive_insert(root->left, key, val, force));
				link_left(root, pair.first);
				return pair;
			}
			return recursive_insert(root->left, key, val, force);
		}
		else if (m_comp(root->pair.first, key))
		{
			if (!root->right)
			{
				std::pair<Node*, bool> pair(recursive_insert(root->right, key, val, force));
				link_right(root, pair.first);
				return pair;
			}
			return recursive_insert(root->right, key, val, force);
		}
		else
		{
			if (force)
				root->pair.second = val;
			return std::pair<Node*, bool>(root, false);
		}
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename std::pair<typename map<Key, T, Cmp, Alloc>::iterator, bool> 
	map<Key, T, Cmp, Alloc>::insert_node(Node* root, Key key, T val, bool force)
	{
		std::pair<Node*, bool> node_pair = recursive_insert(root, key, val, force);
		if (!tree)
			tree = node_pair.first;
		readjust_heights(tree, key);
		rebalance_tree(nullptr, tree, key);
		if (node_pair.second)
			++m_size;
		return std::pair<iterator, bool>
		(iterator(node_pair.first, &tree), node_pair.second);
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::size_type	map<Key, T, Cmp, Alloc>::delete_node(Key key)
	{
		Node* node = find_node(tree, key);
		if (!node)
			return (0);
		iterator successor(node, &tree);
		++successor;
		iterator predecessor(node, &tree);
		--predecessor;
		Node* n = recursive_extract(nullptr, tree, key);
		if (bcast(successor).ptr)
			rebalance_tree(nullptr, tree, successor->first);
		else if (bcast(predecessor).ptr)
			rebalance_tree(nullptr, tree, predecessor->first);
		int del = n ? 1 : 0;
		if (del)
		{
			node_alloc(m_alloc).destroy(n);
			node_alloc(m_alloc).deallocate(n, 1);
			n = nullptr;
			--m_size;
		}
		return (del);
	}

	template <class Key, class T, class Cmp, class Alloc>
	typename map<Key, T, Cmp, Alloc>::Node*	map<Key, T, Cmp, Alloc>::recursive_extract(Node* parent, Node* root, Key key)
	{
		if (!root)
			return (nullptr);
		Node* extracted = nullptr;
		if (m_comp(key, root->pair.first))
			extracted = recursive_extract(root, root->left, key);
		else if (m_comp(root->pair.first, key))
			extracted = recursive_extract(root, root->right, key);
		else
		{
			Node* to_link;
			Node* single_child = root->right ? root->right : root->left;
			if (root->right && root->left)
			{
				Node* successor = root->right;
				while (successor->left)
					successor = successor->left;
				recursive_extract(parent, root, successor->pair.first);
				link_right(successor, root->right);
				link_left(successor, root->left);
				to_link = successor;
			}
			else if (single_child)
				to_link = single_child;
			else
				to_link = nullptr;
				
			if (parent)
				root == parent->right ?
					link_right(parent, to_link) : link_left(parent, to_link);
			else
			{
				tree = to_link;
				to_link->parent = nullptr;
			}
			extracted = root;
		}
		if (parent)
			update_node_height(parent);
		return (extracted);
	}


	template <class Key, class T, class Cmp, class Alloc>
	int	map<Key, T, Cmp, Alloc>::set_heights(Node* root)
	{
		if (!root)
			return -1;
		root->height = std::max(set_heights(root->right), set_heights(root->left)) + 1;
		return (root->height);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::update_node_height(Node* node)
	{
		if (!node)
			return;
		int lheight = node->left ? node->left->height : -1;
		int rheight = node->right ? node->right->height : -1;
		node->height = std::max(lheight, rheight) + 1;
	}

	template <class Key, class T, class Cmp, class Alloc>
	int	map<Key, T, Cmp, Alloc>::readjust_heights(Node* node, Key key)
	{
		if (!node)
			return -1;
		int height_right = node->right ? node->right->height : -1;
		int height_left = node->left ? node->left->height : -1;
		if (m_comp(key, node->pair.first))
			node->height = std::max(readjust_heights(node->left, key), height_right) + 1;
		else
			node->height = std::max(readjust_heights(node->right, key), height_left) + 1;
		return (node->height);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::rebalance_tree(Node* parent, Node* node, Key key)
	{
		if (!node)
			return ;
		if (m_comp(key, node->pair.first))
			rebalance_tree(node, node->left, key);
		else
			rebalance_tree(node, node->right, key);
		int height_right = node->right ? node->right->height : -1;
		int height_left = node->left ? node->left->height : -1;
		if (std::abs(height_left - height_right) > 1)
		{
			if (height_left - height_right > 1)
				right_rotate(parent, node, key);
			else
				left_rotate(parent, node, key);
			return ;
		}
		update_node_height(node);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::right_rotate(Node* root, Node* node, Key key)
	{
		if (m_comp(key, node->pair.first) && !m_comp(key, node->left->pair.first) && node->left->right)
			left_rotate(node, node->left, key);
		Node* nchild = node->left;
		if (!root)
		{
			nchild->parent = nullptr;
			tree = nchild;
		}
		else
		{
			if (node == root->right)
				link_right(root, nchild);
			else if (node == root->left)
				link_left(root, nchild);
		}
		link_left(node, node->left->right);
		link_right(nchild, node);
		update_node_height(node);
		update_node_height(nchild);
		update_node_height(root ? root : tree);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::left_rotate(Node* root, Node* node, Key key)
	{
		if (!m_comp(key, node->pair.first) && m_comp(key, node->right->pair.first) && node->right->left)
			right_rotate(node, node->right, key);
		Node* nchild = node->right;
		if (!root)
		{
			nchild->parent = nullptr;
			tree = nchild;
		}
		else
		{
			if (node == root->right)
				link_right(root, nchild);
			else if (node == root->left)
				link_left(root, nchild);
		}
		link_right(node, node->right->left);
		link_left(nchild, node);
		update_node_height(node);
		update_node_height(nchild);
		update_node_height(root ? root : tree);
	}

	template <class Key, class T, class Cmp, class Alloc>
	bool	map<Key, T, Cmp, Alloc>::is_balanced(Node* root)
	{
		if (!root)
			return true;
		int lheight = root->left ? root->left->height : -1;
		int rheight = root->right ? root->right->height : -1;
		return std::abs(rheight - lheight) <= 1 && is_balanced(root->right) && is_balanced(root->left);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void			map<Key, T, Cmp, Alloc>::free_tree(Node*& root)
	{
		if (!root)
			return;
		free_tree(root->right);
		free_tree(root->left);
		node_alloc(m_alloc).destroy(root);
		node_alloc(m_alloc).deallocate(root, 1);
		root = nullptr;
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::print_root(const Node* root)
	{
		if (!root)
			return ;
		print_root(root->left);
		std::cout << "pair(" << root->pair.first << ", " << root->pair.second << ") (h=" << root->height << ")" << std::endl;
		print_root(root->right);
	}

	template <class Key, class T, class Cmp, class Alloc>
	void	map<Key, T, Cmp, Alloc>::print()
	{
		print_root(tree);
		std::cout << "BALANCED ? " << (is_balanced(tree) ? "yes" : "no") << std::endl;
	}

	template <class Key, class T, class Cmp, class Alloc>
	const typename map<Key, T, Cmp, Alloc>::Node*	map<Key, T, Cmp, Alloc>::get() { return (tree); }
	
}
