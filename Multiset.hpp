/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:38:19 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/27 15:15:10 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseIterators.hpp"

namespace ft {

	template <class T, class Cmp, class Alloc>
	class multiset
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
		
			typedef ft::map_node<value_type> Node;
			typedef const Node* node_pointer;

			typedef typename Alloc::template rebind<Node>::other node_alloc;

			template <typename U, bool is_const>
			class avl_iterator : public base_avl_iterator<U, is_const>
			{
				protected:
					using base_avl_iterator<U, is_const>::ptr;
					using base_avl_iterator<U, is_const>::get;
					using base_avl_iterator<U, is_const>::get_next;
					using base_avl_iterator<U, is_const>::get_prev;
					using base_avl_iterator<U, is_const>::tree_ref;
				public:
					typedef U value_type;
					typedef typename choose<is_const, const U&, U&>::type reference;
					typedef typename choose<is_const, const U*, U*>::type pointer;
					typedef typename remove_const<U>::type non_const_type;
					typedef avl_iterator<non_const_type, false> non_const_iterator;
					
					avl_iterator() : base_avl_iterator<U, is_const>() {}
					avl_iterator(Node* ptr, Node* const* tree)
						: base_avl_iterator<U, is_const>(ptr, tree) {}
					avl_iterator(const base_avl_iterator<U, is_const>& it)
						: base_avl_iterator<U, is_const>(it.ptr, it.tree_ref) {}
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
		
			typedef avl_iterator<const value_type, true> const_iterator;
			typedef const_iterator iterator;
			typedef avl_reverse_iterator<const_iterator> const_reverse_iterator;
			typedef const_reverse_iterator reverse_iterator;
			
			explicit multiset(const key_compare& comp = key_compare());
			template <typename I>
			multiset(I first, I last, const key_compare& comp = key_compare());
			multiset(const multiset& other);
			multiset<T, Cmp, Alloc>& 	operator=(const multiset<T, Cmp, Alloc>& target);
			~multiset();

			const_iterator								begin() const;
			iterator									begin();

			const_iterator								end() const;
			iterator									end();

			const_reverse_iterator						rbegin() const;
			reverse_iterator							rbegin();

			const_reverse_iterator 						rend() const;
			reverse_iterator							rend();

			template <class I>
			void										insert (I first, I last);
			iterator									insert (const value_type& val);
			iterator									insert (iterator position, const value_type& val);

			void										erase(iterator position);
			size_type									erase(const key_type& k);
			void										erase(iterator first, iterator last);

			bool										empty() const;
			size_type									size() const;
			size_type									max_size() const;

			void										swap(multiset<T, Cmp, Alloc>& x);

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

			const Node*					get() const;
			bool						key_equal(key_type lhs, key_type rhs) const;
			Node*						find_node(Node* root, const key_type& key) const;
			long						get_bfactor(Node* node);

			void						link_left(Node* parent, Node* child);
			void						link_right(Node* parent, Node* child);
			int							set_heights(Node* root);
			std::pair<iterator, bool> 	insert_node(Node* root, key_type key);
			std::pair<Node*, bool>		recursive_insert(Node* root, key_type key);
			size_type					delete_node(key_type key, Node* keynode = nullptr);
			std::pair<Node*, Node*>		recursive_extract(Node* parent, Node* root);
			int							readjust_heights(Node* node, key_type key);
			void						update_node_height(Node* node);
			void						rebalance_tree(Node* node);
			void						left_rotate(Node* root, Node* node);
			void						right_rotate(Node* root, Node* node);
			bool						is_balanced(Node* root);

			void						print();
			void						print_root(const Node* root);
			void						free_tree(Node*& root);
	};



	//  dP""b8 888888  dP"Yb  88""Yb    dP 8888b.  888888  dP"Yb  88""Yb 
	// dP   `"   88   dP   Yb 88__dP   dP   8I  Yb   88   dP   Yb 88__dP 
	// Yb        88   Yb   dP 88"Yb   dP    8I  dY   88   Yb   dP 88"Yb  
	//  YboodP   88    YbodP  88  Yb dP    8888Y"    88    YbodP  88  Yb
	

