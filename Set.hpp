/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:31:10 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/20 18:41:39 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

namespace ft {

	template <class T, class Cmp, class Alloc>
	class set
	{
		public:
			typedef T key_type;
			typedef T value_type;
			typedef Cmp key_compare;
			typedef Cmp value_compare;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;

		protected:
			struct Node
			{
				value_type		pair;
				Node*			left;
				Node*			right;
				Node*			parent;
				ssize_t			height;
				
				Node(key_type key)
					: 	pair(key), left(nullptr),
						right(nullptr), parent(nullptr), height(-1) {}
				~Node() {}
			};
			typedef typename Alloc::template rebind<Node>::other node_alloc;
			typedef const Node* node_pointer;

			template <bool is_const>
			class avl_iterator;
			
			template <bool is_const>
			class avl_reverse_iterator : public reverse_iterator< avl_iterator<is_const> >
			{
				private:
					typedef ft::reverse_iterator< avl_iterator<is_const> > reverse_iterator;
				public:
					avl_reverse_iterator()
						: reverse_iterator() {}
					explicit avl_reverse_iterator(const avl_iterator<is_const>& it)
						: reverse_iterator(it) {}
					avl_reverse_iterator(const ft::reverse_iterator< avl_iterator<false> >& rev_it)
						: reverse_iterator(rev_it) {}
					~avl_reverse_iterator() {}
			};
			
		public:
		
			typedef avl_iterator<true> iterator;
			typedef avl_iterator<true> const_iterator;
			typedef avl_reverse_iterator<true> reverse_iterator;
			typedef avl_reverse_iterator<true> const_reverse_iterator;
			
			explicit set(const key_compare& comp = key_compare());
			template <typename I>
			set(I first, I last, const key_compare& comp = key_compare());
			set(const set& other);
			set<T, Cmp, Alloc>& 	operator=(const set<T, Cmp, Alloc>& target);
			~set();

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

			void										swap(set<T, Cmp, Alloc>& x);

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
			
		protected:

			Node*						tree;
			size_type					m_size;
			key_compare					m_comp;
			allocator_type				m_alloc;

			const Node*					get();
			bool						key_equal(key_type lhs, key_type rhs) const;
			Node*						find_node(Node* root, const key_type& key) const;

			void						link_left(Node* parent, Node* child);
			void						link_right(Node* parent, Node* child);
			int							set_heights(Node* root);
			std::pair<iterator, bool> 	insert_node(Node* root, key_type key);
			std::pair<Node*, bool>		recursive_insert(Node* root, key_type key);
			size_type					delete_node(key_type key);
			Node*						recursive_extract(Node* parent, Node* root, key_type key);
			int							readjust_heights(Node* node, key_type key);
			void						update_node_height(Node* node);
			void						rebalance_tree(Node* parent, Node* node, key_type key);
			void						left_rotate(Node* root, Node* node, key_type key);
			void						right_rotate(Node* root, Node* node, key_type key);
			bool						is_balanced(Node* root);

