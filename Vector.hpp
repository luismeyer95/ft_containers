/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:33:13 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:58:10 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

namespace ft {

	template <typename T, class Alloc>
	class vector
	{
		public:
			typedef T				value_type;
			typedef	const T			const_value_type;
			typedef Alloc			allocator_type;
			typedef	T& 				reference;
			typedef	const T& 		const_reference;
			typedef	T* 				pointer;
			typedef	const T* 		const_pointer;
			typedef size_t			size_type;
			typedef std::ptrdiff_t 	difference_type;
		protected:
			size_type		_size;
			size_type		_capacity;
			T*				_array;
			allocator_type	_alloc;
			void		realloc(size_type nsize);

			template <bool is_const>
			class v_iterator;
			
			template <bool is_const>
			class v_reverse_iterator : public reverse_iterator< v_iterator<is_const> >
			{
				private:
					typedef ft::reverse_iterator< v_iterator<is_const> > reverse_iterator;
				public:
					v_reverse_iterator()
						: reverse_iterator() {}
					explicit v_reverse_iterator(const v_iterator<is_const>& it)
						: reverse_iterator(it) {}
					v_reverse_iterator(const ft::reverse_iterator< v_iterator<false> >& rev_it)
						: reverse_iterator(rev_it) {}
					~v_reverse_iterator() {}
			};
			
		public:

			explicit vector(const allocator_type& alloc = allocator_type());
			explicit vector(size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template<typename I>
			vector(I first, I last, const allocator_type& alloc = allocator_type());
			vector(const vector<T, Alloc>& target);
			vector<T, Alloc>& 	operator=(const vector<T, Alloc>& target);
			~vector();
			
			
			typedef v_iterator<false> iterator;
			typedef v_iterator<true> const_iterator;
			typedef v_reverse_iterator<false> reverse_iterator;
			typedef v_reverse_iterator<true> const_reverse_iterator;
			
			size_type				size() const;
			void					resize (size_type n, value_type val = value_type());
			size_type				max_size() const;
			size_type				capacity() const;
			bool					empty() const;
			void					reserve(size_type n);
			void					push_back(const T& e);
			void					pop_back();
			void					swap(vector<T, Alloc>& x);
			void					clear();

			const_iterator			begin() const;
			iterator				begin();
			const_iterator			end() const;
			iterator				end();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rend() const;
			reverse_iterator		rend();

			template<typename I>
			void					assign(I first, I last);
			void					assign(size_type n, const value_type& val);

			iterator				insert(iterator position, const value_type& val = value_type());
			template <typename I>
    		void					insert(iterator position, I first, I last);
			void					insert(iterator position, size_type n, const value_type& val = value_type());

			iterator				erase (iterator position);
			iterator				erase (iterator first, iterator last);

			reference 				operator[](size_type i);
			const_reference			operator[](size_type i) const;
			reference 				at(size_type n);
			const_reference 		at(size_type n) const;
			reference				front();
			const_reference			front() const;
			reference				back();
			const_reference			back() const;

			template<typename U, class V>
  			friend bool operator==(const vector<U, V>&, const vector<U, V>&);
			template<typename U, class V>
			friend bool operator!=(const vector<U, V>&, const vector<U, V>&);
			template<typename U, class V>
			friend bool operator<(const vector<U, V>&, const vector<U, V>&);
			template<typename U, class V>
			friend bool operator<=(const vector<U, V>&, const vector<U, V>&);
			template<typename U, class V>
			friend bool operator>(const vector<U, V>&, const vector<U, V>&);
			template<typename U, class V>
			friend bool operator>=(const vector<U, V>&, const vector<U, V>&);
	};

	template <typename T, class Alloc>
	template <bool is_const>
	class vector<T, Alloc>::v_iterator
	{
		friend class vector<T, Alloc>;
		public:
			typedef T value_type;
			typedef typename choose<is_const, const T&, T&>::type reference;
			typedef typename choose<is_const, const T*, T*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef v_iterator<false> non_const_iterator;
			
			v_iterator() : ptr(nullptr) {}
			v_iterator(pointer p) : ptr(p) {}
			v_iterator(const v_iterator<false>& target) { this->ptr = target.ptr; }
			inline v_iterator&	operator=(const v_iterator<false>& target) { this->ptr = target.ptr; return *this; }
			
