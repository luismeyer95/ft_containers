/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Containers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:46:12 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/26 21:28:27 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#include "Vector.hpp"
#include "List.hpp"
#include "Stack.hpp"
#include "Map.hpp"
#include "Queue.hpp"
#include "Set.hpp"
#include "Multiset.hpp"
#include "Multimap.hpp"
#include "Deque.hpp"

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <deque>

template <class T, class Alloc>
std::ostream&	operator<<(std::ostream& stream, std::vector<T, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename std::vector<T, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::list<T> &e)
{
	stream << "{";
	for (typename std::list<T>::const_iterator it = e.begin(); it != e.end(); it++)
	{
		stream << *it;
		if (it != --e.end())
			std::cout << ", ";
	}
	stream << "}";
	return (stream);
}

template <class Key, class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, std::map<Key, T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename std::map<Key, T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << it->first << ", " << it->second << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class Key, class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, std::multimap<Key, T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename std::multimap<Key, T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << it->first << ", " << it->second << ")";
		if (i != target.size() -1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, std::set<T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename std::set<T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, std::multiset<T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename std::multiset<T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Alloc>
std::ostream&	operator<<(std::ostream& stream, std::deque<T, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename std::deque<T, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::vector<T, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename ft::vector<T, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class Key, class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::map<Key, T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename ft::map<Key, T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << it->first << ", " << it->second << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class Key, class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::multimap<Key, T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename ft::multimap<Key, T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << it->first << ", " << it->second << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::set<T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename ft::set<T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Cmp, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::multiset<T, Cmp, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename ft::multiset<T, Cmp, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template <class T, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::deque<T, Alloc>& target)
{
	std::cout << "{ ";
	size_t i = 0;
	for (typename ft::deque<T, Alloc>::iterator it = target.begin(); it != target.end(); ++it, ++i)
	{
		std::cout << "(" << *it << ")";
		if (i != target.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
	return (stream);
}

template<typename T, class Alloc>
std::ostream&	operator<<(std::ostream& stream, const ft::list<T, Alloc>& target)
{
	stream << "{";
	for (typename ft::list<T, Alloc>::const_iterator it = target.begin(); it != target.end(); it++)
	{
		stream << *it;
		if (ft::fwd(it, 1) != target.end())
			std::cout << ", ";
	}
	stream << "}";
	return (stream);
}

template <typename C>
void	c_info(C& cntr)
{
	std::cout << "size = " << cntr.size() << std::endl;
	std::cout << cntr << std::endl;
}

template <typename A, typename B>
std::ostream &operator<<(std::ostream &stream, const std::pair<A, B> &e)
{
	stream << "(";
	stream << e.first << ", " << e.second;
	stream << ")";
	return (stream);
}