			void						print();
			void						print_root(const Node* root);
			void						free_tree(Node*& root);
	};
	

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	class set<T, Cmp, Alloc>::avl_iterator
	{
		friend class set<T, Cmp, Alloc>;
		protected:
			typedef typename choose<is_const, const Node*, Node*>::type node_pointer;
			node_pointer					ptr;
			const set<T, Cmp, Alloc>*		set_ptr;
			key_compare						m_comp;
			node_pointer&					get() { return (ptr); }
			avl_iterator					get_next(node_pointer root);
			avl_iterator					get_prev(node_pointer root);
			
			bool							operator==(node_pointer b) { return (ptr == b); }
			bool							operator!=(node_pointer b) { return (ptr != b); }
			
		public:
			typedef T value_type;
			typedef typename choose<is_const, const value_type&, value_type&>::type reference;
			typedef typename choose<is_const, const value_type*, value_type*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef avl_iterator<false> non_const_iterator;
			
			avl_iterator() : ptr(nullptr), set_ptr(nullptr) {}
			avl_iterator(node_pointer p, const set<T, Cmp, Alloc>* set, const key_compare& comp = key_compare())
				: ptr(p), set_ptr(set), m_comp(comp) {}

			avl_iterator(const avl_iterator<false>& target) { *this = target; }
			avl_iterator&	operator=(const avl_iterator<false>& target);
									
			~avl_iterator() {}

			pointer			operator->();
			reference		operator*();
			reference		operator*() const;

			avl_iterator&	operator++();
			avl_iterator	operator++(int) {
				avl_iterator tmp(ptr, set_ptr, m_comp);
				operator++();
				return (tmp);
			}

			avl_iterator&	operator--();
			avl_iterator	operator--(int) {
				avl_iterator tmp(ptr, set_ptr, m_comp);
				operator--();
				return (tmp);
			}
			
			template <bool A, bool B>
			friend bool		operator==(const avl_iterator<A>& a,
										const avl_iterator<B>& b) {
				return (a.ptr == b.ptr);
			}

			template <bool A, bool B>
			friend bool		operator!=(const avl_iterator<A>& a,
										const avl_iterator<B>& b) {
				return (a.ptr != b.ptr);
			}
			
	};



	//  dP""b8 888888  dP"Yb  88""Yb    dP 8888b.  888888  dP"Yb  88""Yb 
	// dP   `"   88   dP   Yb 88__dP   dP   8I  Yb   88   dP   Yb 88__dP 
	// Yb        88   Yb   dP 88"Yb   dP    8I  dY   88   Yb   dP 88"Yb  
	//  YboodP   88    YbodP  88  Yb dP    8888Y"    88    YbodP  88  Yb
	

	template <class T, class Cmp, class Alloc>
	set<T, Cmp, Alloc>::set(const key_compare& comp)
		: tree(nullptr), m_size(0), m_comp(comp), m_alloc(allocator_type()) {}

	template <class T, class Cmp, class Alloc>
	template <typename I>
	set<T, Cmp, Alloc>::set(I first, I last, const key_compare& comp)
		:  tree(nullptr), m_size(0), m_comp(comp), m_alloc(allocator_type())
	{
		for (I it = first; it != last; ++it)
			insert_node(tree, *it);
	}

	template <class T, class Cmp, class Alloc>
	set<T, Cmp, Alloc>::set(const set& other)
		: tree(nullptr), m_size(0), m_comp(other.m_comp), m_alloc(other.m_alloc)
	{
		*this = other;
	}

	template <class T, class Cmp, class Alloc>
	set<T, Cmp, Alloc>& 	set<T, Cmp, Alloc>::operator=(const set<T, Cmp, Alloc>& target)
	{
		free_tree(tree);
		m_size = 0;
		m_comp = target.m_comp;
		for (set<T, Cmp, Alloc>::const_iterator it = target.begin(); it != target.end(); ++it)
			insert_node(tree, *it);
		return (*this);
	}

	template <class T, class Cmp, class Alloc>
	set<T, Cmp, Alloc>::~set() { free_tree(tree); }
	
	


	// 8b    d8 888888 8b    d8 88""Yb 888888 88""Yb     888888 88   88 88b 88  dP""b8 .dP"Y8 
	// 88b  d88 88__   88b  d88 88__dP 88__   88__dP     88__   88   88 88Yb88 dP   `" `Ybo." 
	// 88YbdP88 88""   88YbdP88 88""Yb 88""   88"Yb      88""   Y8   8P 88 Y88 Yb      o.`Y8b 
	// 88 YY 88 888888 88 YY 88 88oodP 888888 88  Yb     88     `YbodP' 88  Y8  YboodP 8bodP' 


