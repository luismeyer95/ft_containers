/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:16:15 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/27 17:09:51 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseIterators.hpp"

namespace ft {

	template<typename T, class Alloc>
	class list
	{
		public:
		
			typedef size_t		size_type;
			typedef	T& 			reference;
			typedef	T* 			pointer;
			typedef	T			value_type;
			typedef	const T& 	const_reference;
			typedef	const T* 	const_pointer;
			typedef	const T		const_value_type;
			typedef Alloc		allocator_type;
			
		protected:

			typedef ft::lst_node<T> Node;
			typedef ft::lst_sentry<T> Sentry;
  
			size_t			_size;
			Node*			sentry;
			Alloc			_alloc;

			void 			link(Node* n1, Node* n2);
			Node* 			unlink(Node* e);
			void			insert_node(Node* e, Node* n1, Node *n2);
			void			delete_node(Node* e);
			Node*			create_node(const T& val);
			void			swap_nodes(Node* n1, Node* n2);
			void			empty_list();
			
			typedef typename Alloc::template rebind<Node>::other node_alloc;
			typedef typename Alloc::template rebind<Sentry>::other sentry_alloc;
			
			template <typename U, bool is_const>
			class lst_iterator : public base_lst_iterator<U, is_const>
			{
				protected:
					using base_lst_iterator<U, is_const>::ptr;
					using base_lst_iterator<U, is_const>::get;
				public:
					typedef U value_type;
					typedef typename choose<is_const, const U&, U&>::type reference;
					typedef typename choose<is_const, const U*, U*>::type pointer;
					typedef std::ptrdiff_t difference_type;
					typedef std::random_access_iterator_tag iterator_category;
					typedef typename remove_const<U>::type non_const_type;
					typedef lst_iterator<non_const_type, false> non_const_iterator;
					
					lst_iterator() : base_lst_iterator<U, is_const>() {}
					lst_iterator(const base_lst_iterator<non_const_type, false>& it)
						: base_lst_iterator<U, is_const>(it.ptr) {}
					lst_iterator(const lst_iterator<non_const_type, false>& target)
						: base_lst_iterator<U, is_const>(target) {}
					using base_lst_iterator<U, is_const>::operator=;
					~lst_iterator() {}
			};
			
			template <typename I>
			class lst_reverse_iterator : public base_reverse_iterator<I>
			{
				protected:
					using base_reverse_iterator<I>::itbase;
					typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;
				public:
					lst_reverse_iterator()
						: base_reverse_iterator<I>() {}
					lst_reverse_iterator(const lst_reverse_iterator<non_const_iterator>& it)
						: base_reverse_iterator<I>(it) {}
					lst_reverse_iterator(const base_reverse_iterator<I>& rev_it)
						: base_reverse_iterator<I>(rev_it.itbase) {}
					using base_reverse_iterator<I>::operator=;
					~lst_reverse_iterator() {}
			};

			template <typename U, bool is_const>
			inline const base_lst_iterator<U, is_const>& bcast(const lst_iterator<U, is_const>& it) const
			{
				return *(base_lst_iterator<U, is_const>*)&it;
			}
			
		public:

			explicit list(const allocator_type& alloc = allocator_type());
			explicit list(size_t n, const T& val = T(), const allocator_type& alloc = allocator_type());
			template<typename I>
			list(I first, I last, const allocator_type& alloc = allocator_type());
			list(const list<T, Alloc>& target);
			list<T, Alloc>& 		operator=(const list<T, Alloc>& target);
			~list();

			typedef lst_iterator<T, false> iterator;
			typedef lst_iterator<const T, true> const_iterator;
			typedef lst_reverse_iterator<iterator> reverse_iterator;
			typedef lst_reverse_iterator<const_iterator> const_reverse_iterator;
			
			size_t					size() const;
			void					resize (size_type n, value_type val = value_type());
			size_t					max_size();
			bool					empty() const;
			void					push_back(const T& e);
			void					push_front(const T& e);
			void					pop_back();
			void					pop_front();
			void					swap(list<T, Alloc>& x);
			void					clear();
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

			template<typename I>
			void					assign(I first, I last);
			void					assign(size_type n, const value_type& val);

			iterator				insert(iterator position, const value_type& val = value_type());
			template <typename I>
    		void					insert(iterator position, I first, I last);
			void					insert(iterator position, size_type n, const value_type& val = value_type());

