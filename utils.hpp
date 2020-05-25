/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:08:39 by luis              #+#    #+#             */
/*   Updated: 2020/05/24 13:26:47 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Allocator.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#define nullptr NULL

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


	template <typename I>
	long long distance(I first, I last)
	{
		I ita(first);
		I itb(first);
		long long count = 0;
		while (true)
		{
			if (ita == last)
				return count;
			if (itb == last)
				return (-count);
			count++;
			++ita;
			--itb;
			if (first == ita && ita == itb)
				throw std::exception();
		}
	}

	template <typename I>
	I next(I first, size_t nb)
	{
		while (nb--)
			++first;
		return first;
	}

	template <typename I>
	void advance(I& first, size_t nb)
	{
		while (nb--)
			++first;
	}

	template <typename T>
	bool	less(T lhs, T rhs)
	{
		return (lhs < rhs);
	}

	template <typename T>
	bool	is_const(const T& ref) { static_cast<void>(ref); return true; }
	template <typename T>
	bool	is_const(T& ref) { static_cast<void>(ref); return false; }

	template <typename T>
	struct is_const_type { static const bool value = false; };
	template <typename T>
	struct is_const_type<const T> { static const bool value = true; };

	template <class T>
	T& unconst(const T& val)
	{
		return const_cast<T&>(val);
	}

	template <class T>
	void	swap(T& a, T& b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}

	template <typename T>
	T	fwd(T it, int n)
	{
		if (n > 0)
			while (n--) it++;
		else
			while (n++) it--;
		return (it);
	}

	template <typename T>
	bool	sort_ascend(T a, T b)
	{
		return (a < b);
	}

	template <typename T>
	bool	sort_descend(T a, T b)
	{
		return (a > b);
	}

	template <typename T>
	bool	is_even(T a)
	{
		return (~a & 1);
	}

	ssize_t	circular_increment(const ssize_t& value, const ssize_t& max)
	{
		if (value < max && value >= 0)
			return value;
		if (value == max)
			return 0;
		if (value == -1)
			return max - 1;
		else
			throw std::exception();
	}

	long long	circular_clamp(const long long & value, const long long & low, const long long & high)
	{
		if (value >= low && value < high)
			return value;
		long long dist_min = std::abs(low - value);
		long long dist_max = std::abs(high - value);
		if (dist_min < dist_max)
			return dist_min % (high - low) == 0 ? low : high - (dist_min % (high - low));
		else
			return low + (dist_max % (high - low));
	}

	long long substract_size_t(const size_t& a, const size_t& b)
	{
		long long la = a;
		long long lb = b;
		return (la - lb);
	}

	
	template<bool Cond, class T = void>
	struct enable_if {};
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<typename T>
	struct wrapper { typedef T type; };

	template <class T>
	struct remove_const { typedef T type; };
	template <class T>
	struct remove_const<const T> { typedef T type; };

	template <class T>
	struct add_const { typedef const T type; };
	template <class T>
	struct add_const<const T> { typedef const T type; };

	template <typename T, typename U>
	struct is_same { static const bool value = false; };
	template <typename T>
	struct is_same<T, T> { static const bool value = true; };

	template <bool flag, class IsTrue, class IsFalse>
	struct choose;
	template <class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse> { typedef IsTrue type; };
	template <class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse> { typedef IsFalse type; };


	template <class U>
	class reverse_iterator
	{
		private:
			template <class A> friend class reverse_iterator;
		public:
			typedef U iterator_type;
			typedef typename iterator_type::iterator_category iterator_category;
			typedef typename iterator_type::value_type value_type;
			typedef typename iterator_type::difference_type difference_type;
			typedef typename iterator_type::pointer pointer;
			typedef typename iterator_type::reference reference;
			typedef typename iterator_type::non_const_iterator non_const_iterator;
			reverse_iterator() {}
			explicit reverse_iterator(iterator_type it)
				: itbase(it) {}
			reverse_iterator(const reverse_iterator<non_const_iterator>& rev_it)
				: itbase(rev_it.itbase) {}
			virtual ~reverse_iterator() {}
			reverse_iterator&	operator=(const reverse_iterator& target) { itbase = target.itbase; return *this; }

			reference			operator*() const { return (*ft::fwd(itbase, -1)); }
			pointer				operator->() { return ft::fwd(itbase, -1).operator->(); }
			reverse_iterator&	operator++() { --itbase; return *this; }

			reverse_iterator	operator+(difference_type n) { reverse_iterator tmp(*this); while (n--) ++tmp; return tmp; }
			reverse_iterator	operator-(difference_type n) { reverse_iterator tmp(*this); while (n--) --tmp; return tmp; }

			reverse_iterator	operator++(int) { reverse_iterator tmp(*this); --itbase; return (tmp); }
			reverse_iterator&	operator--() { ++itbase; return *this; }
			reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++itbase; return (tmp); }
			iterator_type 		base() const { return itbase; }
			reference 			operator[](difference_type n) const { return itbase[-n - 1]; }

			template <typename A, typename B>
			friend bool		operator==(const reverse_iterator<A>& a,
										const reverse_iterator<B>& b)
			{ return a.itbase == b.itbase; }

			template <typename A, typename B>
			friend bool		operator!=(const reverse_iterator<A>& a,
										const reverse_iterator<B>& b)
			{ return a.itbase != b.itbase; }


			bool				operator<(const reverse_iterator& b) { return itbase >= b.itbase; }
			bool				operator<=(const reverse_iterator& b) { return itbase > b.itbase; }
			bool				operator>(const reverse_iterator& b) { return itbase <= b.itbase; }
			bool				operator>=(const reverse_iterator& b) { return itbase < b.itbase; }
		protected:
			iterator_type	itbase;
	};
	
}
