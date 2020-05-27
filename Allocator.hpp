/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:11:55 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/27 12:18:18 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include <functional>

namespace ft {

	template <class T>
   	class allocator {

		public:
		
			typedef T					value_type;
			typedef T*					pointer;
			typedef const T*			const_pointer;
			typedef T&					reference;
			typedef const T& 			const_reference;
			typedef size_t				size_type;
			typedef ::std::ptrdiff_t	difference_type;

			template <class U>
			struct rebind {
				typedef allocator<U> other;
			};

			pointer address(reference value) const { return &value; }
			const_pointer address(const_reference value) const { return &value; }

			allocator() throw() {}
			allocator(const allocator&) throw() {}
			template <class U>
			allocator (const allocator<U>&) throw() {}
			~allocator() throw() {}

			size_type max_size() const throw() {
				return std::numeric_limits<size_t>::max() / sizeof(T);
			}

			pointer allocate(size_type num) {
				pointer ret = (pointer)(::operator new(num * sizeof(T)));
				return ret;
			}

			void construct(pointer p, const T& value) {
				new ((void*)p) T(value);
			}

			void destroy(pointer p) {
				p->~T();
			}

			void deallocate(pointer p, size_type num) {
				(void)num;
				::operator delete((void*)p);
			}
   };
}