			iterator				erase (iterator position);
			iterator				erase (iterator first, iterator last);

			reference				front();
			const_reference			front() const;
			reference				back();
			const_reference			back() const;
			const T&				operator[](size_type i) const;
			T&						operator[](size_type i);

			void 					splice (iterator position, list<T, Alloc>& x);
			void 					splice (iterator position, list<T, Alloc>& x, iterator i);
			void 					splice (iterator position, list<T, Alloc>& x, iterator first, iterator last);
			void					remove (const value_type& val);
			template <class Predicate>
  			void 					remove_if (Predicate pred);
			void 					unique();
			template <class BinaryPredicate>
  			void 					unique (BinaryPredicate binary_pred);
			void 					merge (list<T, Alloc>& x);
			template <class Compare>
  			void 					merge (list<T, Alloc>& x, Compare comp);
			void 					sort();
			template <class Compare>
  			void 					sort (Compare comp);
			void					reverse();

			template<typename U, typename V>
  			friend bool operator==(const list<U, V>&, const list<U, V>&);
			template<typename U, typename V>
			friend bool operator!=(const list<U, V>&, const list<U, V>&);
			template<typename U, typename V>
			friend bool operator<(const list<U, V>&, const list<U, V>&);
			template<typename U, typename V>
			friend bool operator<=(const list<U, V>&, const list<U, V>&);
			template<typename U, typename V>
			friend bool operator>(const list<U, V>&, const list<U, V>&);
			template<typename U, typename V>
			friend bool operator>=(const list<U, V>&, const list<U, V>&);
	};


	template<typename T, class Alloc>
	void 			list<T, Alloc>::link(Node* n1, Node* n2) { n1->next = n2; n2->prev = n1; }
	template<typename T, class Alloc>
	typename list<T, Alloc>::Node* 			list<T, Alloc>::unlink(Node* e)
	{
		link(e->prev, e->next);
		return (e);
	}

	template<typename T, class Alloc>
	void			list<T, Alloc>::insert_node(Node* e, Node* n1, Node *n2) { link(n1, e); link(e, n2); }
	
	template<typename T, class Alloc>
	void			list<T, Alloc>::delete_node(Node* e)
	{
		unlink(e);
		node_alloc(_alloc).destroy(e);
		node_alloc(_alloc).deallocate(e, 1);
		e = nullptr;
	}
	
	template<typename T, class Alloc>
	typename list<T, Alloc>::Node*	list<T, Alloc>::create_node(const T& val)
	{
		Node *e = node_alloc(_alloc).allocate(1);
		node_alloc(_alloc).construct(e, Node(val));
		e->data = val;
		return e;
	}

	template<typename T, class Alloc>
	void			list<T, Alloc>::swap_nodes(Node* n1, Node* n2)
	{
		if (n1->next == n2 && n2->prev == n1)
		{
			unlink(n1);
			insert_node(n1, n2, n2->next);
		}
		else if (n2->next == n1 && n1->prev == n2)
		{
			unlink(n2);
			insert_node(n2, n1, n1->next);
		}
		else
		{
			Node* prevn2 = n2->prev;
			Node* nextn2 = n2->next;
			unlink(n1);
			unlink(n2);
			insert_node(n2, n1->prev, n1->next);
			insert_node(n1, prevn2, nextn2);
		}
	}

	template<typename T, class Alloc>
	void			list<T, Alloc>::empty_list()
	{
		Node* tmp;
		Node* iter = sentry->next;
		while (iter != sentry)
		{
			tmp = iter->next;
			node_alloc(_alloc).destroy(iter);
			node_alloc(_alloc).deallocate(iter, 1);
			iter = tmp;
		}
		link(sentry, sentry);
		_size = 0;
	}

	/* CONSTRUCTORS + DESTRUCTOR */
	template<typename T, class Alloc>
	list<T, Alloc>::list(const allocator_type& alloc)
		: _size(0), _alloc(alloc)
	{
		sentry = node_alloc(_alloc).allocate(1);
		sentry_alloc(_alloc).construct((Sentry*)sentry, Sentry());
        link(sentry, sentry);
	}

	template<typename T, class Alloc>
	list<T, Alloc>::list(size_t n, const T& val, const allocator_type& alloc)
		: _size(0), _alloc(alloc)
	{
		sentry = node_alloc(_alloc).allocate(1);
		sentry_alloc(_alloc).construct((Sentry*)sentry, Sentry());
		link(sentry, sentry);
        for (size_t i(0); i < n; i++)
			push_back(val);
	}

