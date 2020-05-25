/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 09:06:03 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:06:43 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vector.hpp"
#include "utils.hpp"

namespace ft {

	template <typename T, class Alloc>
	class deque
	{
		public:

			typedef T				value_type;
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
			size_type		_chunk_size;
			ft::vector<T*>	_pmap;
			allocator_type	_alloc;

			ssize_t			_head;
			size_type		_headchunk;
			ssize_t			_tail;
			size_type		_tailchunk;
			
			void		expand(size_type nb_chunks = 1);
			void		set_empty();
			void		dump_chunks();

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

			explicit deque(const allocator_type& alloc = allocator_type());
			explicit deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template<typename I>
			deque(I first, I last, const allocator_type& alloc = allocator_type());
			deque(const deque<T, Alloc>& target);
			deque<T, Alloc>& 	operator=(const deque<T, Alloc>& target);
			~deque();
			
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
			void					push_back(const value_type& e);
			void					push_front(const value_type& e);
			void					pop_back();
			void					pop_front();
			void					swap(deque<T, Alloc>& x);
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
  			friend bool operator==(const deque<U, V>&, const deque<U, V>&);
			template<typename U, class V>
			friend bool operator!=(const deque<U, V>&, const deque<U, V>&);
			template<typename U, class V>
			friend bool operator<(const deque<U, V>&, const deque<U, V>&);
			template<typename U, class V>
			friend bool operator<=(const deque<U, V>&, const deque<U, V>&);
			template<typename U, class V>
			friend bool operator>(const deque<U, V>&, const deque<U, V>&);
			template<typename U, class V>
			friend bool operator>=(const deque<U, V>&, const deque<U, V>&);
	};

	template <typename T, class Alloc>
	template <bool is_const>
	class deque<T, Alloc>::v_iterator
	{
		friend class deque<T, Alloc>;
		public:
			typedef T value_type;
			typedef typename choose<is_const, const T&, T&>::type reference;
			typedef typename choose<is_const, const T*, T*>::type pointer;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef v_iterator<false> non_const_iterator;
			
			v_iterator() : head(0), dq(nullptr) {}
			v_iterator(const v_iterator<false>& target) : head(target.head), dq(target.dq) {}
			inline v_iterator&	operator=(const v_iterator<false>& target);
			
			~v_iterator() {}
			inline	reference	operator*() { return dq->_pmap[head / dq->_chunk_size][head % dq->_chunk_size]; }
			inline	reference	operator[](difference_type n) { return *(*this + n); }
			inline	reference	operator[](difference_type n) const { *(*this + n); }
			inline	v_iterator	operator+(difference_type n) { v_iterator tmp(*this); while (n--) ++tmp; return tmp; }
			inline  v_iterator&	operator+=(difference_type n) { *this = *this + n; return *this; }
			inline  v_iterator	operator-(difference_type n) { v_iterator tmp(*this); while (n--) --tmp; return tmp; }
			inline  long long	operator-(const v_iterator& other);
			inline  v_iterator&	operator-=(difference_type n) { *this = *this + n; return *this; }
			inline  v_iterator&	operator++();
			inline  v_iterator	operator++(int) { v_iterator tmp(*this); operator++(); return (tmp); }
			inline  v_iterator&	operator--();
			inline  v_iterator	operator--(int) { v_iterator tmp(*this); operator--(); return (tmp); }

			template <bool A, bool B>
			friend inline bool			operator==(v_iterator<A> a, v_iterator<B> b)
			{ return (a.dq && a.dq == b.dq && a.head == b.head); }
			template <bool A, bool B>
			friend inline bool			operator!=(v_iterator<A> a, v_iterator<B> b)
			{ return (a.dq && a.dq == b.dq && a.head != b.head); }
			template <bool A, bool B>
			friend inline bool			operator<(v_iterator<A> a, v_iterator<B> b)
			{
				if (!a.dq || a.dq != b.dq || a.head == -1)
					return false;
				if (b.head == -1)
					return true;
				if (a.dq->_head < a.dq->_tail)
					return a.head < b.head;
				long long diff_a = (long long)a.head - (long long)a.dq->_head;
				long long diff_b = (long long)b.head - (long long)a.dq->_head;
				long long shift_a = circular_clamp(diff_a, 0, a.dq->_capacity);
				long long shift_b = circular_clamp(diff_b, 0, a.dq->_capacity);
				return (shift_a < shift_b);
			}
			template <bool A, bool B>
			friend inline bool			operator<=(v_iterator<A> a, v_iterator<B> b)
			{ return (a.dq && a.dq == b.dq && !(a > b)); }
			template <bool A, bool B>
			friend inline bool			operator>(v_iterator<A> a, v_iterator<B> b)
			{ return (a.dq && a.dq == b.dq && !(a < b) && a != b); }
			template <bool A, bool B>
			friend inline bool			operator>=(v_iterator<A> a, v_iterator<B> b)
			{ return (a.dq && a.dq == b.dq && !(a < b)); }
			
