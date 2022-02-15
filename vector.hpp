#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft
{
    /*
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
    */
    template <class T>
    class vectorIter;
    template <class T>
    class vectorReverseIter;

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
        typedef typename ft::vectorIter<T> iterator;                            // LegacyRandomAccessIterator????
        typedef typename ft::vectorIter<const T> const_iterator;                //"
        typedef typename ft::vectorReverseIter<T> reverse_iterator;             //"
        typedef typename ft::vectorReverseIter<const T> const_reverse_iterator; //"
        typedef typename std::ptrdiff_t difference_type;                        // std::ptrdiff_t
        typedef typename std::size_t size_type;                                 // std::size_t

        // Basic member function
        explicit vector(const allocator_type &alloc = allocator_type()){
            _alloc = alloc.allocate();
            _start = nullptr;

        };
        explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()){
            _start = _alloc.allocate(n);
            std::uninitialized_fill(_start, _start + n, val);
        };
        // template <class InputIterator>
        // vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
        // vector(const vector &x);
        ~vector(){
            //delete _alloc;
            _alloc.deallocate(0, 1);
        };
        vector& operator= (const vector& x);

        // Iterators
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        // Capacity
        size_type size() const;
        size_type max_size() const;
        void resize (size_type n, value_type val = value_type());
        size_type capacity() const;
        bool empty() const;
        void reserve(size_type n);

        // Element access
        reference operator[](size_type n){
            return (*(_start + n));
        };
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
        void push_back(const value_type &val);
        void pop_back();
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
        // pointer _end;
        // pointer _end_capacity;
    };
    // Non-member functions
    template <class T, class Alloc>
    bool operator==(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs);
    template <class T, class Alloc>
    bool operator!=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs);
    template <class T, class Alloc>
    bool operator<(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs);
    template <class T, class Alloc>
    bool operator<=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs);
    template <class T, class Alloc>
    bool operator>(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs);
    template <class T, class Alloc>
    bool operator>=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs);
    template <class T, class Alloc>
    void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);
}

#endif