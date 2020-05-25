/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Containers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:46:12 by lumeyer           #+#    #+#             */
/*   Updated: 2020/03/09 11:30:12 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_HPP
# define CONTAINERS_HPP

#include <stack>
#include <vector>
#include <list>

# include "Vector.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &e)
{
	for (size_t i(0); i < e.size(); i++)
	{
		stream << e[i];
		i == e.size() - 1 ? 0 : std::cout << ", ";
	}
	return (stream);
}

template <typename T>
void	vec_info(ft::Vector<T>& vec)
{
	std::cout << "Vector : " << vec << std::endl;
	std::cout << "Capacity = " << vec.capacity() << ", size = " << vec.size() << std::endl;
}

template <typename T>
void	vec_info(std::vector<T>& vec)
{
	std::cout << "Vector : " << vec << std::endl;
	std::cout << "Capacity = " << vec.capacity() << ", size = " << vec.size() << std::endl;
}

template <typename T>
bool	is_const(const T& ref) { static_cast<void>(ref); return true; }
template <typename T>
bool	is_const(T& ref) { static_cast<void>(ref); return false; }

# include "Stack.hpp"

# include "List.hpp"

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
std::ostream &operator<<(std::ostream &stream, const std::list<T> &e)
{
	stream << "{";
	for (typename std::list<T>::const_iterator it = e.cbegin(); it != e.cend(); it++)
	{
		stream << *it;
		it == --e.cend() ? 0 : std::cout << ", ";
	}
	stream << "}";
	return (stream);
}

#endif