		protected:
			v_iterator(ssize_t index, const deque<T, Alloc>* dq)
				: head(index), dq(dq) {}
			ssize_t					head;
			const deque<T, Alloc>*	dq;

	};

	
	// 888888  dP"Yb   dP"Yb  88     .dP"Y8 
	//   88   dP   Yb dP   Yb 88     `Ybo.
	//   88   Yb   dP Yb   dP 88       `Y8b 
	//   88    YbodP   YbodP  88ood8 8bodP' 


	template <typename T, class Alloc>
	void	deque<T, Alloc>::expand(size_type nb_chunks)
	{
		pointer array = _alloc.allocate(_chunk_size);
		typename ft::vector<pointer>::iterator nchunk = _pmap.insert(_pmap.begin() + _tailchunk + 1, array);
		for (size_type i = _tail % _chunk_size + 1; i < _chunk_size; ++i)
		{
			_alloc.construct(*nchunk + i, _pmap[_tailchunk][i]);
			_alloc.destroy(_pmap[_tailchunk] + i);
		}
		for (size_type i = 0; i < nb_chunks - 1; ++i)
			_pmap.insert(_pmap.begin() + _tailchunk + 1, _alloc.allocate(_chunk_size));
		if (_head == _tail + 1)
		{
			_headchunk += nb_chunks;
			_head += nb_chunks * _chunk_size;
		}
		_capacity += nb_chunks * _chunk_size;
	}

	template <typename T, class Alloc>
	void	deque<T, Alloc>::set_empty()
	{
		_head = -1;
		_tail = -1;
		_headchunk = 0;
		_tailchunk = 0;
	}

	template <typename T, class Alloc>
	void	deque<T, Alloc>::dump_chunks()
	{
		for (typename ft::vector<pointer>::iterator it = _pmap.begin(); it != _pmap.end(); ++it)
		{
			std::cout << "{";
			for (size_type i = 0; i < _chunk_size; ++i)
				std::cout << (*it)[i] << (i == _chunk_size - 1 ? "" : ", ");
			std::cout << "}" << std::endl;
		}
		std::cout << "size of map : " << _pmap.size() << std::endl;
		std::cout << "chunk_size : " << _chunk_size << std::endl;
		std::cout << "capacity : " << _capacity << std::endl;
		std::cout << "size : " << _size << std::endl;
		std::cout << "head : " << _head << std::endl;
		std::cout << "tail : " << _tail << std::endl;
	}


	//  dP""b8 888888  dP"Yb  88""Yb    dP 8888b.  888888  dP"Yb  88""Yb 
	// dP   `"   88   dP   Yb 88__dP   dP   8I  Yb   88   dP   Yb 88__dP 
	// Yb        88   Yb   dP 88"Yb   dP    8I  dY   88   Yb   dP 88"Yb  
	//  YboodP   88    YbodP  88  Yb dP    8888Y"    88    YbodP  88  Yb

	template <typename T, class Alloc>
	deque<T, Alloc>::deque(const allocator_type& alloc)
		: _size(0), _alloc(alloc), _head(-1), _headchunk(0), _tail(-1), _tailchunk(0)
	{
		_chunk_size = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
		// _chunk_size = 4;
		pointer array = _alloc.allocate(_chunk_size);
		_pmap.push_back(array);
		_capacity = _chunk_size;
	}

