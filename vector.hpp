#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include "util.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public :
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::vectorIterator<T> iterator;
		typedef typename ft::vectorIterator<const T> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename std::size_t size_type;

		explicit vector(const allocator_type &alloc = allocator_type()){
			_alloc = alloc;
			_start = NULL;
			_size = 0;
			_capacity = 0;
		};
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()){
			_alloc = alloc;
			_start = _alloc.allocate(n);
			_size = n;
			_capacity = n;
			std::uninitialized_fill(_start, _start + n, val); 
		};
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
			_alloc = alloc;
			_size = std::distance(first, last);
			_capacity = _size;
			_start = _alloc.allocate(_capacity);
			std::uninitialized_copy(first, last , _start);
		}
		vector(const vector &x) : _size(0), _capacity(0){
			*this = x;
		};
		~vector(){
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			if (_capacity > 0){
				_alloc.deallocate(_start, _capacity);
			}
		};
		vector& operator= (const vector& x){
			if (_size > 0)
				clear();
			if (_capacity > 0)
				_alloc.deallocate(_start, _capacity);
			if (_capacity < x.capacity())
			{
				_start = _alloc.allocate(x._size);
				_capacity = x._size;
			}
			_size = x._size;
			size_type i = 0;
			while (i < x._size)
			{
				_alloc.construct(_start + i, x[i]);
				i++;
			}
			return (*this);
		};

		iterator begin(){return (iterator(_start));}
		const_iterator begin() const {return (const_iterator(_start));}
		iterator end(){return (iterator(_start + _size));}
		const_iterator end() const {return (const_iterator(_start + _size));}
		reverse_iterator rbegin(){return (reverse_iterator(end()));}
		const_reverse_iterator rbegin() const{return (const_reverse_iterator(end()));}
		reverse_iterator rend(){return (reverse_iterator(begin()));}
		const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}

		size_type size() const{return (_size);}
		size_type max_size() const{return (_alloc.max_size());}
		void resize (size_type n, value_type val = value_type()){
			size_type i = 0;
			if (n < _size)
			{
				while (i + n < _size)
				{
					_alloc.destroy(_start + i + n);
					i++;
				}
				_size = n;
				
			}
			else if (n > _size)
			{
				if (_capacity < n && n < _capacity * 2)
				{
					_capacity *= 2;
					reserve(_capacity);
				}
				else if (n > _capacity * 2)
				{
					_capacity = n;
					reserve(_capacity);
				}
				while (_size + i < n)
				{
					_alloc.construct(_start + _size + i, val);
					i++;
				}
				_size = n;
			}
		}
		size_type capacity() const{return (_capacity);}
		bool empty() const{ return (_size == 0);}
		void reserve(size_type n){
			if (_capacity >= n)
				return ;
			pointer new_start;
			new_start = _alloc.allocate(n);
			size_type i = 0;
			while (i < _size)
			{
				_alloc.construct(new_start + i, *(_start + i));
				i++;
			}
			if (_capacity > 0)
				_alloc.deallocate(_start, _capacity);
			_start = new_start;
			_capacity = n;
		}

		reference operator[](size_type n){return (*(_start + n));}
		const_reference operator[](size_type n) const{return (*(_start + n));}
		reference at(size_type n){
			if(n > _capacity)
				throw std::out_of_range("out_of_range");
			return (*(_start + n));}
		const_reference at(size_type n) const{
			if(n > _capacity)
				throw std::out_of_range("out_of_range");
			return (*(_start + n));}
		reference front(){return *(_start);}
		const_reference front() const {return *(_start);}
		reference back(){return *(_start + _size - 1);}
		const_reference back() const{ return *(_start + _size - 1);}

		void assign (size_type n, const value_type& val){
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			if (_capacity < n)
			{
				if (_capacity > 0)
					_alloc.deallocate(_start, _capacity);
				_start = _alloc.allocate(n);
				_capacity = n;
			}
			_size = n;
			std::uninitialized_fill(_start, _start + n, val);
		};
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			if (_capacity < static_cast<size_type>(std::distance(first, last)))
			{
				if (_capacity > 0)
					_alloc.deallocate(_start, _capacity);
				_start = _alloc.allocate(std::distance(first, last));
				_capacity = std::distance(first, last);
			}
			std::uninitialized_copy(first, last, _start);
			_size = std::distance(first, last);
		};
		void push_back(const value_type &val){
			if (_capacity == 0)
				reserve(1);
			else if (_size == _capacity)
				reserve(_capacity * 2);
			_alloc.construct(_start + _size, val);
			_size++;
		};
		void pop_back(){
			_alloc.destroy(_start + _size - 1);
			_size--;
		}
		iterator insert (iterator position, const value_type& val){
			if (_capacity == 0)
				_capacity = 1;
			else if (_size == _capacity)
				_capacity *= 2;
			pointer new_alloc = _alloc.allocate(_capacity);
			size_type new_position = position - begin();
			std::uninitialized_copy(begin(), position, new_alloc);
			_alloc.construct(new_alloc + new_position, val);
			std::uninitialized_copy(position, end(), new_alloc + new_position + 1);
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			_alloc.deallocate(_start, _size);
			_size++;
			_start = new_alloc;
			return (iterator(new_alloc + new_position));
		}
		void insert (iterator position, size_type n, const value_type& val){
			size_type old_capacity = _capacity;

			if (_capacity == 0)
				_capacity = n;
			else if (_capacity < _size + n && _size + n < _capacity * 2)
				_capacity *= 2;
			else if (_size + n > _capacity * 2)
				_capacity = _size + n;
			pointer new_alloc = _alloc.allocate(_capacity);
			difference_type new_position = position - begin();
			
			std::uninitialized_copy(begin(), position, new_alloc);
			std::uninitialized_fill(new_alloc + new_position, new_alloc + new_position + n, val);
			std::uninitialized_copy(position, end(), new_alloc + new_position + n);
			
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			_alloc.deallocate(_start, old_capacity);
			_start = new_alloc;
			_size += n;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
			size_type new_capa = _capacity;
			
			if (_capacity * 2 > _size + std::distance(first, last))
				new_capa *= 2;
			else if(_size + std::distance(first, last) > _capacity)
				new_capa = _size + std::distance(first, last);
				
			pointer new_alloc = _alloc.allocate(new_capa);
			difference_type new_position = position - begin();
			std::uninitialized_copy(begin(), position, new_alloc);
			std::uninitialized_copy(first, last , new_alloc + new_position);
			std::uninitialized_copy(position, end(), new_alloc + new_position + std::distance(first, last));
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			_alloc.deallocate(_start, _capacity);
			_size += std::distance(first, last);
			_capacity = new_capa;
			_start = new_alloc;


		};
		iterator erase(iterator position){
			size_type i = 0;
			while (position + i != end())
			{
				_alloc.destroy(position.base() + i);
				_alloc.construct(position.base() + i, *(position + i + 1));
				i++;
			}
			_alloc.destroy(position.base() + i);
			_size--;
			return (iterator(_start) + (position - begin()));
		}
		iterator erase(iterator first, iterator last){
			size_type i = 0;
			
			while (first + i != end())
			{
				_alloc.destroy(first.base() + i);
				_alloc.construct(first.base() + i, *(last + i));
				i++;
			}
			_size -= std::distance(first, last);
			return (iterator(_start) + (first - begin()));
		}
		void swap(vector &x){
			std::swap(_alloc, x._alloc);
			std::swap(_start, x._start);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
		}
		void clear(){
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			_size = 0;
		};
		
		Allocator get_allocator() const {return _alloc;}

	private:
		allocator_type _alloc;
		pointer _start;
		size_type _size;
		size_type _capacity;
	};

	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
		return !(lhs == rhs);}
	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
		return !(lhs > rhs);}
	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
		return (rhs < lhs);}
	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
		return !(lhs < rhs);}
	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y){
		x.swap(y);
	};
}

#endif