			~v_iterator() {}
			inline	reference	operator*() { return *ptr; }
			inline	reference	operator[](difference_type n) { return ptr[n]; }
			inline	reference	operator[](difference_type n) const { return ptr[n]; }
			inline	v_iterator	operator+(difference_type n) { return v_iterator(ptr + n); }
			inline  v_iterator&	operator+=(difference_type n) { ptr += n; return *this; }
			inline  v_iterator	operator-(difference_type n) { return v_iterator(ptr - n); }
			inline  long long	operator-(const v_iterator& other) {
				return ((long long)ptr - (long long)other.ptr) / (long long)sizeof(value_type);
			}
			inline  v_iterator&	operator-=(difference_type n) { ptr -= n; return *this; }
			inline  v_iterator&	operator++() { ptr++; return (*this); }
			inline  v_iterator	operator++(int) { v_iterator tmp(ptr); operator++(); return (tmp); }
			inline  v_iterator&	operator--() { ptr--; return (*this); }
			inline  v_iterator	operator--(int) { v_iterator tmp(ptr); operator--(); return (tmp); }

			template <bool A, bool B>
			friend inline bool			operator==(v_iterator<A> a, v_iterator<B> b) { return (a.ptr == b.ptr); }
			template <bool A, bool B>
			friend inline bool			operator!=(v_iterator<A> a, v_iterator<B> b) { return (a.ptr != b.ptr); }
			template <bool A, bool B>
			friend inline bool			operator<(v_iterator<A> a, v_iterator<B> b) { return (a.ptr < b.ptr); }
			template <bool A, bool B>
			friend inline bool			operator<=(v_iterator<A> a, v_iterator<B> b) { return (a.ptr <= b.ptr); }
			template <bool A, bool B>
			friend inline bool			operator>(v_iterator<A> a, v_iterator<B> b) { return (a.ptr > b.ptr); }
			template <bool A, bool B>
			friend inline bool			operator>=(v_iterator<A> a, v_iterator<B> b) { return (a.ptr >= b.ptr); }
			
		protected:
			pointer			ptr;
			inline pointer&	get() { return (ptr); }

	};

	/* CONSTRUCTORS + DESTRUCTOR */
	template <typename T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc)
		: _size(0), _capacity(0), _array(nullptr), _alloc(alloc) {}

	template <typename T, class Alloc>
	vector<T, Alloc>::vector(size_t n, const T& val, const allocator_type& alloc)
		: _size(n), _capacity(n), _alloc(alloc)
	{
		_array = _alloc.allocate(_size);
		for (size_t i(0); i < _size; i++)
			_alloc.construct(_array + i, val);
	}

	template <typename T, class Alloc>
	template<typename I>
	vector<T, Alloc>::vector(I first, I last, const allocator_type& alloc)
		: _size(0), _capacity(0), _array(nullptr), _alloc(alloc)
	{
		this->assign(first, last);
	}

	template <typename T, class Alloc>
	vector<T, Alloc>::vector(const vector<T, Alloc>& target) : _array(nullptr) { *this = target; }

	template <typename T, class Alloc>
	vector<T, Alloc>::~vector()
	{
		for (size_type i = 0; i < _size; ++i)
			_alloc.destroy(_array + i);
		_alloc.deallocate(_array, _size);	
	}

	template <typename T, class Alloc>
	void	vector<T, Alloc>::realloc(size_t nsize)
	{
		_capacity = nsize;
		T* copy = _alloc.allocate(_capacity);
		for (size_t i(0); i < _size; i++)
			_alloc.construct(copy + i, _array[i]);
		if (_array)
		{
			for (size_type i = 0; i < _size; ++i)
				_alloc.destroy(_array + i);
			_alloc.deallocate(_array, _size);
		}
		_array = copy;
	}

	/* SIZE */
	template <typename T, class Alloc>
	size_t		vector<T, Alloc>::size() const { return (_size); }

	/* RESIZE */
	template <typename T, class Alloc>
	void		vector<T, Alloc>::resize (size_type n, value_type val)
	{
		if (n > max_size())
			return ;
		if (n <= (size_type)_size)
			_size = n;
		else
		{
			size_type current_size = _size;
			for (size_type i(0); i < n - current_size; ++i)
				push_back(val);
		}
	}