	template <class T, class Cmp, class Alloc>
	multiset<T, Cmp, Alloc>::multiset(const key_compare& comp)
		: tree(nullptr), m_size(0), m_comp(comp), m_alloc(allocator_type()) {}

	template <class T, class Cmp, class Alloc>
	template <typename I>
	multiset<T, Cmp, Alloc>::multiset(I first, I last, const key_compare& comp)
		:  tree(nullptr), m_size(0), m_comp(comp), m_alloc(allocator_type())
	{
		for (I it = first; it != last; ++it)
			insert_node(tree, *it);
	}

	template <class T, class Cmp, class Alloc>
	multiset<T, Cmp, Alloc>::multiset(const multiset& other)
		: tree(nullptr), m_size(0), m_comp(other.m_comp), m_alloc(other.m_alloc)
	{
		*this = other;
	}

	template <class T, class Cmp, class Alloc>
	multiset<T, Cmp, Alloc>&
	multiset<T, Cmp, Alloc>::operator=(const multiset<T, Cmp, Alloc>& target)
	{
		free_tree(tree);
		m_size = 0;
		m_comp = target.m_comp;
		for (multiset<T, Cmp, Alloc>::const_iterator it = target.begin(); it != target.end(); ++it)
			insert_node(tree, *it);
		return (*this);
	}

	template <class T, class Cmp, class Alloc>
	multiset<T, Cmp, Alloc>::~multiset() { free_tree(tree); }
	
	


	// 8b    d8 888888 8b    d8 88""Yb 888888 88""Yb     888888 88   88 88b 88  dP""b8 .dP"Y8 
	// 88b  d88 88__   88b  d88 88__dP 88__   88__dP     88__   88   88 88Yb88 dP   `" `Ybo." 
	// 88YbdP88 88""   88YbdP88 88""Yb 88""   88"Yb      88""   Y8   8P 88 Y88 Yb      o.`Y8b 
	// 88 YY 88 888888 88 YY 88 88oodP 888888 88  Yb     88     `YbodP' 88  Y8  YboodP 8bodP' 


