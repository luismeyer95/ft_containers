/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Containers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:46:12 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 13:31:27 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_HPP
# define CONTAINERS_HPP

#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include "../utils.hpp"

template <typename T, class Alloc>
std::ostream &operator<<(std::ostream &stream, const std::vector<T, Alloc> &e)
{
	for (size_t i(0); i < e.size(); i++)
	{
		stream << e[i];
		if (i != e.size() - 1)
			std::cout << ", ";
	}
	return (stream);
}

template <typename T, class Alloc>
void	vec_info(std::vector<T, Alloc>& vec)
{
	std::cout << "Vector : " << vec << std::endl;
	std::cout << "Capacity = " << vec.capacity() << ", size = " << vec.size() << std::endl;
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

template <class Key, class T, class Cmp, class Alloc>
void	map_info(std::map<Key, T, Cmp, Alloc>& map)
{
	std::cout << "Map: " << map;
	std::cout << "Size = " << map.size() << std::endl << std::endl;
}

template <typename T>
void	lst_info(const std::list<T>& lst)
{
	std::cout << "size = " << lst.size() << std::endl;
	std::cout << lst << std::endl;
}

template <typename A, typename B>
std::ostream &operator<<(std::ostream &stream, const std::pair<A, B> &e)
{
	stream << "(";
	stream << e.first << ", " << e.second;
	stream << ")";
	return (stream);
}

template<typename T, class Alloc>
std::ostream&	operator<<(std::ostream& stream, ft::vector<T, Alloc>& target)
{
	for (size_t i(0); i < target.size(); i++)
	{
		stream << target[i];
		if (i != target.size() - 1)
			std::cout << ", ";
	}
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

// template <typename C>
// std::ostream &operator<<(std::ostream &stream, const C &e)
// {
// 	stream << "{";
// 	for (typename C::const_iterator it = e.begin(); it != e.end(); it++)
// 	{
// 		stream << *it;
// 		it == --e.end() ? 0 : stream << ", ";
// 	}
// 	stream << "}";
// 	return (stream);
// }

template <typename C>
void	c_info(C& cntr)
{
	std::cout << "size = " << cntr.size() << std::endl;
	std::cout << cntr << std::endl;
}

#endif
