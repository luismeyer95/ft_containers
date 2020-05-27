/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseIterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 19:40:04 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/27 16:59:12 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

namespace ft {

	template <class T, class Cmp = std::less<T>, class Alloc = ft::allocator<T> >
	class set;
	template <class T, class Cmp = std::less<T>, class Alloc = ft::allocator<T> >
	class multiset;
	template <class Key, class T, class Cmp = std::less<Key>, class Alloc = ft::allocator<std::pair<const Key,T> > >
	class map;
	template <class Key, class T, class Cmp = std::less<Key>, class Alloc = ft::allocator<std::pair<const Key,T> > >
	class multimap;
	template<typename T, class Alloc = ft::allocator<T> >
	class list;
	template<typename T, class Alloc = ft::allocator<T> >
	class vector;
	template<typename T, class Alloc = ft::allocator<T> >
	class deque;
	template<typename T, class C = deque<T> >
	class stack;
	template<typename T, class C = deque<T> >
	class queue;

	template <typename T, bool is_const>
	class base_v_iterator
	{
		public:
			typedef T value_type;
			typedef typename choose<is_const, const T&, T&>::type reference;
			typedef typename choose<is_const, const T*, T*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename remove_const<T>::type non_const_type;
			typedef base_v_iterator<non_const_type, false> non_const_iterator;

			T*			ptr;
			T&	get() { return (ptr); }
			
			base_v_iterator() : ptr(nullptr) {}
			base_v_iterator(pointer p) : ptr(p) {}
			base_v_iterator(const non_const_iterator& target) : ptr(target.ptr) {}
			virtual ~base_v_iterator() {}

			inline base_v_iterator&		operator=(const non_const_iterator& target) {
				this->ptr = target.ptr;
				return *this;
			}
			
			inline  base_v_iterator&	operator++() {
				ptr++;
				return (*this);
			}
			
			inline  base_v_iterator		operator++(int) {
				base_v_iterator tmp(ptr);
				operator++();
				return (tmp);
			}
			
			inline  base_v_iterator&	operator--() {
				ptr--;
				return (*this);
			}
			
			inline  base_v_iterator		operator--(int) {
				base_v_iterator tmp(ptr);
				operator--();
				return (tmp);
			}
			
			inline	reference			operator*() {
				return *ptr;
			}

			inline	reference			operator[](difference_type n) {
				return ptr[n];
			}
			
			inline	base_v_iterator		operator+(difference_type n) {
				return base_v_iterator(ptr + n);
			}
			
			inline  base_v_iterator&	operator+=(difference_type n) {
				ptr += n;
				return *this;
			}
			
			inline  base_v_iterator		operator-(difference_type n) {
				return base_v_iterator(ptr - n);
			}
			
			inline  long long			operator-(const base_v_iterator& other) {
				return ((long long)ptr - (long long)other.ptr) / (long long)sizeof(value_type);
			}