	// BEGIN
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_iterator	set<T, Cmp, Alloc>::begin() const
	{
		Node* it = tree;
		while (it && it->left)
			it = it->left;
		return (const_iterator(it, this, m_comp));
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::iterator	set<T, Cmp, Alloc>::begin()
	{
		Node* it = tree;
		while (it && it->left)
			it = it->left;
		return (iterator(it, this, m_comp));
	}

	// END
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_iterator	set<T, Cmp, Alloc>::end() const
	{
		return (const_iterator(nullptr, this, m_comp));
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::iterator	set<T, Cmp, Alloc>::end()
	{
		return (iterator(nullptr, this, m_comp));
	}

	// RBEGIN
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_reverse_iterator set<T, Cmp, Alloc>::rbegin() const
	{
		return const_reverse_iterator(end());
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::reverse_iterator set<T, Cmp, Alloc>::rbegin()
	{
		return reverse_iterator(end());
	}

	// REND
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_reverse_iterator	set<T, Cmp, Alloc>::rend() const
	{
		return const_reverse_iterator(begin());
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::reverse_iterator	set<T, Cmp, Alloc>::rend()
	{
		return reverse_iterator(begin());
	}

	// INSERT
	template <class T, class Cmp, class Alloc>
	std::pair<typename set<T, Cmp, Alloc>::iterator, bool> set<T, Cmp, Alloc>::insert(const typename set<T, Cmp, Alloc>::value_type& val)
	{
		return insert_node(tree, val);
	}

	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::iterator	set<T, Cmp, Alloc>::insert(typename set<T, Cmp, Alloc>::iterator position, const typename set<T, Cmp, Alloc>::value_type& val)
	{
		Node* pos_ptr = const_cast<Node*>(position.get());
		iterator nextpos(ft::fwd(position, 1));
		bool current_next_is_end = (nextpos == end());
		// 3 cases:
		// -> position is a valid hint: would directly precede val, insert from position node down to optimize
		// -> val key = position successor's key, just return successor
		// -> otherwise insert and return the iterator
		if (pos_ptr && m_comp(*position, val)
			&& (current_next_is_end || m_comp(val, *nextpos)))
			return insert_node(pos_ptr, val).first;
		else if (!current_next_is_end && key_equal(val, *nextpos))
			return nextpos;
		else
			return insert(val).first;
	}

	template <class T, class Cmp, class Alloc>
	template <class I>
	void set<T, Cmp, Alloc>::insert(I first, I last)
	{
		for (I it = first; it != last; ++it)
			insert_node(tree, *it);
	}

	// ERASE
	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::erase(iterator position)
	{
		delete_node(*position);
	}

	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::size_type		set<T, Cmp, Alloc>::erase(const key_type& k)
	{
		return delete_node(k);
	}

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::erase(iterator first, iterator last)
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
	template <class T, class Cmp, class Alloc>
	bool	set<T, Cmp, Alloc>::empty() const
	{
		return (!m_size);
	}

	// SIZE
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::size_type		set<T, Cmp, Alloc>::size() const
	{
		return (m_size);
	}

	// MAX SIZE
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::size_type		set<T, Cmp, Alloc>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(Node));
	}

	// SWAP
	template <class T, class Cmp, class Alloc>
	void set<T, Cmp, Alloc>::swap(set<T, Cmp, Alloc>& x)
	{
		std::swap(tree, x.tree);
		std::swap(m_size, x.m_size);
	}

	// CLEAR
	template <class T, class Cmp, class Alloc>
	void set<T, Cmp, Alloc>::clear()
	{
		free_tree(tree);
		m_size = 0;
	}

	// KEY_COMP
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::key_compare	set<T, Cmp, Alloc>::key_comp() const
	{
		return (m_comp);
	}

	// VALUE_COMP
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::value_compare set<T, Cmp, Alloc>::value_comp() const
	{
		return (value_compare(m_comp));
	}

	// FIND
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::iterator set<T, Cmp, Alloc>::find(const key_type& k)
	{
		Node* node = find_node(tree, k);
		
		if (node)
			return iterator(node, this, m_comp);
		else
			return end();
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_iterator set<T, Cmp, Alloc>::find(const key_type& k) const
	{
		Node* node = find_node(tree, k);
		
		if (node)
			return const_iterator(node, this, m_comp);
		else
			return end();
	}

	// COUNT
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::size_type set<T, Cmp, Alloc>::count(const key_type& k) const
	{
		Node* node = find_node(tree, k);
		return (node ? 1 : 0);
	}

	// LOWER BOUND
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::iterator set<T, Cmp, Alloc>::lower_bound (const key_type& k)
	{
		iterator beg = this->begin();
		iterator end = this->end();
		for (iterator it = beg; it != end; ++it)
			if (!m_comp(*it, k))
				return it;
		return end;
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_iterator set<T, Cmp, Alloc>::lower_bound (const key_type& k) const
	{
		const_iterator beg(this->begin());
		const_iterator end(this->end());
		for (const_iterator it = beg; it != end; ++it)
			if (!m_comp(*it, k))
				return it;
		return end;
	}

	// UPPER BOUND
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::iterator set<T, Cmp, Alloc>::upper_bound(const key_type& k)
	{
		iterator beg = this->begin();
		iterator end = this->end();
		for (iterator it = beg; it != end; ++it)
			if (m_comp(k, *it))
				return it;
		return end;
	}
	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::const_iterator set<T, Cmp, Alloc>::upper_bound(const key_type& k) const
	{
		const_iterator beg = this->begin();
		const_iterator end = this->end();
		for (const_iterator it = beg; it != end; ++it)
			if (m_comp(k, *it))
				return it;
		return end;
	}

	// EQUAL RANGE
	template <class T, class Cmp, class Alloc>
	std::pair<typename set<T, Cmp, Alloc>::const_iterator, typename set<T, Cmp, Alloc>::const_iterator>
	set<T, Cmp, Alloc>::equal_range(const key_type& k) const
	{
		return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
	template <class T, class Cmp, class Alloc>
	std::pair<typename set<T, Cmp, Alloc>::iterator, typename set<T, Cmp, Alloc>::iterator>
	set<T, Cmp, Alloc>::equal_range(const key_type& k)
	{
		return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	

	// 88 888888 888888 88""Yb    db    888888  dP"Yb  88""Yb .dP"Y8 
	// 88   88   88__   88__dP   dPYb     88   dP   Yb 88__dP `Ybo." 
	// 88   88   88""   88"Yb   dP__Yb    88   Yb   dP 88"Yb  o.`Y8b 
	// 88   88   888888 88  Yb dP""""Yb   88    YbodP  88  Yb 8bodP' 


	template <class T, class Cmp, class Alloc>
	template <bool B>
	typename set<T, Cmp, Alloc>::template avl_iterator<B>&
	set<T, Cmp, Alloc>::avl_iterator<B>::operator=(const avl_iterator<false>& target)
	{
		ptr = target.ptr;
		set_ptr = target.set_ptr;
		m_comp = target.m_comp;
		return *this;
	}

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>&
	set<T, Cmp, Alloc>::avl_iterator<is_const>::operator++()
	{
		if (*this == set_ptr->end())
		{
			Node* it = set_ptr->tree;
			while (it && it->left)
				it = it->left;
			ptr = it;
		}
		else
			*this = get_next(ptr);
		return (*this);
	}

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>&
	set<T, Cmp, Alloc>::avl_iterator<is_const>::operator--()
	{
		if (*this == set_ptr->end())
		{
			Node* it = set_ptr->tree;
			while (it && it->right)
				it = it->right;
			ptr = it;
		}
		else
			*this = get_prev(ptr);
		return (*this);
	}

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>::pointer
	set<T, Cmp, Alloc>::avl_iterator<is_const>::operator->()
	{
		if (ptr)
			return &ptr->pair;
		throw std::out_of_range(std::string("Error: dereferencing null pointer"));
	}

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>::reference
	set<T, Cmp, Alloc>::avl_iterator<is_const>::operator*()
	{
		if (ptr)
			return ptr->pair;
		throw std::out_of_range(std::string("Error: dereferencing null pointer"));
	}

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>::reference
	set<T, Cmp, Alloc>::avl_iterator<is_const>::operator*() const
	{
		if (ptr && ptr->pair)
			return *ptr->pair;
		throw std::out_of_range(std::string("Error: dereferencing null pointer"));
	}
	


	// 888888  dP"Yb   dP"Yb  88     .dP"Y8 
	//   88   dP   Yb dP   Yb 88     `Ybo.
	//   88   Yb   dP Yb   dP 88       `Y8b 
	//   88    YbodP   YbodP  88ood8 8bodP' 


	template <class T, class Cmp, class Alloc>
	void					set<T, Cmp, Alloc>::link_left
	(typename set<T, Cmp, Alloc>::Node* parent, typename set<T, Cmp, Alloc>::Node* child)
	{
		if (parent)
			parent->left = child;
		if (child)
			child->parent = parent;
	}
	
	template <class T, class Cmp, class Alloc>
	void					set<T, Cmp, Alloc>::link_right
	(typename set<T, Cmp, Alloc>::Node* parent, typename set<T, Cmp, Alloc>::Node* child)
	{
		if (parent)
			parent->right = child;
		if (child)
			child->parent = parent;
	}

	template <class T, class Cmp, class Alloc>
	bool					set<T, Cmp, Alloc>::key_equal(key_type lhs, key_type rhs) const
	{
		return (!m_comp(lhs, rhs) && !m_comp(rhs, lhs));
	}

	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::Node*	set<T, Cmp, Alloc>::find_node(Node* root, const key_type& key) const
	{
		if (!root)
			return nullptr;
		if (key_equal(root->pair, key))
			return root;
		if (m_comp(key, root->pair))
			return find_node(root->left, key);
		else
			return find_node(root->right, key);
	}

	template <class T, class Cmp, class Alloc>
	std::pair<typename set<T, Cmp, Alloc>::Node*, bool>	set<T, Cmp, Alloc>::recursive_insert(Node* root, key_type key)
	{
		if (!root)
		{
			Node* new_node = node_alloc(m_alloc).allocate(1);
			node_alloc(m_alloc).construct(new_node, Node(key));
			return std::pair<Node*, bool>(new_node, true);
		}

		if (m_comp(key, root->pair))
		{
			if (!root->left)
			{
				std::pair<Node*, bool> pair(recursive_insert(root->left, key));
				link_left(root, pair.first);
				return pair;
			}
			return recursive_insert(root->left, key);
		}
		else if (m_comp(root->pair, key))
		{
			if (!root->right)
			{
				std::pair<Node*, bool> pair(recursive_insert(root->right, key));
				link_right(root, pair.first);
				return pair;
			}
			return recursive_insert(root->right, key);
		}
		else
			return std::pair<Node*, bool>(root, false);
	}

	template <class T, class Cmp, class Alloc>
	typename std::pair<typename set<T, Cmp, Alloc>::iterator, bool> 	set<T, Cmp, Alloc>::insert_node(Node* root, key_type key)
	{
		std::pair<Node*, bool> node_pair = recursive_insert(root, key);
		if (!tree)
			tree = node_pair.first;
		readjust_heights(tree, key);
		rebalance_tree(nullptr, tree, key);
		if (node_pair.second)
			++m_size;
		return std::pair<iterator, bool>(iterator(node_pair.first, this, m_comp), node_pair.second);
	}

	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::size_type	set<T, Cmp, Alloc>::delete_node(key_type key)
	{
		Node* node = find_node(tree, key);
		if (!node)
			return (0);
		iterator successor(node, this, m_comp);
		++successor;
		iterator predecessor(node, this, m_comp);
		--predecessor;
		Node* n = recursive_extract(nullptr, tree, key);
		if (successor.get())
			rebalance_tree(nullptr, tree, *successor);
		else if (predecessor.get())
			rebalance_tree(nullptr, tree, *predecessor);
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

	template <class T, class Cmp, class Alloc>
	typename set<T, Cmp, Alloc>::Node*	set<T, Cmp, Alloc>::recursive_extract(Node* parent, Node* root, key_type key)
	{
		if (!root)
			return (nullptr);
		Node* extracted = nullptr;
		if (m_comp(key, root->pair))
			extracted = recursive_extract(root, root->left, key);
		else if (m_comp(root->pair, key))
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
				recursive_extract(parent, root, successor->pair);
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


	template <class T, class Cmp, class Alloc>
	int	set<T, Cmp, Alloc>::set_heights(Node* root)
	{
		if (!root)
			return -1;
		root->height = std::max(set_heights(root->right), set_heights(root->left)) + 1;
		return (root->height);
	}

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::update_node_height(Node* node)
	{
		if (!node)
			return;
		int lheight = node->left ? node->left->height : -1;
		int rheight = node->right ? node->right->height : -1;
		node->height = std::max(lheight, rheight) + 1;
	}

	template <class T, class Cmp, class Alloc>
	int	set<T, Cmp, Alloc>::readjust_heights(Node* node, key_type key)
	{
		if (!node)
			return -1;
		int height_right = node->right ? node->right->height : -1;
		int height_left = node->left ? node->left->height : -1;
		if (m_comp(key, node->pair))
			node->height = std::max(readjust_heights(node->left, key), height_right) + 1;
		else
			node->height = std::max(readjust_heights(node->right, key), height_left) + 1;
		return (node->height);
	}

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::rebalance_tree(Node* parent, Node* node, key_type key)
	{
		if (!node)
			return ;
		if (m_comp(key, node->pair))
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

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::right_rotate(Node* root, Node* node, key_type key)
	{
		if (m_comp(key, node->pair) && !m_comp(key, node->left->pair) && node->left->right)
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

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::left_rotate(Node* root, Node* node, key_type key)
	{
		if (!m_comp(key, node->pair) && m_comp(key, node->right->pair) && node->right->left)
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

	template <class T, class Cmp, class Alloc>
	bool	set<T, Cmp, Alloc>::is_balanced(Node* root)
	{
		if (!root)
			return true;
		int lheight = root->left ? root->left->height : -1;
		int rheight = root->right ? root->right->height : -1;
		return std::abs(rheight - lheight) <= 1 && is_balanced(root->right) && is_balanced(root->left);
	}

	template <class T, class Cmp, class Alloc>
	void			set<T, Cmp, Alloc>::free_tree(Node*& root)
	{
		if (!root)
			return;
		free_tree(root->right);
		free_tree(root->left);
		node_alloc(m_alloc).destroy(root);
		node_alloc(m_alloc).deallocate(root, 1);
		root = nullptr;
	}

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::print_root(const Node* root)
	{
		if (!root)
			return ;
		print_root(root->left);
		std::cout << "value(" << root->pair << ") (h=" << root->height << ")" << std::endl;
		print_root(root->right);
	}

	template <class T, class Cmp, class Alloc>
	void	set<T, Cmp, Alloc>::print()
	{
		print_root(tree);
		std::cout << "BALANCED ? " << (is_balanced(tree) ? "yes" : "no") << std::endl;
	}

	template <class T, class Cmp, class Alloc>
	const typename set<T, Cmp, Alloc>::Node*	set<T, Cmp, Alloc>::get() { return (tree); }
	
	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>
	set<T, Cmp, Alloc>::avl_iterator<is_const>::get_next(node_pointer root)
	{
		if (root->right)
		{
			root = root->right;
			while (root->left)
				root = root->left;
		}
		else
		{
			node_pointer old;
			do
			{
				old = root;
				root = root->parent;
				if (!root)
					return avl_iterator<is_const>(nullptr, set_ptr, m_comp);
			} while (root->right == old);		
		}
		return avl_iterator<is_const>(root, set_ptr, m_comp);
	}

	template <class T, class Cmp, class Alloc>
	template <bool is_const>
	typename set<T, Cmp, Alloc>::template avl_iterator<is_const>
	set<T, Cmp, Alloc>::avl_iterator<is_const>::get_prev(node_pointer root)
	{
		if (root->left)
		{
			root = root->left;
			while (root->right)
				root = root->right;
		}
		else
		{
			node_pointer old;
			do
			{
				old = root;
				root = root->parent;
				if (!root)
					return avl_iterator<is_const>(nullptr, set_ptr, m_comp);
			} while (root->left == old);		
		}
		return avl_iterator<is_const>(root, set_ptr, m_comp);
	}
}