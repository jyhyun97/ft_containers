#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include "util.hpp"

namespace ft
{
	template <class Iterator>
	class vectorIterator
	{
		public :
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator *>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator *>::value_type		value_type;
		typedef typename iterator_traits<Iterator *>::pointer			pointer;
		typedef typename iterator_traits<Iterator *>::reference			reference;
		typedef typename iterator_traits<Iterator *>::iterator_category	iterator_category;

		vectorIterator() : _ptr() {}
		explicit vectorIterator(pointer a) : _ptr(a) {}
		template <class Iter>//복사생성자
		vectorIterator(const vectorIterator<Iter> &rev_it) : _ptr(rev_it.base()) {}
		vectorIterator &operator=(const vectorIterator &x){
			_ptr = x.base();
			return (*this);
		}
		pointer base() const {
			return (_ptr);
		}
		reference operator*() const {
			return (*_ptr);
		}
		pointer operator->() const {
			return &(this->operator*());
		}
		vectorIterator& operator++() {
			++_ptr;
			return (*this);
		}
		vectorIterator operator++(int) {
			vectorIterator tmp(*this);
			++_ptr;
			return (tmp); 
		}
		vectorIterator& operator--(){
			--_ptr;
			return (*this);
		}
		vectorIterator operator--(int){
			vectorIterator tmp(*this);
			--_ptr;
			return (tmp);
		}
		vectorIterator operator+ (const difference_type &n) const {
			return (vectorIterator(_ptr + n));
		}
		vectorIterator &operator+= (const difference_type &n){
			_ptr += n;
			return (*this);
		}
		vectorIterator operator- (const difference_type &n) const {
			return (vectorIterator(_ptr - n));
		}
		vectorIterator &operator-= (const difference_type &n){
			_ptr -= n;
			return (*this);
		}
		reference operator[](difference_type n) const {
			return *(_ptr + n);
		}
		private :
			pointer _ptr;
	};

