/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:08:39 by luis              #+#    #+#             */
/*   Updated: 2020/05/26 21:06:49 by lumeyer          ###   ########lyon.fr   */
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
	
}