	/* MAX_SIZE */
	template <typename T, class Alloc>
	size_t		vector<T, Alloc>::max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }

	/* CAPACITY */
	template <typename T, class Alloc>
	size_t		vector<T, Alloc>::capacity() const { return (_capacity); }

	/* EMPTY */
	template <typename T, class Alloc>
	bool 		vector<T, Alloc>::empty() const { return (_size == 0); }

	/* RESERVE */
	template <typename T, class Alloc>
	void		vector<T, Alloc>::reserve(size_type n)
	{
		if (n > max_size())
			throw std::length_error("Error: reserve() parameter greater than container's max_size()");
		else if (n > _capacity)
			realloc(n);
	}

	/* PUSH_BACK */
	template <typename T, class Alloc>
	void		vector<T, Alloc>::push_back(const T& e)
	{
		if (_size == _capacity)
			realloc(_capacity ? _capacity * 2 : 1);
		_alloc.construct(_array + _size, e);
		_size++;
	}

	/* POP_BACK */
	template <typename T, class Alloc>
	void		vector<T, Alloc>::pop_back() { _size ? _size-- : 0; }


	/* ITERATEURS */
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator				vector<T, Alloc>::begin() const { return (const_iterator(_array)); }
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator				vector<T, Alloc>::begin() { return (iterator(_array)); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator				vector<T, Alloc>::end() const { return (const_iterator(_array + _size)); }
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator				vector<T, Alloc>::end() { return (iterator(_array + _size)); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator		vector<T, Alloc>::rbegin() const { return const_reverse_iterator(end()); }
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator		vector<T, Alloc>::rbegin() { return reverse_iterator(end()); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator		vector<T, Alloc>::rend() const { return const_reverse_iterator(begin()); }
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator		vector<T, Alloc>::rend() { return reverse_iterator(begin()); }

	/* AT */
	template <typename T, class Alloc>
	T& vector<T, Alloc>::at(size_type i)
	{
		if (i < 0 || i >= size())
			throw std::out_of_range(std::string("vector"));
		return (_array[i]);
	}

	template <typename T, class Alloc>
	const T& vector<T, Alloc>::at(size_type i) const
	{
		if (i < 0 || i >= size())
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (_array[i]);
	}

	/* FRONT */
	template <typename T, class Alloc>
	T&			vector<T, Alloc>::front() { if (!_size) { throw std::out_of_range(std::string("Error: out of bounds access")); } return (_array[0]); }
	template <typename T, class Alloc>
	const T&	vector<T, Alloc>::front() const { if (!_size) { throw std::out_of_range(std::string("Error: out of bounds access")); } return (_array[0]); }

	/* BACK */
	template <typename T, class Alloc>
	T&			vector<T, Alloc>::back() { if (!_size) { throw std::out_of_range(std::string("Error: out of bounds access")); } return (_array[_size - 1]); }
	template <typename T, class Alloc>
	const T&	vector<T, Alloc>::back() const { if (!_size) { throw std::out_of_range(std::string("Error: out of bounds access")); } return (_array[_size - 1]); }

	/* ASSIGN */
	template <typename T, class Alloc>
	template<typename I>
	void		vector<T, Alloc>::assign(I first, I last)
	{
		size_type n(0);
		for (I it = first; it != last; it++, n++) {}
		if (n > _capacity)
			realloc(n);
		for (size_type i = 0; i < size(); ++i)
			_alloc.destroy(&at(i));
		_size = 0;
		for (I it = first; it != last; it++)
			push_back(*it);
	}

	template <typename T, class Alloc>
	void		vector<T, Alloc>::assign(size_type n, const value_type& val)
	{
		if (n < 0)
			throw std::bad_alloc();
		if (n > _capacity)
			realloc(n);
		for (size_type i = 0; i < size(); ++i)
			_alloc.destroy(&at(i));
		_size = 0;
		for (size_type i(0); i < n; i++)
			push_back(val);
	}

	/* INSERT */
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::insert(iterator position, const value_type& val)
	{
		size_type ind(0);
		for (iterator b = begin(); b != position; b++, ind++) {  }
		if (_size == _capacity)
		{
			realloc(_capacity ? _capacity * 2 : 1);
			position = _array + ind;
		}
		for (iterator b = this->end(); b != position; b--)
		{
			_alloc.destroy(b.get());
			_alloc.construct(b.get(), *(b - 1));
		}
		*position = val;
		_size++;
		return (position);	
	}

	template <typename T, class Alloc>
	void					vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		size_type ind(0);
		for (iterator b = begin(); b != position; b++, ind++) {}
		for (size_type i(0); i < n; i++)
			push_back(val);
		position = _array + ind;
		for (iterator b = --end(); b != position + n - 1; b--)
		{
			_alloc.destroy(b.get());
			_alloc.construct(b.get(), *(b - n));
		}
		for (iterator b = position; b != position + n; b++)
		{
			_alloc.destroy(b.get());
			_alloc.construct(b.get(), val);
		}
	}

	template <typename T, class Alloc>
	template<typename I>
    void							vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, I first, I last)
	{
		size_type ind(0);
		size_type n(0);

		for (iterator b = begin(); b != position; b++, ind++) {}
		for (I it = first; it != last; it++, n++)
			push_back(*it);
		position = iterator(_array + ind);
		for (iterator b = --end(); b != position + n - 1; b--)
		{
			_alloc.destroy(b.get());
			_alloc.construct(b.get(), *(b - n));
		}
		I itb = first;
		for (iterator b = position; itb != last; b++, itb++)
		{
			_alloc.destroy(b.get());
			_alloc.construct(b.get(), *itb);
		}
	}

	/* ERASE */
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase (iterator position)
	{
		if (position == end())
		{
			pop_back();
			return end();
		}
		for (iterator it = position; it != this->end() - 1; ++it)
		{
			_alloc.destroy(it.get());
			_alloc.construct(it.get(), *(it + 1));
		}
		_alloc.destroy(_array + _size - 1);
		_size--;
		return (position);
	}

	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase (iterator first, iterator last)
	{
		long long n = std::distance(first, last);
		if (n < 0)
			throw std::invalid_argument("Error: invalid iterator(s)");
		if (last == end())
		{
			for (long long i = 0; i < n; ++i)
				pop_back();
			return end();
		}
		for (iterator it = last; it != end(); ++it)
		{
			_alloc.destroy(&(*(it - n)));
			_alloc.construct(&(*(it - n)), *it);
		}
		for (long long i = 0; i < n; ++i)
			pop_back();
		return (first);
	}

	/* SWAP */
	template <typename T, class Alloc>
	void							vector<T, Alloc>::swap(vector<T, Alloc>& x)
	{
		std::swap(this->_capacity, x._capacity);
		std::swap(this->_size, x._size);
		std::swap(this->_array, x._array);
	}

	/* CLEAR */
	template <typename T, class Alloc>
	void							vector<T, Alloc>::clear()
	{
		for (size_type i = 0; i < _size; ++i)
			_alloc.destroy(_array + i);
		_size = 0;
	}

	/* OPERATOR OVERLOADS */
	template <typename T, class Alloc>
	const T& vector<T, Alloc>::operator[](size_type i) const { return (_array[i]); }
	template <typename T, class Alloc>
	T& vector<T, Alloc>::operator[](size_type i) { return (_array[i]); }

	template <typename T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& target)
	{
		if (_array)
		{
			for (size_type i = 0; i < _size; ++i)
				_alloc.destroy(_array + i);
			_alloc.deallocate(_array, _size);
		}
		_size = target.size();
		_capacity = target._capacity;
		_array = _alloc.allocate(_capacity);
		for (size_t i(0); i < _size; i++)
			_alloc.construct(_array + i, target[i]);
		return (*this);
	}

	template <typename U, class V>
  	bool operator==(const vector<U, V>& lhs, const vector<U, V>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i(0); i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	
	template <typename U, class V>
	bool operator!=(const vector<U, V>& lhs, const vector<U, V>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename U, class V>
	bool operator<(const vector<U, V>& lhs, const vector<U, V>& rhs)
	{
		return std::lexicographical_compare<typename vector<U, V>::const_iterator, typename vector<U, V>::const_iterator>
		(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename U, class V>
	bool operator<=(const vector<U, V>& lhs, const vector<U, V>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <typename U, class V>
	bool operator>(const vector<U, V>& lhs, const vector<U, V>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <typename U, class V>
	bool operator>=(const vector<U, V>& lhs, const vector<U, V>& rhs)
	{
		return (!(lhs < rhs));
	}

	/* NON-MEMBER SWAP */
	template <typename T, class Alloc>
  	void swap (vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		vector<T, Alloc> tmp = x;
		x = y;
		y = tmp;
	}

}