	template <typename T, class Alloc>
	deque<T, Alloc>::deque(size_t n, const T& val, const allocator_type& alloc)
		: _size(0), _alloc(alloc), _head(-1), _headchunk(0), _tail(-1), _tailchunk(0)
	{
		_chunk_size = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
		pointer array = _alloc.allocate(_chunk_size);
		_pmap.push_back(array);
		_capacity = _chunk_size;
		assign(n, val);
	}

	template <typename T, class Alloc>
	template<typename I>
	deque<T, Alloc>::deque(I first, I last, const allocator_type& alloc)
		: _size(0), _alloc(alloc), _head(-1), _headchunk(0), _tail(-1), _tailchunk(0)
	{
		_chunk_size = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
		pointer array = _alloc.allocate(_chunk_size);
		_pmap.push_back(array);
		_capacity = _chunk_size;
		assign(first, last);
	}

	template <typename T, class Alloc>
	deque<T, Alloc>::deque(const deque<T, Alloc>& target)
		: _size(0), _alloc(target._alloc), _head(-1), _headchunk(0), _tail(-1), _tailchunk(0)
	{
		_chunk_size = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
		pointer array = _alloc.allocate(_chunk_size);
		_pmap.push_back(array);
		_capacity = _chunk_size;
		assign(target.begin(), target.end());
	}

	template <typename T, class Alloc>
	deque<T, Alloc>::~deque()
	{
		for (typename ft::vector<pointer>::iterator it = _pmap.begin(); it != _pmap.end(); ++it)
		{
			for (size_type i = 0; i < _chunk_size; ++i)
				_alloc.destroy(*it + i);
			_alloc.deallocate(*it, _chunk_size);
		}
	}


	// 8b    d8 888888 8b    d8 88""Yb 888888 88""Yb     888888 88   88 88b 88  dP""b8 .dP"Y8 
	// 88b  d88 88__   88b  d88 88__dP 88__   88__dP     88__   88   88 88Yb88 dP   `" `Ybo." 
	// 88YbdP88 88""   88YbdP88 88""Yb 88""   88"Yb      88""   Y8   8P 88 Y88 Yb      o.`Y8b 
	// 88 YY 88 888888 88 YY 88 88oodP 888888 88  Yb     88     `YbodP' 88  Y8  YboodP 8bodP' 

	/* SIZE */
	template <typename T, class Alloc>
	size_t		deque<T, Alloc>::size() const { return (_size); }

	/* RESIZE */
	template <typename T, class Alloc>
	void		deque<T, Alloc>::resize (size_type n, value_type val)
	{
		if (n > max_size() || n < 0)
			return ;
		size_type current_size = _size;
		if (n <= _size)
		{
			for (size_type i = n; i < current_size; ++i)
				_alloc.destroy(&this->at(i));
			_tail = circular_clamp(_tail - (current_size - n), 0, _capacity);
			_size = n;
		}
		else
		{
			for (size_type i(0); i < n - current_size; ++i)
				push_back(val);
		}
	}

