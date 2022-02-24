#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft
{
	template <class T>
	struct iterator_traits
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	class vectorIterator
	{
		public :
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

		vectorIterator(){
			_ptr = nullptr;
		};
		vectorIterator(pointer a){
			_ptr = a;
		}
		vectorIterator &operator= (const vectorIterator &x){
			_ptr = x.base();
			return (*this);
		}
		vectorIterator& operator++(){
			++_ptr;
			return (*this);
		}
		vectorIterator operator++(int){
			vectorIterator tmp(*this);
			++_ptr;
			return (tmp);
		}
		pointer base() const{
			return (_ptr);
		}
		reference operator*() const {
			return *_ptr;
		}
		private :
		pointer _ptr;
	};
	template <class T>
	bool operator!=(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return !(lhs.base() == rhs.base());
	}
	template <class T>
	bool operator==(const ft::vectorIterator<T> &lhs, const ft::vectorIterator<T> &rhs){
			return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	class vectorReverseIterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
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
		typedef typename ft::vectorReverseIterator<T> reverse_iterator;             //"
		typedef typename ft::vectorReverseIterator<const T> const_reverse_iterator; //"
		typedef typename std::ptrdiff_t difference_type;                        // std::ptrdiff_t
		typedef typename std::size_t size_type;                                 // std::size_t

		// Basic member function
		explicit vector(const allocator_type &alloc = allocator_type()){
			_alloc = alloc.allocate(alloc);
			_start = nullptr;//define 하기
			_size = 0;
			_capacity = 0;
		};
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()){
			_start = _alloc.allocate(n);
			_size = n;
			_capacity = n;
			std::uninitialized_fill(_start, _start + n, val); 
		};
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		// vector(const vector &x);
		~vector(){
			_alloc.deallocate(0, _capacity);
		};
		vector& operator= (const vector& x);
		// Iterators
		iterator begin(){return (iterator(_start));}
		const_iterator begin() const;
		iterator end(){return (iterator(_start + _capacity));}
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// Capacity
		size_type size() const{return (_size);};
		size_type max_size() const;
		void resize (size_type n, value_type val = value_type());
		size_type capacity() const{return (_capacity);};
		bool empty() const;
		void reserve(size_type n){
			if (!(_capacity < n))
				return ;
			allocator_type new_alloc;
			pointer new_start;
			new_start = new_alloc.allocate(n);
			int i = 0;
			while (i < _size)
			{
				new_alloc.construct(new_start + i, *(_start + i));
				i++;
			}
			_alloc.deallocate(_start, _capacity);
			_start = new_start;
			_capacity = n;
			//사이즈를 n으로 재조정하는 함수!
			//뭔가 사이즈가 n인 새 alloc을 만들고!
			//안에 원소 옮겨담고!
			//_start, _alloc, _capacity 재조정!
			//기존의 것 삭제는 deallocate로 하면 되겠다
		}

		// Element access
		reference operator[](size_type n){return (*(_start + n));}
		const_reference operator[](size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// Modifiers
		void assign (size_type n, const value_type& val);
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void push_back(const value_type &val){
			if (_capacity == 0)
				reserve(1);
			else if (_size == _capacity)
				reserve(_capacity * 2);
			_alloc.construct(_start + _size, val);
			_size++;
			
		};
		void pop_back(){
			//맨 뒤의 원소를 하나 삭제

		}
		iterator insert (iterator position, const value_type& val);
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector &x);
		void clear();
		
		//Allocator
		Allocator get_allocator() const;

	private:
		allocator_type _alloc;
		pointer _start;
		size_type _size;//저장된 원소의 수
		size_type _capacity;//할당된 공간의 크기
	};
	// Non-member functions
	template <class T, class Alloc>
	bool operator==(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs){
		return (lhs == rhs);}
	template <class T, class Alloc>
	bool operator!=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs){
		return !(lhs == rhs);}
	template <class T, class Alloc>
	bool operator<(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs){
		return (lhs < rhs);}
	template <class T, class Alloc>
	bool operator<=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs){
		return (lhs <= rhs);}
	template <class T, class Alloc>
	bool operator>(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs){
		return (lhs > rhs);}
	template <class T, class Alloc>
	bool operator>=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs){
		return (lhs >= rhs);}
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);
}

#endif