	template<typename T, class Alloc>
	template<typename I>
	list<T, Alloc>::list(I first, I last, const allocator_type& alloc)
		:_size(0), _alloc(alloc)
	{
		sentry = node_alloc(_alloc).allocate(1);
		sentry_alloc(_alloc).construct((Sentry*)sentry, Sentry());
		link(sentry, sentry);
		assign(first, last);
	}

	template<typename T, class Alloc>
	list<T, Alloc>::list(const list<T, Alloc>& target)
		: _size(0)
	{
		sentry = node_alloc(_alloc).allocate(1);
		sentry_alloc(_alloc).construct((Sentry*)sentry, Sentry());
		link(sentry, sentry);
		*this = target;
	}

	template<typename T, class Alloc>
	list<T, Alloc>::~list()
	{
		empty_list();
		sentry_alloc(_alloc).destroy((Sentry*)sentry);
		node_alloc(_alloc).deallocate(sentry, 1);
		sentry = nullptr;
	}

	// /* SIZE */
	template<typename T, class Alloc>
	size_t		list<T, Alloc>::size() const { return (_size); }


	/* RESIZE */
	template<typename T, class Alloc>
	void		list<T, Alloc>::resize(size_type n, value_type val)
	{
		if (n < _size)
			for (size_type i(0); i < _size - n; i++)
				delete_node(sentry->prev);
		if (n > _size)
			insert(end(), n - _size, val);
		_size = n;
	}

	/* MAX_SIZE */
	template<typename T, class Alloc>
	size_t		list<T, Alloc>::max_size() { return (std::numeric_limits<size_t>::max() / sizeof(Node)); }

	/* EMPTY */
	template<typename T, class Alloc>
	bool		list<T, Alloc>::empty() const { return (sentry == sentry->next); }


	/* PUSH_BACK */
	template<typename T, class Alloc>
	void		list<T, Alloc>::push_back(const T& e)
	{
		insert_node(create_node(e), sentry->prev, sentry);
		_size++;
	}

	template<typename T, class Alloc>
	void		list<T, Alloc>::push_front(const T& e)
	{
		insert_node(create_node(e), sentry, sentry->next);
		_size++;
	}

	// /* POP_BACK */
	template<typename T, class Alloc>
	void		list<T, Alloc>::pop_back()
	{
		if (!empty())
		{
			delete_node(sentry->prev);
			_size--;
		}
	}

	template<typename T, class Alloc>
	void		list<T, Alloc>::pop_front()
	{
		if (!empty())
		{
			delete_node(sentry->next);
			_size--;
		}
	}

	/* ITERATEURS */
	template<typename T, class Alloc>
	typename list<T, Alloc>::const_iterator				list<T, Alloc>::begin() const { return (const_iterator(sentry->next)); }
	template<typename T, class Alloc>
	typename list<T, Alloc>::iterator					list<T, Alloc>::begin() { return (iterator(sentry->next)); }

	template<typename T, class Alloc>
	typename list<T, Alloc>::const_reverse_iterator		list<T, Alloc>::rbegin() const { return (const_reverse_iterator(end())); }
	template<typename T, class Alloc>
	typename list<T, Alloc>::reverse_iterator			list<T, Alloc>::rbegin() { return (reverse_iterator(end())); }

	template<typename T, class Alloc>
	typename list<T, Alloc>::const_iterator				list<T, Alloc>::end() const { return (const_iterator(sentry)); }
	template<typename T, class Alloc>
	typename list<T, Alloc>::iterator					list<T, Alloc>::end() { return (iterator(sentry)); }

	template<typename T, class Alloc>
	typename list<T, Alloc>::const_reverse_iterator		list<T, Alloc>::rend() const { return (const_reverse_iterator(begin())); }
	template<typename T, class Alloc>
	typename list<T, Alloc>::reverse_iterator			list<T, Alloc>::rend() { return (reverse_iterator(begin())); }

	// /* FRONT */
	template<typename T, class Alloc>
	T&			list<T, Alloc>::front()
	{
		if (empty())
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (sentry->next->data);
	}
	template<typename T, class Alloc>
	const T&	list<T, Alloc>::front() const
	{
		if (empty())
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (sentry->next->data);
	}