			inline  base_v_iterator&	operator-=(difference_type n) {
				ptr -= n;
				return *this;
			}
			

			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator==(	base_v_iterator<Ta, A> a,
													base_v_iterator<Tb, B> b) {
				return (a.ptr == b.ptr);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator!=(	base_v_iterator<Ta, A> a,
													base_v_iterator<Tb, B> b) {
				return (a.ptr != b.ptr);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator<(	base_v_iterator<Ta, A> a,
													base_v_iterator<Tb, B> b) {
				return (a.ptr < b.ptr);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator<=(	base_v_iterator<Ta, A> a,
													base_v_iterator<Tb, B> b) {
				return (a.ptr <= b.ptr);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator>(	base_v_iterator<Ta, A> a,
													base_v_iterator<Tb, B> b) {
				return (a.ptr > b.ptr);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator>=(	base_v_iterator<Ta, A> a,
													base_v_iterator<Tb, B> b) {
				return (a.ptr >= b.ptr);
			}
			
	};


	template <typename T>
	struct lst_node
	{
		lst_node* next;
		lst_node* prev;
		T data;
		lst_node(T val) : data(val) {}
	};

	template <typename T>
	struct lst_sentry
	{
		lst_node<T>* next;
		lst_node<T>* prev;
	};

	template <typename T, bool is_const>
	class base_lst_iterator
	{
		public:
			typedef typename remove_const<T>::type non_const_type;
			typedef base_lst_iterator<non_const_type, false> non_const_iterator;
			typedef typename choose<is_const, const lst_node<T>*, lst_node<T>*>::type node_pointer;
			typedef T value_type;
			typedef typename choose<is_const, const T&, T&>::type reference;
			typedef typename choose<is_const, const T*, T*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef std::bidirectional_iterator_tag iterator_category;

			lst_node<non_const_type>*		ptr;
			lst_node<non_const_type>*		get() { return (ptr); }

			base_lst_iterator() : ptr(nullptr) {}
			base_lst_iterator(node_pointer p) : ptr(p) {}
			base_lst_iterator(const non_const_iterator& target) : ptr(target.ptr) {}
			virtual ~base_lst_iterator() {}
			
			base_lst_iterator&	operator=(const non_const_iterator& target) {
				ptr = target.ptr; return *this;
			}

			reference			operator*() {
				if (ptr)
					return ptr->data;
				throw std::out_of_range(std::string("Error: dereferencing null pointer"));
			}
			
			base_lst_iterator&	operator++() {
				if (ptr)
					ptr = ptr->next;
				return (*this);
			}

			base_lst_iterator	operator++(int) {
				base_lst_iterator tmp(ptr);
				operator++();
				return (tmp);
			}
			
			base_lst_iterator&	operator--() {
				if (ptr)
					ptr = ptr->prev;
				return (*this);
			}

			base_lst_iterator	operator--(int) {
				base_lst_iterator tmp(ptr);
				operator--();
				return (tmp);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend bool			operator==(	const base_lst_iterator<Ta, A>& a,
											const base_lst_iterator<Tb, B>& b) {
				return (a.ptr == b.ptr);
			}

			template <typename Ta, typename Tb, bool A, bool B>
			friend bool			operator!=(	const base_lst_iterator<Ta, A>& a,
											const base_lst_iterator<Tb, B>& b) {
				return (a.ptr != b.ptr);
			}
			
			bool				operator==(node_pointer b) {
				return (ptr == b);
			}

			bool				operator!=(node_pointer b) {
				return (ptr != b);
			}
	};

	template <typename T>
	struct map_node
	{
		T						pair;
		map_node*				left;
		map_node*				right;
		map_node*				parent;
		ssize_t					height;
		
		map_node(T val)
			: 	pair(val), left(nullptr),
				right(nullptr), parent(nullptr), height(-1) {}
		~map_node() {}
	};

	
	template <typename T, bool is_const>
	class base_avl_iterator
	{
		public:
			typedef typename remove_const<T>::type non_const_type;
			typedef base_avl_iterator<non_const_type, false> non_const_iterator;
			typedef typename choose<is_const, const map_node<T>*, map_node<T>*>::type node_pointer;
		
			typedef typename choose<is_const, const T&, T&>::type reference;
			typedef typename choose<is_const, const T*, T*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef std::bidirectional_iterator_tag iterator_category;
			
			map_node<non_const_type>*			ptr;
			map_node<non_const_type>* const*	tree_ref;

			base_avl_iterator() : ptr(nullptr), tree_ref(nullptr) {}
			base_avl_iterator(map_node<non_const_type>* p, map_node<non_const_type>* const* tree_ref)
				: ptr(p), tree_ref(tree_ref) {}
			base_avl_iterator(const non_const_iterator& target)
				: ptr(target.ptr), tree_ref(target.tree_ref) {}
			virtual ~base_avl_iterator() {}

			base_avl_iterator&	operator=(const non_const_iterator& target) {
				ptr = target.ptr;
				tree_ref = target.tree_ref;
				return *this;
			}
			
			map_node<non_const_type>*		get() { return (ptr); }
			
			base_avl_iterator				get_next(map_node<non_const_type>* root)
			{
				if (root->right)
				{
					root = root->right;
					while (root->left)
						root = root->left;
				}
				else
				{
					map_node<non_const_type>* old;
					do
					{
						old = root;
						root = root->parent;
						if (!root)
							return base_avl_iterator(nullptr, tree_ref);
					} while (root->right == old);		
				}
				return base_avl_iterator(root, tree_ref);
			}
			
			base_avl_iterator				get_prev(map_node<non_const_type>* root)
			{
				if (root->left)
				{
					root = root->left;
					while (root->right)
						root = root->right;
				}
				else
				{
					map_node<non_const_type>* old;
					do
					{
						old = root;
						root = root->parent;
						if (!root)
							return base_avl_iterator(nullptr, tree_ref);
					} while (root->left == old);		
				}
				return base_avl_iterator(root, tree_ref);
			}
			
			bool			operator==(map_node<non_const_type>* b) { return (ptr == b); }
			bool			operator!=(map_node<non_const_type>* b) { return (ptr != b); }

			pointer			operator->()
			{
				if (ptr)
					return &ptr->pair;
				throw std::out_of_range(std::string("Error: dereferencing null pointer"));
			}
	
			reference		operator*()
			{
				if (ptr)
					return ptr->pair;
				throw std::out_of_range(std::string("Error: dereferencing null pointer"));
			}

			base_avl_iterator&	operator++()
			{
				if (!ptr)
				{
					ptr = *tree_ref;
					while (ptr && ptr->left)
						ptr = ptr->left;
				}
				else
					*this = get_next(ptr);
				return (*this);
			}

			base_avl_iterator	operator++(int)
			{
				base_avl_iterator tmp(ptr, tree_ref);
				operator++();
				return (tmp);
			}

			base_avl_iterator&	operator--()
			{
				if (!ptr)
				{
					ptr = *tree_ref;
					while (ptr && ptr->right)
						ptr = ptr->right;
				}
				else
					*this = get_prev(ptr);
				return (*this);
			}
			
			base_avl_iterator	operator--(int)
			{
				base_avl_iterator tmp(ptr, tree_ref);
				operator--();
				return (tmp);
			}
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend bool			operator==(	const base_avl_iterator<Ta, A>& a,
											const base_avl_iterator<Tb, B>& b) {
				return (a.ptr == b.ptr);
			}

			template <typename Ta, typename Tb, bool A, bool B>
			friend bool			operator!=(	const base_avl_iterator<Ta, A>& a,
											const base_avl_iterator<Tb, B>& b) {
				return (a.ptr != b.ptr);
			}
			
	};
	
	template <typename T>
	struct deque_node
	{
		ft::vector<T*>	_pmap;
		size_t			_size;
		size_t			_capacity;
		size_t			_chunksize;
		ssize_t			_head;
		size_t			_headchunk;
		ssize_t			_tail;
		size_t			_tailchunk;
		deque_node()
			:	_size(0), _capacity(0), _chunksize(0),
				_head(-1), _headchunk(0),
				_tail(-1), _tailchunk(0) {}
		~deque_node() {}
	};
	
	template <typename T, bool is_const>
	class base_dq_iterator
	{
		public:
			typedef T value_type;
			typedef typename choose<is_const, const T&, T&>::type reference;
			typedef typename choose<is_const, const T*, T*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename remove_const<T>::type non_const_type;
			typedef base_dq_iterator<non_const_type, false> non_const_iterator;

			ssize_t								head;
			const deque_node<non_const_type>*	dq;
			
			base_dq_iterator() : head(0), dq(nullptr) {}
			base_dq_iterator(ssize_t head, const deque_node<non_const_type>* dq) : head(head), dq(dq) {}
			base_dq_iterator(const non_const_iterator& target) : head(target.head), dq(target.dq) {}
			~base_dq_iterator() {}
			
			inline base_dq_iterator&	operator=(const non_const_iterator& target) {
				this->dq = target.dq;
				this->head = target.head;
				return *this;
			}
			
			inline  base_dq_iterator&	operator++() {
				if (head == dq->_tail)
					head = -1;
				else if (head == -1)
					head = dq->_head;
				else
					head = circular_increment(head + 1, dq->_capacity);
				return (*this);
			}

			inline  base_dq_iterator	operator++(int) {
				base_dq_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			inline  base_dq_iterator&	operator--() {
				if (head == dq->_head)
					head = -1;
				else if (head == -1)
					head = dq->_tail;
				else
					head = circular_increment(head - 1, dq->_capacity);
				return (*this);
			}
			
			inline  base_dq_iterator	operator--(int) {
				base_dq_iterator tmp(*this);
				operator--();
				return (tmp);
			}
			
			inline	reference			operator*() {
				return dq->_pmap[head / dq->_chunksize][head % dq->_chunksize];
			}

			inline	reference			operator[](difference_type n) {
				return *(*this + n);
			}

			inline	base_dq_iterator	operator+(difference_type n) {
				base_dq_iterator tmp(*this);
				while (n--) ++tmp;
				return tmp;
			}

			inline  base_dq_iterator&	operator+=(difference_type n) {
				*this = *this + n;
				return *this;
			}
			
			inline  base_dq_iterator	operator-(difference_type n) {
				base_dq_iterator tmp(*this);
				while (n--) --tmp;
				return tmp;
			}
			
			inline  base_dq_iterator&	operator-=(difference_type n) {
				*this = *this - n;
				return *this;
			}

			inline  long long			operator-(const base_dq_iterator& other) {
				bool pos = *this > other;
				base_dq_iterator first(!pos ? *this : other);
				base_dq_iterator target(!pos ? other : *this);
				long long count = 0;
				long long sign = pos ? 1 : -1;
				while (true)
				{
					if (first == target)
						return (count * sign);
					++first;
					++count;
					if (count > (long long)dq->_size)
						throw std::invalid_argument("Error: invalid comparison on deque iterator");
				}
			}

			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator==(base_dq_iterator<Ta, A> a, base_dq_iterator<Tb, B> b)
			{ return (a.dq && a.dq == b.dq && a.head == b.head); }

			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator!=(base_dq_iterator<Ta, A> a, base_dq_iterator<Tb, B> b)
			{ return (a.dq && a.dq == b.dq && a.head != b.head); }
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator<(base_dq_iterator<Ta, A> a, base_dq_iterator<Tb, B> b) {
				if (!a.dq || a.dq != b.dq || a.head == -1)
					return false;
				if (b.head == -1)
					return true;
				if (a.dq->_head < a.dq->_tail)
					return a.head < b.head;
				long long diff_a = (long long)a.head - (long long)a.dq->_head;
				long long diff_b = (long long)b.head - (long long)a.dq->_head;
				long long shift_a = circular_clamp(diff_a, 0, a.dq->_capacity);
				long long shift_b = circular_clamp(diff_b, 0, a.dq->_capacity);
				return (shift_a < shift_b);
			}

			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator<=(base_dq_iterator<Ta, A> a, base_dq_iterator<Tb, B> b)
			{ return (a.dq && a.dq == b.dq && !(a > b)); }

			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator>(base_dq_iterator<Ta, A> a, base_dq_iterator<Tb, B> b)
			{ return (a.dq && a.dq == b.dq && !(a < b) && a != b); }
			
			template <typename Ta, typename Tb, bool A, bool B>
			friend inline bool			operator>=(base_dq_iterator<Ta, A> a, base_dq_iterator<Tb, B> b)
			{ return (a.dq && a.dq == b.dq && !(a < b)); }

	};


	template <class U>
	class base_reverse_iterator
	{
		public:
			typedef U iterator_type;
			typedef typename iterator_type::iterator_category iterator_category;
			typedef typename iterator_type::value_type value_type;
			typedef typename iterator_type::difference_type difference_type;
			typedef typename iterator_type::pointer pointer;
			typedef typename iterator_type::reference reference;
			typedef typename iterator_type::non_const_type non_const_type;
			typedef typename iterator_type::non_const_iterator non_const_iterator;

			iterator_type	itbase;

			base_reverse_iterator() {}
			base_reverse_iterator(const iterator_type& it)
				: itbase(it) {}
			base_reverse_iterator(const base_reverse_iterator<non_const_iterator>& rev_it)
				: itbase(rev_it.itbase) {}
			virtual ~base_reverse_iterator() {}
			base_reverse_iterator&	operator=(const base_reverse_iterator<non_const_iterator>& target) {
				itbase = target.itbase;
				return *this;
			}

			reference				operator*() {
				return (*ft::fwd(itbase, -1));
			}

			pointer					operator->() {
				return ft::fwd(itbase, -1).operator->();
			}
			
			base_reverse_iterator&	operator++() {
				--itbase;
				return *this;
			}

			base_reverse_iterator	operator++(int) {
				base_reverse_iterator tmp(*this);
				--itbase;
				return (tmp);
			}

			base_reverse_iterator&	operator--() {
				++itbase;
				return *this;
			}

			base_reverse_iterator	operator--(int) {
				base_reverse_iterator tmp(*this);
				++itbase;
				return (tmp);
			}

			base_reverse_iterator	operator+(difference_type n) {
				base_reverse_iterator tmp(*this);
				while (n--) ++tmp;
				return tmp;
			}
			
			base_reverse_iterator	operator-(difference_type n) {
				base_reverse_iterator tmp(*this);
				while (n--) --tmp;
				return tmp;
			}

			iterator_type 			base() {
				return itbase;
			}

			reference 				operator[](difference_type n) {
				return itbase[-n - 1];
			}

			template <typename A, typename B>
			friend bool		operator==(	const base_reverse_iterator<A>& a,
										const base_reverse_iterator<B>& b) {
				return a.itbase == b.itbase;
			}

			template <typename A, typename B>
			friend bool		operator!=(	const base_reverse_iterator<A>& a,
										const base_reverse_iterator<B>& b) {
				return a.itbase != b.itbase;
			}

			template <typename A, typename B>
			friend bool		operator<(	const base_reverse_iterator<A>& a,
										const base_reverse_iterator<B>& b) {
				return a.itbase >= b.itbase;
			}

			template <typename A, typename B>
			friend bool		operator<=(	const base_reverse_iterator<A>& a,
										const base_reverse_iterator<B>& b) {
				return a.itbase > b.itbase;
			}

			template <typename A, typename B>
			friend bool		operator>(	const base_reverse_iterator<A>& a,
										const base_reverse_iterator<B>& b) {
				return a.itbase <= b.itbase;
			}

			template <typename A, typename B>
			friend bool		operator>=(	const base_reverse_iterator<A>& a,
										const base_reverse_iterator<B>& b) {
				return a.itbase < b.itbase;
			}

	};
}