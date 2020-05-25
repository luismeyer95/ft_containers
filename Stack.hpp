/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:59:18 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 13:51:11 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vector.hpp"
#include "Deque.hpp"
#include "List.hpp"
#include "utils.hpp"

namespace ft {

	template<typename T, class C>
	class stack
	{
		public:
			C					c;
			typedef T			value_type;
			typedef	C			container_type;
			typedef size_t		size_type;
			explicit stack(const container_type& ctnr = container_type());
			bool				empty() const;
			size_type			size() const;
			value_type&			top();
			const value_type&	top() const;
			void				push(const value_type& val);
			void				pop();
	};

	template<typename T, class C>
	stack<T, C>::stack(const container_type& ctnr) { c = ctnr; }

	template<typename T, class C>
	bool							stack<T, C>::empty() const { return (c.empty()); }

	template<typename T, class C>
	typename stack<T, C>::size_type			stack<T, C>::size() const { return (c.size()); }

	template<typename T, class C>
	typename stack<T, C>::value_type&		stack<T, C>::top() { return (c.back()); }

	template<typename T, class C>
	const typename stack<T, C>::value_type&	stack<T, C>::top() const { return (c.back()); }

	template<typename T, class C>
	void							stack<T, C>::push(const value_type& val) { c.push_back(val); }

	template<typename T, class C>
	void							stack<T, C>::pop() { c.pop_back(); }

	template <class T, class C>
  	bool operator== (const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.c == rhs.c; }
	template <class T, class C>
  	bool operator!= (const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.c != rhs.c; }
	template <class T, class C>
  	bool operator<  (const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.c < rhs.c; }
	template <class T, class C>
  	bool operator<= (const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.c <= rhs.c; }
	template <class T, class C>
  	bool operator>  (const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.c > rhs.c; }
	template <class T, class C>
  	bool operator>= (const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.c >= rhs.c; }

}