/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:33:13 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/27 13:12:04 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseIterators.hpp"

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

			template <typename U, bool is_const>
			class v_iterator : public base_v_iterator<U, is_const>
			{
				protected:
					using base_v_iterator<U, is_const>::ptr;
					using base_v_iterator<U, is_const>::get;
				public:
					typedef U value_type;
					typedef typename choose<is_const, const U&, U&>::type reference;
					typedef typename choose<is_const, const U*, U*>::type pointer;
					typedef std::ptrdiff_t difference_type;
					typedef std::random_access_iterator_tag iterator_category;
					typedef typename remove_const<U>::type non_const_type;
					typedef v_iterator<non_const_type, false> non_const_iterator;
					
					v_iterator() : base_v_iterator<U, is_const>() {}
					v_iterator(const base_v_iterator<non_const_type, false>& it) : base_v_iterator<U, is_const>(it.ptr) {}
					v_iterator(const v_iterator<non_const_type, false>& target) : base_v_iterator<U, is_const>(target) {}
					using base_v_iterator<U, is_const>::operator=;
					~v_iterator() {}
			};
			
			template <typename I>
			class v_reverse_iterator : public base_reverse_iterator<I>
			{
				protected:
					using base_reverse_iterator<I>::itbase;
					typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;
				public:
					v_reverse_iterator()
						: base_reverse_iterator<I>() {}
					v_reverse_iterator(const v_reverse_iterator<non_const_iterator>& it)
						: base_reverse_iterator<I>(it) {}
					v_reverse_iterator(const base_reverse_iterator<I>& rev_it)
						: base_reverse_iterator<I>(rev_it.itbase) {}
					using base_reverse_iterator<I>::operator=;
					~v_reverse_iterator() {}
			};

			template <typename U, bool is_const>
			inline const base_v_iterator<U, is_const>& bcast(const v_iterator<U, is_const>& it) const
			{
				return *(base_v_iterator<U, is_const>*)&it;
			}
			
		public:

			explicit vector(const allocator_type& alloc = allocator_type());
			explicit vector(size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template<typename I>
			vector(I first, I last, const allocator_type& alloc = allocator_type());
			vector(const vector<T, Alloc>& target);
			vector<T, Alloc>& 	operator=(const vector<T, Alloc>& target);
			~vector();
			
			
			typedef v_iterator<T, false> iterator;
			typedef v_iterator<const T, true> const_iterator;
			typedef v_reverse_iterator<iterator> reverse_iterator;
			typedef v_reverse_iterator<const_iterator> const_reverse_iterator;
			
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
	size_t		vector<T, Alloc>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(value_type));
	}

	/* CAPACITY */
	template <typename T, class Alloc>
	size_t		vector<T, Alloc>::capacity() const
	{
		return (_capacity);
	}

	/* EMPTY */
	template <typename T, class Alloc>
	bool 		vector<T, Alloc>::empty() const
	{
		return (!_size);
	}

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
	void		vector<T, Alloc>::pop_back()
	{
		if (_size)
		{
			_alloc.destroy(_array + _size - 1);
			--_size;
		}
	}


	/* ITERATEURS */
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator
	vector<T, Alloc>::begin() const { return (const_iterator(_array)); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::begin() { return (iterator(_array)); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator
	vector<T, Alloc>::end() const { return (const_iterator(_array + _size)); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::end() { return (iterator(_array + _size)); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::rbegin() const { return const_reverse_iterator(end()); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator
	vector<T, Alloc>::rbegin() { return reverse_iterator(end()); }

	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::rend() const { return const_reverse_iterator(begin()); }
	
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator
	vector<T, Alloc>::rend() { return reverse_iterator(begin()); }

	/* AT */
	template <typename T, class Alloc>
	T& vector<T, Alloc>::at(size_type i)
	{
		if (i < 0 || i >= size())
			throw std::out_of_range(std::string("Error: out of bounds access"));
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
	T&			vector<T, Alloc>::front()
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (_array[0]);
	}
	
	template <typename T, class Alloc>
	const T&	vector<T, Alloc>::front() const
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (_array[0]);
	}

	/* BACK */
	template <typename T, class Alloc>
	T&			vector<T, Alloc>::back()
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (_array[_size - 1]);
	}
	
	template <typename T, class Alloc>
	const T&	vector<T, Alloc>::back() const
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return (_array[_size - 1]);
	}

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
			_alloc.destroy(bcast(b).ptr);
			_alloc.construct(bcast(b).ptr, *(b - 1));
		}
		*position = val;
		_size++;
		return (position);	
	}

	template <typename T, class Alloc>
	void	vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		size_type ind(0);
		for (iterator b = begin(); b != position; b++, ind++) {}
		for (size_type i(0); i < n; i++)
			push_back(val);
		position = _array + ind;
		for (iterator b = --end(); b != position + n - 1; b--)
		{
			_alloc.destroy(bcast(b).ptr);
			_alloc.construct(bcast(b).ptr, *(b - n));
		}
		for (iterator b = position; b != position + n; b++)
		{
			_alloc.destroy(bcast(b).ptr);
			_alloc.construct(bcast(b).ptr, val);
		}
	}

	template <typename T, class Alloc>
	template<typename I>
    void	vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, I first, I last)
	{
		size_type ind(0);
		size_type n(0);

		for (iterator b = begin(); b != position; b++, ind++) {}
		for (I it = first; it != last; it++, n++)
			push_back(*it);
		position = iterator(_array + ind);
		for (iterator b = --end(); b != position + n - 1; b--)
		{
			_alloc.destroy(bcast(b).ptr);
			_alloc.construct(bcast(b).ptr, *(b - n));
		}
		I itb = first;
		for (iterator b = position; itb != last; b++, itb++)
		{
			_alloc.destroy(bcast(b).ptr);
			_alloc.construct(bcast(b).ptr, *itb);
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
			_alloc.destroy(bcast(it).ptr);
			_alloc.construct(bcast(it).ptr, *(it + 1));
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
	void	vector<T, Alloc>::swap(vector<T, Alloc>& x)
	{
		std::swap(this->_capacity, x._capacity);
		std::swap(this->_size, x._size);
		std::swap(this->_array, x._array);
	}

	/* CLEAR */
	template <typename T, class Alloc>
	void	vector<T, Alloc>::clear()
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
		return std::lexicographical_compare<
			base_v_iterator<const U, true>,
			base_v_iterator<const U, true> >
		(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		return true;
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