	/* MAX_SIZE */
	template <typename T, class Alloc>
	size_t		deque<T, Alloc>::max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }


	/* EMPTY */
	template <typename T, class Alloc>
	bool 		deque<T, Alloc>::empty() const { return (_head == -1 && _tail == -1); }

	/* PUSH_BACK */
	template <typename T, class Alloc>
	void		deque<T, Alloc>::push_back(const T& e)
	{
		if (empty())
		{
			_head = 0;
			_tail = 0;
			_tailchunk = 0;
			_headchunk = 0;
			_alloc.construct(_pmap[0], e);
			++_size;
			return ;
		}
		if (_size == _capacity)
			expand();
		_tail = circular_increment(_tail + 1, _capacity);
		_tailchunk = _tail / _chunk_size;
		_alloc.construct(_pmap[_tailchunk] + (_tail % _chunk_size), e);
		++_size;
	}

	/* POP_BACK */
	template <typename T, class Alloc>
	void		deque<T, Alloc>::pop_back()
	{
		if (empty())
			return ;
		_alloc.destroy(_pmap[_tailchunk] + (_tail % _chunk_size));
		if (_tail == _head)
			set_empty();
		else
		{
			_tail = circular_increment(_tail - 1, _capacity);
			_tailchunk = _tail / _chunk_size;
		}
		--_size;
	}

	/* PUSH_FRONT */
	template <typename T, class Alloc>
	void		deque<T, Alloc>::push_front(const T& e)
	{
		if (empty())
		{
			_head = 0;
			_tail = 0;
			_tailchunk = 0;
			_headchunk = 0;
			_alloc.construct(_pmap[0], e);
			++_size;
			return ;
		}
		if (_size == _capacity)
			expand();
		_head = circular_increment(_head - 1, _capacity);
		_headchunk = _head / _chunk_size;
		_alloc.construct(_pmap[_headchunk] + (_head % _chunk_size), e);
		++_size;
	}

	/* POP_FRONT */
	template <typename T, class Alloc>
	void		deque<T, Alloc>::pop_front()
	{
		if (empty())
			return ;
		_alloc.destroy(_pmap[_headchunk] + (_head % _chunk_size));
		if (_tail == _head)
			set_empty();
		else
		{
			_head = circular_increment(_head + 1, _capacity);
			_headchunk = _head / _chunk_size;
		}
		--_size;
	}


	// /* ITERATEURS */
	template <typename T, class Alloc>
	typename deque<T, Alloc>::const_iterator				deque<T, Alloc>::begin() const { return (const_iterator(_head, this)); }
	template <typename T, class Alloc>
	typename deque<T, Alloc>::iterator				deque<T, Alloc>::begin() { return (iterator(_head, this)); }

	template <typename T, class Alloc>
	typename deque<T, Alloc>::const_iterator				deque<T, Alloc>::end() const { return (const_iterator(-1, this)); }
	template <typename T, class Alloc>
	typename deque<T, Alloc>::iterator				deque<T, Alloc>::end() { return (iterator(-1, this)); }

	template <typename T, class Alloc>
	typename deque<T, Alloc>::const_reverse_iterator		deque<T, Alloc>::rbegin() const { return const_reverse_iterator(end()); }
	template <typename T, class Alloc>
	typename deque<T, Alloc>::reverse_iterator		deque<T, Alloc>::rbegin() { return reverse_iterator(end()); }

	template <typename T, class Alloc>
	typename deque<T, Alloc>::const_reverse_iterator		deque<T, Alloc>::rend() const { return const_reverse_iterator(begin()); }
	template <typename T, class Alloc>
	typename deque<T, Alloc>::reverse_iterator		deque<T, Alloc>::rend() { return reverse_iterator(begin()); }

	/* AT */
	template <typename T, class Alloc>
	T& deque<T, Alloc>::at(size_type i)
	{
		if (i < 0 || i >= size())
			throw std::out_of_range(std::string("Error: tried to access out of bounds element\n"));
		size_type index = (_head + i) % _capacity;
		return (_pmap[index / _chunk_size][index % _chunk_size]);
	}

	template <typename T, class Alloc>
	const T& deque<T, Alloc>::at(size_type i) const
	{
		if (i < 0 || i >= size())
			throw std::out_of_range(std::string("Error: tried to access out of bounds element\n"));
		size_type index = (_head + i) % _capacity;
		return (_pmap[index / _chunk_size][index % _chunk_size]);
	}

	/* FRONT */
	template <typename T, class Alloc>
	T&			deque<T, Alloc>::front()
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return at(0);
	}
	
	template <typename T, class Alloc>
	const T&	deque<T, Alloc>::front() const
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return at(0);
	}

	/* BACK */
	template <typename T, class Alloc>
	T&			deque<T, Alloc>::back()
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return at(_size - 1);
	}
	
	template <typename T, class Alloc>
	const T&	deque<T, Alloc>::back() const
	{
		if (!_size)
			throw std::out_of_range(std::string("Error: out of bounds access"));
		return at(_size - 1);
	}

	// /* ASSIGN */
	template <typename T, class Alloc>
	template<typename I>
	void		deque<T, Alloc>::assign(I first, I last)
	{
		long long n(0);
		n = std::distance(first, last);
		if (n < 0 || (size_type)n > max_size())
			throw std::bad_alloc();
		long long cap = _capacity;
		if (n > cap)
			expand((n - cap) / sizeof(value_type) + 1);
		for (size_type i = 0; i < size(); ++i)
			_alloc.destroy(&this->at(i));
		_size = 0;
		set_empty();
		for (I it = first; it != last; it++)
			push_back(*it);
	}

	template <typename T, class Alloc>
	void		deque<T, Alloc>::assign(size_type n, const value_type& val)
	{
		if (n < 0 || (size_type)n > max_size())
			throw std::bad_alloc();
		if (n > _capacity)
			expand(substract_size_t(n, _capacity) / sizeof(value_type) + 1);
		for (size_type i = 0; i < size(); ++i)
			_alloc.destroy(&this->at(i));
		_size = 0;
		set_empty();
		for (size_type i = 0; i < n; ++i)
			push_back(val);
	}

	// /* INSERT */
	template <typename T, class Alloc>
	typename deque<T, Alloc>::iterator	deque<T, Alloc>::insert(iterator position, const value_type& val)
	{
		if (position == end())
		{
			push_back(val);
			return end() - 1;
		}
		long long n(0);
		n = std::distance(begin(), position);
		if (n < 0 || n > (long long)size())
			throw std::invalid_argument("Error: position iterator is not valid");
		push_back(val);
		for (iterator b = end() - 1; b != position; --b)
		{
			_alloc.destroy(&(*b));
			_alloc.construct(&(*b), *(b - 1));
		}
		_alloc.destroy(&(*position));
		_alloc.construct(&(*position), val);
		return (position);	
	}

	template <typename T, class Alloc>
	void		deque<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		if (position == end())
		{
			for (size_type i(0); i < n; i++)
				push_back(val);
			return ;
		}
		long long d(0);
		d = std::distance(begin(), position);
		if (d < 0 || d > (long long)size())
			throw std::invalid_argument("Error: position iterator is not valid");
		for (size_type i(0); i < n; i++)
			push_back(val);
		for (iterator b = --end(); b != position + n - 1; --b)
		{
			_alloc.destroy(&(*b));
			_alloc.construct(&(*b), *(b - n));
		}
		for (iterator b = position; b != position + n; ++b)
		{
			_alloc.destroy(&(*b));
			_alloc.construct(&(*b), val);
		}
	}

	template <typename T, class Alloc>
	template<typename I>
    void							deque<T, Alloc>::insert(deque<T, Alloc>::iterator position, I first, I last)
	{
		if (position == end())
		{
			for (I it = first; it != last; ++it)
				push_back(*it);
			return ;
		}
		long long d, n;
		d = std::distance(begin(), position);
		n = std::distance(first, last);
		if (d < 0 || d > (long long)size() || n < 0)
			throw std::invalid_argument("Error: invalid iterator(s)");
		for (I it = first; it != last; ++it)
			push_back(*it);
		for (iterator b = --end(); b != position + n - 1; --b)
		{
			_alloc.destroy(&(*b));
			_alloc.construct(&(*b), *(b - n));
		}
		I itb = first;
		for (iterator b = position; b != position + n; ++b, ++itb)
		{
			_alloc.destroy(&(*b));
			_alloc.construct(&(*b), *itb);
		}
	}

	/* ERASE */
	template <typename T, class Alloc>
	typename deque<T, Alloc>::iterator	deque<T, Alloc>::erase (iterator position)
	{
		if (position == end())
		{
			pop_back();
			return end();
		}
		for (iterator it = position; it != this->end() - 1; ++it)
		{
			_alloc.destroy(&(*it));
			_alloc.construct(&(*it), *(it + 1));
		}
		pop_back();
		return (position);
	}

	template <typename T, class Alloc>
	typename deque<T, Alloc>::iterator	deque<T, Alloc>::erase (iterator first, iterator last)
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
	void							deque<T, Alloc>::swap(deque<T, Alloc>& x)
	{
		std::swap(this->_size, x._size);
		std::swap(this->_capacity, x._capacity);
		std::swap(this->_chunk_size, x._chunk_size);
		std::swap(this->_pmap, x._pmap);
		std::swap(this->_alloc, x._alloc);

		std::swap(this->_head, x._head);
		std::swap(this->_headchunk, x._headchunk);
		std::swap(this->_tail, x._tail);
		std::swap(this->_tailchunk, x._tailchunk);
	}

	/* CLEAR */
	template <typename T, class Alloc>
	void							deque<T, Alloc>::clear()
	{
		for (iterator it = begin(); it != end(); ++it)
			_alloc.destroy(&(*it));
		set_empty();
		_size = 0;
	}

	// /* OPERATOR OVERLOADS */
	template <typename T, class Alloc>
	const T& deque<T, Alloc>::operator[](size_type i) const
	{
		i = (_head + i) % _capacity;
		return (_pmap[i / _chunk_size][i % _chunk_size]);
	}

	template <typename T, class Alloc>
	T& deque<T, Alloc>::operator[](size_type i)
	{
		i = (_head + i) % _capacity;
		return (_pmap[i / _chunk_size][i % _chunk_size]);
	}

	template <typename T, class Alloc>
	deque<T, Alloc>& deque<T, Alloc>::operator=(const deque<T, Alloc>& target)
	{
		assign(target.begin(), target.end());
		return *this;
	}

	template <typename U, class V>
  	bool operator==(const deque<U, V>& lhs, const deque<U, V>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}
	
	template <typename U, class V>
	bool operator!=(const deque<U, V>& lhs, const deque<U, V>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename U, class V>
	bool operator<(const deque<U, V>& lhs, const deque<U, V>& rhs)
	{
		return std::lexicographical_compare<typename deque<U, V>::const_iterator, typename deque<U, V>::const_iterator>
		(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename U, class V>
	bool operator<=(const deque<U, V>& lhs, const deque<U, V>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <typename U, class V>
	bool operator>(const deque<U, V>& lhs, const deque<U, V>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <typename U, class V>
	bool operator>=(const deque<U, V>& lhs, const deque<U, V>& rhs)
	{
		return (!(lhs < rhs));
	}

	/* NON-MEMBER SWAP */
	template <typename T, class Alloc>
  	void swap(deque<T, Alloc>& x, deque<T, Alloc>& y)
	{
		deque<T, Alloc> tmp = x;
		x = y;
		y = tmp;
	}

	// 88 888888 888888 88""Yb    db    888888  dP"Yb  88""Yb .dP"Y8 
	// 88   88   88__   88__dP   dPYb     88   dP   Yb 88__dP `Ybo." 
	// 88   88   88""   88"Yb   dP__Yb    88   Yb   dP 88"Yb  o.`Y8b 
	// 88   88   888888 88  Yb dP""""Yb   88    YbodP  88  Yb 8bodP' 
	

	template <typename T, class Alloc>
	template <bool is_const>
	typename deque<T, Alloc>::template v_iterator<is_const>&
	deque<T, Alloc>::v_iterator<is_const>::operator=(const v_iterator<false>& target)
	{
		this->dq = target.dq;
		this->head = target.head;
		return *this;
	}

	template <typename T, class Alloc>
	template <bool is_const>
	typename deque<T, Alloc>::template v_iterator<is_const>&
	deque<T, Alloc>::v_iterator<is_const>::operator++()
	{
		if (head == dq->_tail)
			head = -1;
		else if (head == -1)
			head = dq->_head;
		else
			head = circular_increment(head + 1, dq->_capacity);
		return (*this);
	}
	
	template <typename T, class Alloc>
	template <bool is_const>
	typename deque<T, Alloc>::template v_iterator<is_const>&	deque<T, Alloc>::v_iterator<is_const>::operator--()
	{
		if (head == dq->_head)
			head = -1;
		else if (head == -1)
			head = dq->_tail;
		else
			head = circular_increment(head - 1, dq->_capacity);
		return (*this);
	}
	
	template <typename T, class Alloc>
	template <bool is_const>
	long long	deque<T, Alloc>::v_iterator<is_const>::operator-(const v_iterator& other)
	{
		bool pos = *this > other;
		v_iterator first(!pos ? *this : other);
		v_iterator target(!pos ? other : *this);
		long long count = 0;
		long long sign = pos ? 1 : -1;
		while (true)
		{
			if (first == target)
				return (count * sign);
			++first;
			++count;
			if (count > (long long)dq->_size)
				throw std::invalid_argument("Error: invalid comparison on deque iterator");
		}
	}

}
