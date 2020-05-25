/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:24:36 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 13:27:41 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "List.hpp"
#include "Deque.hpp"
#include "utils.hpp"

namespace ft {

	template<typename T, class C>
	class queue
	{
		public:
			C					c;
			typedef T			value_type;
			typedef	C			container_type;
			typedef size_t		size_type;
			explicit queue(const container_type& ctnr = container_type());
			bool				empty() const;
			size_type			size() const;
			value_type&			front();
			const value_type&	front() const;
			value_type&			back();
			const value_type&	back() const;
			void				push(const value_type& val);
			void				pop();
	};

	template<typename T, class C>
	queue<T, C>::queue(const container_type& ctnr) { c = ctnr; }

	template<typename T, class C>
	bool							queue<T, C>::empty() const { return (c.empty()); }

	template<typename T, class C>
	typename queue<T, C>::size_type			queue<T, C>::size() const { return (c.size()); }

	template<typename T, class C>
	typename queue<T, C>::value_type&			queue<T, C>::front() { return (c.front()); }
	template<typename T, class C>
	const typename queue<T, C>::value_type&		queue<T, C>::front() const { return (c.front()); }
	template<typename T, class C>
	typename queue<T, C>::value_type&			queue<T, C>::back() { return (c.back()); }
	template<typename T, class C>
	const typename queue<T, C>::value_type&		queue<T, C>::back() const { return (c.back()); }

	template<typename T, class C>
	void							queue<T, C>::push(const value_type& val) { c.push_back(val); }

	template<typename T, class C>
	void							queue<T, C>::pop() { c.pop_front(); }

	template <class T, class C>
  	bool operator== (const queue<T, C>& lhs, const queue<T, C>& rhs) { return lhs.c == rhs.c; }
	template <class T, class C>
  	bool operator!= (const queue<T, C>& lhs, const queue<T, C>& rhs) { return lhs.c != rhs.c; }
	template <class T, class C>
  	bool operator<  (const queue<T, C>& lhs, const queue<T, C>& rhs) { return lhs.c < rhs.c; }
	template <class T, class C>
  	bool operator<= (const queue<T, C>& lhs, const queue<T, C>& rhs) { return lhs.c <= rhs.c; }
	template <class T, class C>
  	bool operator>  (const queue<T, C>& lhs, const queue<T, C>& rhs) { return lhs.c > rhs.c; }
	template <class T, class C>
  	bool operator>= (const queue<T, C>& lhs, const queue<T, C>& rhs) { return lhs.c >= rhs.c; }

}