	// BEGIN
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_iterator
	multiset<T, Cmp, Alloc>::begin() const
	{
		Node* it = tree;
		while (it && it->left)
			it = it->left;
		return (const_iterator(it, &tree));
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::begin()
	{
		Node* it = tree;
		while (it && it->left)
			it = it->left;
		return (iterator(it, &tree));
	}

	// END
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_iterator
	multiset<T, Cmp, Alloc>::end() const
	{
		return (const_iterator(nullptr, &tree));
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::end()
	{
		return (iterator(nullptr, &tree));
	}

	// RBEGIN
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_reverse_iterator
	multiset<T, Cmp, Alloc>::rbegin() const
	{
		return const_reverse_iterator(end());
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::reverse_iterator
	multiset<T, Cmp, Alloc>::rbegin()
	{
		return reverse_iterator(end());
	}

	// REND
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_reverse_iterator
	multiset<T, Cmp, Alloc>::rend() const
	{
		return const_reverse_iterator(begin());
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::reverse_iterator
	multiset<T, Cmp, Alloc>::rend()
	{
		return reverse_iterator(begin());
	}

	// INSERT
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::insert(const typename multiset<T, Cmp, Alloc>::value_type& val)
	{
		return insert_node(tree, val).first;
	}

	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::insert(typename multiset<T, Cmp, Alloc>::iterator position,
									const typename multiset<T, Cmp, Alloc>::value_type& val)
	{
		Node* pos_ptr = const_cast<Node*>(bcast(position).ptr);
		iterator nextpos(ft::fwd(position, 1));
		bool current_next_is_end = (nextpos == end());
		bool pos_infeq = m_comp(*position, val) || key_equal(*position, val);
		bool next_supeq = current_next_is_end || m_comp(val, *nextpos)
		|| key_equal(val, *nextpos);
		// 2 cases:
		// -> position is a valid hint and would directly precede/equal val: insert from position node down to optimize
		// -> otherwise insert and return the iterator
		if (pos_ptr && pos_infeq && next_supeq)
			return insert_node(pos_ptr, val).first;
		else
			return insert(val);
	}

	template <class T, class Cmp, class Alloc>
	template <class I>
	void multiset<T, Cmp, Alloc>::insert(I first, I last)
	{
		for (I it = first; it != last; ++it)
			insert_node(tree, *it);
	}

	// ERASE
	template <class T, class Cmp, class Alloc>
	void	multiset<T, Cmp, Alloc>::erase(iterator position)
	{
		delete_node(*position, const_cast<Node*>(bcast(position).ptr));
	}

	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::size_type
	multiset<T, Cmp, Alloc>::erase(const key_type& k)
	{
		size_type del = 0;
		while (delete_node(k))
			++del;
		return del;
	}

	template <class T, class Cmp, class Alloc>
	void	multiset<T, Cmp, Alloc>::erase(iterator first, iterator last)
	{
		iterator it = first;
		while (it != last)
		{
			iterator successor = ft::fwd(it, 1);
			delete_node(*it, const_cast<Node*>(bcast(it).ptr));
			it = successor;
		}
	}

	// EMPTY
	template <class T, class Cmp, class Alloc>
	bool	multiset<T, Cmp, Alloc>::empty() const
	{
		return (!m_size);
	}

	// SIZE
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::size_type
	multiset<T, Cmp, Alloc>::size() const
	{
		return (m_size);
	}

	// MAX SIZE
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::size_type
	multiset<T, Cmp, Alloc>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(Node));
	}

	// SWAP
	template <class T, class Cmp, class Alloc>
	void multiset<T, Cmp, Alloc>::swap(multiset<T, Cmp, Alloc>& x)
	{
		std::swap(tree, x.tree);
		std::swap(m_size, x.m_size);
	}

	// CLEAR
	template <class T, class Cmp, class Alloc>
	void multiset<T, Cmp, Alloc>::clear()
	{
		free_tree(tree);
		m_size = 0;
	}

	// KEY_COMP
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::key_compare
	multiset<T, Cmp, Alloc>::key_comp() const
	{
		return (m_comp);
	}

	// VALUE_COMP
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::value_compare
	multiset<T, Cmp, Alloc>::value_comp() const
	{
		return (value_compare(m_comp));
	}

	// FIND
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::find(const key_type& k)
	{
		Node* node = find_node(tree, k);
		
		if (node)
			return iterator(node, &tree);
		else
			return end();
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_iterator
	multiset<T, Cmp, Alloc>::find(const key_type& k) const
	{
		Node* node = find_node(tree, k);
		
		if (node)
			return const_iterator(node, &tree);
		else
			return end();
	}

	// COUNT
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::size_type
	multiset<T, Cmp, Alloc>::count(const key_type& k) const
	{
		Node* node = find_node(tree, k);
		if (!node)
			return (0);
		size_type count = 0;
		const_iterator it(node, &tree);
		while (it != end() && key_equal(*it, k))
		{
			++count;
			++it;
		}
		return (count);
	}

	// LOWER BOUND
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::lower_bound (const key_type& k)
	{
		iterator beg = this->begin();
		iterator end = this->end();
		for (iterator it = beg; it != end; ++it)
			if (!m_comp(*it, k))
				return it;
		return end;
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_iterator
	multiset<T, Cmp, Alloc>::lower_bound (const key_type& k) const
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
	typename multiset<T, Cmp, Alloc>::iterator
	multiset<T, Cmp, Alloc>::upper_bound(const key_type& k)
	{
		iterator beg = this->begin();
		iterator end = this->end();
		for (iterator it = beg; it != end; ++it)
			if (m_comp(k, *it))
				return it;
		return end;
	}
	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::const_iterator
	multiset<T, Cmp, Alloc>::upper_bound(const key_type& k) const
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
	std::pair<typename multiset<T, Cmp, Alloc>::const_iterator, typename multiset<T, Cmp, Alloc>::const_iterator>
	multiset<T, Cmp, Alloc>::equal_range(const key_type& k) const
	{
		return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
	template <class T, class Cmp, class Alloc>
	std::pair<typename multiset<T, Cmp, Alloc>::iterator, typename multiset<T, Cmp, Alloc>::iterator>
	multiset<T, Cmp, Alloc>::equal_range(const key_type& k)
	{
		return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}


	// 888888  dP"Yb   dP"Yb  88     .dP"Y8 
	//   88   dP   Yb dP   Yb 88     `Ybo.
	//   88   Yb   dP Yb   dP 88       `Y8b 
	//   88    YbodP   YbodP  88ood8 8bodP' 


	template <class T, class Cmp, class Alloc>
	void					multiset<T, Cmp, Alloc>::link_left
	(typename multiset<T, Cmp, Alloc>::Node* parent, typename multiset<T, Cmp, Alloc>::Node* child)
	{
		if (parent)
			parent->left = child;
		if (child)
			child->parent = parent;
	}
	
	template <class T, class Cmp, class Alloc>
	void					multiset<T, Cmp, Alloc>::link_right
	(typename multiset<T, Cmp, Alloc>::Node* parent, typename multiset<T, Cmp, Alloc>::Node* child)
	{
		if (parent)
			parent->right = child;
		if (child)
			child->parent = parent;
	}

	template <class T, class Cmp, class Alloc>
	long					multiset<T, Cmp, Alloc>::get_bfactor(Node* node)
	{
		long height_right = node->right ? node->right->height : -1;
		long height_left = node->left ? node->left->height : -1;
		return height_right - height_left;
	}


	template <class T, class Cmp, class Alloc>
	bool					multiset<T, Cmp, Alloc>::key_equal(key_type lhs, key_type rhs) const
	{
		return (!m_comp(lhs, rhs) && !m_comp(rhs, lhs));
	}

	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::Node*
	multiset<T, Cmp, Alloc>::find_node(Node* root, const key_type& key) const
	{
		if (!root)
			return nullptr;
		if (m_comp(key, root->pair))
			return find_node(root->left, key);
		else if (m_comp(root->pair, key))
			return find_node(root->right, key);
		else
		{
			Node* subnode = find_node(root->left, key);
			return (subnode ? subnode : root);
		}
		
	}

	template <class T, class Cmp, class Alloc>
	std::pair<typename multiset<T, Cmp, Alloc>::Node*, bool>
	multiset<T, Cmp, Alloc>::recursive_insert(Node* root, key_type key)
	{
		if (!root)
		{
			Node* new_node = node_alloc(m_alloc).allocate(1);
			node_alloc(m_alloc).construct(new_node, Node(key));
			new_node->height = 0;
			return std::pair<Node*, bool>(new_node, true);
		}

		if (m_comp(key, root->pair))
		{
			bool had_left = root->left;
			std::pair<Node*, bool> pair = recursive_insert(root->left, key);
			if (!had_left)
				link_left(root, pair.first);
			update_node_height(root);
			return pair;
		}
		else
		{
			bool had_right = root->right;
			std::pair<Node*, bool> pair = recursive_insert(root->right, key);
			if (!had_right)
				link_right(root, pair.first);
			update_node_height(root);
			return pair;
		}
	}

	template <class T, class Cmp, class Alloc>
	typename std::pair<typename multiset<T, Cmp, Alloc>::iterator, bool>
	multiset<T, Cmp, Alloc>::insert_node(Node* root, key_type key)
	{
		std::pair<Node*, bool> node_pair = recursive_insert(root, key);
		if (!tree)
			tree = node_pair.first;
		readjust_heights(node_pair.first, key);
		rebalance_tree(node_pair.first->parent);
		if (node_pair.second)
			++m_size;
		return std::pair<iterator, bool>(iterator(node_pair.first, &tree), node_pair.second);
	}

	template <class T, class Cmp, class Alloc>
	typename multiset<T, Cmp, Alloc>::size_type
	multiset<T, Cmp, Alloc>::delete_node(key_type key, Node* keynode)
	{
		Node* node;
		if (keynode)
			node = keynode;
		else
			node = find_node(tree, key);
		if (!node)
			return (0);
		std::pair<Node*, Node*> n = recursive_extract(node->parent, node);
		rebalance_tree(n.second);
		int del = n.first ? 1 : 0;
		if (del)
		{
			node_alloc(m_alloc).destroy(n.first);
			node_alloc(m_alloc).deallocate(n.first, 1);
			n.first = nullptr;
			--m_size;
		}
		return (del);
	}

	template <class T, class Cmp, class Alloc>
	std::pair<typename multiset<T, Cmp, Alloc>::Node*, typename multiset<T, Cmp, Alloc>::Node*>
	multiset<T, Cmp, Alloc>::recursive_extract(Node* parent, Node* root)
	{
		Node* extracted = nullptr;
		Node* to_link;
		Node* to_update = parent;
		Node* single_child = root->right ? root->right : root->left;
		if (root->right && root->left)
		{
			Node* successor = root->right;
			while (successor->left)
				successor = successor->left;
			if (successor != root->right)
				to_update = successor->parent;
			else
				to_update = root->parent;
			recursive_extract(successor->parent, successor);
			link_right(successor, root->right);
			link_left(successor, root->left);
			update_node_height(successor);
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
			if (to_link)
				to_link->parent = nullptr;
		}
		extracted = root;
		parent = to_update;
		while (parent)
		{
			update_node_height(parent);
			parent = parent->parent;
		}
		return std::pair<Node*, Node*>(extracted, to_update);
	}


	template <class T, class Cmp, class Alloc>
	int	multiset<T, Cmp, Alloc>::set_heights(Node* root)
	{
		if (!root)
			return -1;
		root->height = std::max(set_heights(root->right), set_heights(root->left)) + 1;
		return (root->height);
	}

	template <class T, class Cmp, class Alloc>
	void	multiset<T, Cmp, Alloc>::update_node_height(Node* node)
	{
		if (!node)
			return;
		int lheight = node->left ? node->left->height : -1;
		int rheight = node->right ? node->right->height : -1;
		node->height = std::max(lheight, rheight) + 1;
	}

	template <class T, class Cmp, class Alloc>
	int	multiset<T, Cmp, Alloc>::readjust_heights(Node* node, key_type key)
	{
		Node* min = find_node(tree, key);
		while (min)
		{
			update_node_height(min);
			min = min->parent;
		}
		return (node->height);
	}

	template <class T, class Cmp, class Alloc>
	void	multiset<T, Cmp, Alloc>::rebalance_tree(Node* node)
	{
		while (node)
		{
			update_node_height(node);
			long bf = get_bfactor(node);
			if (std::abs(bf) > 1)
			{
				if (bf > 1)
					left_rotate(node->parent, node);
				else
					right_rotate(node->parent, node);
			}
			node = node->parent;
		}
	}

	template <class T, class Cmp, class Alloc>
	void	multiset<T, Cmp, Alloc>::right_rotate(Node* root, Node* node)
	{
		if (get_bfactor(node->left) > 0)
			left_rotate(node, node->left);
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
	void	multiset<T, Cmp, Alloc>::left_rotate(Node* root, Node* node)
	{
		if (get_bfactor(node->right) < 0)
			right_rotate(node, node->right);
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
	bool	multiset<T, Cmp, Alloc>::is_balanced(Node* root)
	{
		if (!root)
			return true;
		int lheight = root->left ? root->left->height : -1;
		int rheight = root->right ? root->right->height : -1;
		return std::abs(rheight - lheight) <= 1 && is_balanced(root->right) && is_balanced(root->left);
	}

	template <class T, class Cmp, class Alloc>
	void			multiset<T, Cmp, Alloc>::free_tree(Node*& root)
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
	void	multiset<T, Cmp, Alloc>::print_root(const Node* root)
	{
		if (!root)
			return ;
		print_root(root->left);
		std::cout << "pair(" << root->pair << ") (h=" << root->height << ")" << std::endl;
		print_root(root->right);
	}

	template <class T, class Cmp, class Alloc>
	void	multiset<T, Cmp, Alloc>::print()
	{
		print_root(tree);
		std::cout << "BALANCED ? " << (is_balanced(tree) ? "yes" : "no") << std::endl;
	}

	template <class T, class Cmp, class Alloc>
	const typename multiset<T, Cmp, Alloc>::Node*	multiset<T, Cmp, Alloc>::get() const { return (tree); }

}