	/* BACK */
	template<typename T, class Alloc>
	T&			list<T, Alloc>::back()
	{
		if (empty())
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (sentry->prev->data);
	}
	template<typename T, class Alloc>
	const T&	list<T, Alloc>::back() const
	{
		if (empty())
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (sentry->prev->data);
	}

	/* ASSIGN */
	template<typename T, class Alloc>
	template<typename I>
	void		list<T, Alloc>::assign(I first, I last)
	{
		empty_list();
		for ((void)first; first != last; first++)
			push_back(*first);
	}

	template<typename T, class Alloc>
	void		list<T, Alloc>::assign(size_type n, const value_type& val)
	{
		empty_list();
		for (size_type i(0); i < n; i++)
			push_back(val);
	}

	// /* INSERT */
	template<typename T, class Alloc>
	typename list<T, Alloc>::iterator	list<T, Alloc>::insert(iterator position, const value_type& val)
	{
		Node* it = bcast(position).ptr;
		insert_node(create_node(val), it->prev, it);
		_size++;
		return (position);
	}

	template<typename T, class Alloc>
	void					list<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		for (size_t i(0); i < n; i++)
			insert(position, val);
	}

	template<typename T, class Alloc>
	template<typename I>
    void							list<T, Alloc>::insert(list<T, Alloc>::iterator position, I first, I last)
	{
		for (I it = first; it != last; it++)
			insert(position, *it);
	}

	/* ERASE */
	template<typename T, class Alloc>
	typename list<T, Alloc>::iterator	list<T, Alloc>::erase(iterator position)
	{
		if (position == end())
			throw std::invalid_argument("Error: trying to delete past the end element of list");
		iterator next(fwd(position, 1));
		delete_node(bcast(position).ptr);
		_size--;
		return (next);
	}

	template<typename T, class Alloc>
	typename list<T, Alloc>::iterator	list<T, Alloc>::erase (iterator first, iterator last)
	{
		iterator next;
		iterator it = first;
		while (it != last)
		{
			if (it == end())
				throw std::invalid_argument("Error: trying to delete past the end element of list");
			next = fwd(it, 1);
			delete_node(bcast(it).ptr);
			it = next;
			_size--;
		}
		return (it);
	}

	/* SWAP */
	template<typename T, class Alloc>
	void							list<T, Alloc>::swap(list<T, Alloc>& x)
	{
		std::swap(_size, x._size);
		std::swap(sentry, x.sentry);
	}

	/* CLEAR */
	template<typename T, class Alloc>
	void							list<T, Alloc>::clear() { empty_list(); }

	/* SPLICE */
	template<typename T, class Alloc>
	void 					list<T, Alloc>::splice(iterator position, list<T, Alloc>& x)
	{
		splice(position, x, x.begin(), x.end());
	}

	template<typename T, class Alloc>
	void 					list<T, Alloc>::splice(iterator position, list<T, Alloc>& x, iterator i)
	{
		insert_node(unlink(bcast(i).ptr), bcast(ft::fwd(position, -1)).ptr, bcast(position).ptr);
		_size++;
		x._size--;
	}

	template<typename T, class Alloc>
	void 					list<T, Alloc>::splice(iterator position, list<T, Alloc>& x, iterator first, iterator last)
	{
		Node* pit;
		typename list<T, Alloc>::iterator next(nullptr);
		typename list<T, Alloc>::iterator it = first;
		while (it != last)
		{
			pit = bcast(it).ptr;
			next = fwd(it, 1);
			insert_node(unlink(pit), bcast(fwd(position, -1)).ptr, bcast(position).ptr);
			_size++;
			x._size--;
			it = next;
		}
	}

	template<typename T, class Alloc>
	void					list<T, Alloc>::remove(const value_type& val)
	{
		iterator it = begin();
		while (it != end())
			*it == val ? it = erase(it) : it++;
	}

	template<typename T, class Alloc>
	template <class Predicate>
  	void 					list<T, Alloc>::remove_if(Predicate pred)
	{
		iterator it = begin();
		while (it != end())
			pred(*it) ? it = erase(it) : it++;
	}

	template<typename T, class Alloc>
	void 					list<T, Alloc>::unique()
	{
		iterator it = ++begin();
		while (it != end())
			*it == *(fwd(it, -1)) ? it = erase(it) : it++;
	}

	template<typename T, class Alloc>
	template <class BinaryPredicate>
  	void 					list<T, Alloc>::unique(BinaryPredicate binary_pred)
	{	 
		iterator it = ++begin();
		while (it != end())
		{
			if (binary_pred(*fwd(it, -1), *it))
				it = erase(it);
			else
				++it;
		}
	}

	template<typename T, class Alloc>
	void 					list<T, Alloc>::merge(list<T, Alloc>& x)
	{
		iterator it = begin();
		iterator itx = x.begin();
		iterator next(nullptr);
		while (itx != x.end())
		{
			while (it != end() && !(*itx < *it))
				it++;
			next = fwd(itx, 1);
			splice(it, x, itx);
			itx = next;
		}
	}

	template<typename T, class Alloc>
	template <class Compare>
  	void 					list<T, Alloc>::merge(list<T, Alloc>& x, Compare comp)
	{
		typename list<T, Alloc>::iterator it = begin();
		typename list<T, Alloc>::iterator itx = x.begin();
		typename list<T, Alloc>::iterator next(nullptr);
		while (itx != x.end())
		{
			while (it != end() && !comp(*itx, *it))
				it++;
			next = fwd(itx, 1);
			splice(it, x, itx);
			itx = next;
		}
	}

	template<typename T, class Alloc>
	void 					list<T, Alloc>::sort()
	{
		typename list<T, Alloc>::iterator it = ++begin();
		while (it != end())
		{
			if (*it < *fwd(it, -1))
			{
				swap_nodes(bcast(it).ptr->prev, bcast(it).ptr);
				if (it == begin())
					it++;
			}
			else
				it++;
		}
	}

	template<typename T, class Alloc>
	template <class Compare>
  	void 					list<T, Alloc>::sort(Compare comp)
	{	
		typename list<T, Alloc>::iterator it = ++begin();
		while (it != end())
		{
			if (comp(*it, *fwd(it, -1)))
			{
				swap_nodes(bcast(it).ptr->prev, bcast(it).ptr);
				if (it == begin())
					it++;
			}
			else
				it++;
		}
	}

	template<typename T, class Alloc>
	void					list<T, Alloc>::reverse()
	{
        Node* current = sentry; 
        Node *prev = sentry->prev, *next = nullptr;
        do {
            next = current->next;
            current->next = prev;
			current->prev = next;
            prev = current;
            current = next;
        } while (current != sentry);
	}

	/* OPERATOR OVERLOADS */
	template<typename T, class Alloc>
	const T& list<T, Alloc>::operator[](size_type i) const { return *(begin() + i); }
	template<typename T, class Alloc>
	T& list<T, Alloc>::operator[](size_type i) { return *(begin() + i); }

	template<typename T, class Alloc>
	list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& target)
	{
		empty_list();
		_alloc = target._alloc;
		typename list<T, Alloc>::const_iterator it = target.begin();
		for (it = target.begin() ; it != target.end(); it++)
			push_back(*it);
		return (*this);
	}

	template <typename U, typename V>
  	bool operator==(const list<U, V>& lhs, const list<U, V>& rhs)
	{
		typename list<U, V>::const_iterator a, b;
		if (lhs.size() != rhs.size())
			return false;
		for (a = lhs.begin(), b = rhs.begin(); a != lhs.end() && b != rhs.end() ; a++, b++)
			if (*a != *b)
				return false;
		return true;
	}
	
	template <typename U, typename V>
	bool operator!=(const list<U, V>& lhs, const list<U, V>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename U, typename V>
	bool operator<(const list<U, V>& lhs, const list<U, V>& rhs)
	{
		return std::lexicographical_compare<
			base_lst_iterator<const U, true>,
			base_lst_iterator<const U, true> >
		(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename U, typename V>
	bool operator<=(const list<U, V>& lhs, const list<U, V>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <typename U, typename V>
	bool operator>(const list<U, V>& lhs, const list<U, V>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <typename U, typename V>
	bool operator>=(const list<U, V>& lhs, const list<U, V>& rhs)
	{
		return (!(lhs < rhs));
	}

	/* NON-MEMBER SWAP */
	template<typename T, class Alloc>
  	void swap (list<T, Alloc>& x, list<T, Alloc>& y)
	{
		list<T, Alloc> tmp = x;
		x = y;
		y = tmp;
	}
}