	template <class T>
	bool operator!=(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() != rhs.base());
	}

	template <class T>
	bool operator==(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() == rhs.base());
	}
	template <class T>
	bool operator>(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() > rhs.base());
	}
	template <class T>
	bool operator<(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() < rhs.base());
	}
	template <class T>
	bool operator>=(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() >= rhs.base());
	}
	template <class T>
	bool operator<=(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() <= rhs.base());
	}
	template <class Iterator>
	ft::vectorIterator<Iterator> operator+(
		typename ft::vectorIterator<Iterator>::difference_type n,
		const ft::vectorIterator<Iterator> &rev_it){
			return (rev_it + n);
	};

	template <class Iterator>
	typename ft::vectorIterator<Iterator>::difference_type operator-(
		const ft::vectorIterator<Iterator> &lhs,
		const ft::vectorIterator<Iterator> &rhs){
			return (lhs.base() - rhs.base());
	};

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public :
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;                   // value_type&
		typedef typename allocator_type::const_reference const_reference;       // const value_type&
		typedef typename allocator_type::pointer pointer;                       // Allocator::pointer
		typedef typename allocator_type::const_pointer const_pointer;           // Allocator::const_pointer
		typedef typename ft::vectorIterator<T> iterator;                            // LegacyRandomAccessIterator????
		typedef typename ft::vectorIterator<const T> const_iterator;                //"
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;             //"
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator; //"
		typedef typename std::ptrdiff_t difference_type;                        // std::ptrdiff_t
		typedef typename std::size_t size_type;                                 // std::size_t

		// Basic member function vector
		explicit vector(const allocator_type &alloc = allocator_type()){
			_alloc = alloc;
			//_start = nullptr;//define 하기
			_start = _alloc.allocate(0);			
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
			if (_capacity > 0)
				_alloc.deallocate(0, _capacity);
		};
		vector& operator= (const vector& x){
			//먼저 있는 거 다 비워주고
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			//새로 allocate(x size)하고 construct(x 하나씩)하고~ size랑 capacity 초기화하고 끝~!
			clear();
			//if (_capacity != 0)
			//	_alloc.deallocate(_start, _capacity);
			if (_capacity < x.capacity())
			{
				_start = _alloc.allocate(x._size);
				_capacity = x._size;
			}
			_size = x._size;
			i = 0;
			while (i < x._size)
			{
				_alloc.construct(_start + i, x[i]);
				i++;
			}
			return (*this);
		};
		// Iterators
		iterator begin(){return (iterator(_start));}
		const_iterator begin() const {return (const_iterator(_start));}
		iterator end(){return (iterator(_start + _size));}
		const_iterator end() const {return (const_iterator(_start + _size));}
		reverse_iterator rbegin(){return (reverse_iterator(end()));}
		const_reverse_iterator rbegin() const{return (const_reverse_iterator(end()));}
		reverse_iterator rend(){return (reverse_iterator(begin()));}
		const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}

		// Capacity
		size_type size() const{return (_size);}
		size_type max_size() const{return (_alloc.max_size());}
		void resize (size_type n, value_type val = value_type()){
			//n이 사이즈보다 작으면 파괴, 크면 늘리고 val로 채우기
			//cpct 생각해서.. n이 cpct보다 크면.... 할당...
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
				//reserve~~~~
				if (_capacity < n && n < _capacity * 2)//_capacity =< _size + n < _capacity * 2
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
			if (_capacity >= n)//이미 충분한 capacity는 필요 없음...
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

		// Element access
		reference operator[](size_type n){return (*(_start + n));}
		const_reference operator[](size_type n) const{return (*(_start + n));}
		reference at(size_type n){
			if(n > _capacity)
				throw std::out_of_range("test");
			return (*(_start + n));}
		const_reference at(size_type n) const{
			if(n > _capacity)
				throw std::out_of_range("test");
			return (*(_start + n));}
		reference front(){return *(_start);}
		const_reference front() const {return *(_start);}
		reference back(){return *(_start + _size - 1);}
		const_reference back() const{ return *(_start + _size - 1);}

		// Modifiers
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
				_capacity = n;//
			}
			_size = n;
			std::uninitialized_fill(_start, _start + n, val);
		};
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
			//새 벡터 크기 가 현재 벡터 용량을 초과하는 경우에만 할당된 저장 공간이 자동으로 재할당됩니다.
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
				_capacity = std::distance(first, last);//
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
			_alloc.deallocate(_start, _size);//옛날 capacity로 고쳐야 함
			_size++;
			_start = new_alloc;
			return (iterator(new_alloc + new_position));
		}
		void insert (iterator position, size_type n, const value_type& val){
			size_type old_capacity = _capacity;

			if (_capacity == 0)
				_capacity = n;
			else if (_capacity < _size + n && _size + n < _capacity * 2)//_capacity =< _size + n < _capacity * 2
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
			_alloc.deallocate(_start, old_capacity);//옛날 카파시티로 고쳐야 함
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
			//position위치까지는 그대로 스킵하고,
			//position부터 destroy하고 한 칸씩 땡겨서 construct
			size_type i = 0;
			while (position + i != end())
			{
				_alloc.destroy(position.base() + i);
				_alloc.construct(position.base() + i, *(position + i + 1));
				i++;
			}
			_alloc.destroy(position.base() + i);
			_size--;
			return (iterator(_start) + (position - begin()));//지워진 요소 바로 다음~
		}
		iterator erase(iterator first, iterator last){
			//first ~ last 지워용
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
			//다 destroy하고 size 0
			size_type i = 0;
			while (i < _size)
			{
				_alloc.destroy(_start + i);
				i++;
			}
			_size = 0;
		};
		
		//Allocator
		Allocator get_allocator() const {return _alloc;}

	private:
		allocator_type _alloc;
		pointer _start;
		size_type _size;//저장된 원소의 수
		size_type _capacity;//할당된 공간의 크기
	};
	// Non-member functions
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