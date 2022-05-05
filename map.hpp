#ifndef MAP_HPP
# define MAP_HPP

#include "tree.hpp"

namespace ft{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
		public :
		typedef Key                                     key_type;
		typedef T                                       mapped_type;
		typedef ft::pair<const key_type, mapped_type>   value_type;
		typedef Compare                                 key_compare;
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		};
		typedef ft::tree<value_type, Compare, Alloc>        tree_type;
		typedef Alloc                                       allocator_type;
		typedef typename allocator_type::reference          reference;
		typedef typename allocator_type::const_reference    const_reference;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef ft::treeIterator<value_type>                iterator;
		typedef ft::const_treeIterator<value_type>          const_iterator;
		typedef ft::reverse_iterator<iterator>              reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename allocator_type::size_type          size_type;

		public :
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()){
			_alloc = alloc;
			_compare = comp;
			_tree = tree_type();
		};
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){
			_alloc = alloc;
			_compare = comp;
			_tree = tree_type();
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		};
		map (const map& x){
			*this = x;
		};
		~map(){};
		map& operator= (const map& x){
			this->_tree = x._tree;
			this->_alloc = x._alloc;
			this->_compare = x._compare;
			return (*this);
		};
		iterator begin(){
			return (_tree.begin());
		};
		const_iterator begin() const{
			return (_tree.begin());
		};
		iterator end(){
			return (_tree.end());
		};
		const_iterator end() const{
			return (_tree.end());
		};
		reverse_iterator rbegin(){
			return (reverse_iterator(_tree.end()));
		};
		const_reverse_iterator rbegin() const{
			return (reverse_iterator(_tree.end()));
		};
		reverse_iterator rend(){
			return (reverse_iterator(_tree.begin()));
		};
		const_reverse_iterator rend() const{
			return (reverse_iterator(_tree.begin()));
		};

		bool empty() const {return (_tree.size() == 0);}
		size_type size() const {return (_tree.size());}
		size_type max_size() const {return _alloc.max_size();}
		mapped_type& operator[] (const key_type& k){
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
		}
		ft::pair<iterator,bool> insert (const value_type& val){return(_tree.insert(val));};
		iterator insert (iterator position, const value_type& val){
			_tree.insert(val);
			position = _tree.find(val);
			return (position);
		};
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		};
		void erase (iterator position){_tree.erase(*position);}
		size_type erase (const key_type& k){return(_tree.erase(ft::make_pair(k, mapped_type())));}
		void erase (iterator first, iterator last){
			iterator tmp1 = first;
			iterator tmp2 = tmp1;
			while (tmp1 != last)
			{
				tmp1++;
				erase(tmp2);
				tmp2 = tmp1;
			}
		};
		void swap (map& x){
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_compare, x._compare);
			_tree.swap(x._tree);
		};
		void clear(){_tree.clear();}
		key_compare key_comp() const {return(_compare);}
		value_compare value_comp() const {
			return value_compare(_compare);
		};
		iterator find (const key_type& k){return(_tree.find(ft::make_pair(k, mapped_type())));}
		const_iterator find (const key_type& k) const {return _tree.find(ft::make_pair(k, mapped_type()));}
		size_type count (const key_type& k) const {return (find(k) == end() ? 0 : 1);}
		iterator lower_bound(const key_type &k){return (_tree.lower_bound(ft::make_pair(k, mapped_type())));}
		const_iterator lower_bound(const key_type &k) const {return _tree.lower_bound(ft::make_pair(k, mapped_type()));}
		iterator upper_bound (const key_type& k){return (_tree.upper_bound(ft::make_pair(k, mapped_type())));}
		const_iterator upper_bound(const key_type &k) const {return _tree.upper_bound(ft::make_pair(k, mapped_type()));}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const{return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));}
		ft::pair<iterator, iterator> equal_range(const key_type &k){return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));};
		allocator_type get_allocator() const {return (_alloc);};

	private:
		allocator_type	_alloc;
		tree_type		_tree;
		key_compare		_compare;
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs){
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs){
		return !(lhs == rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs){
						return !(lhs > rhs);
					};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs){
					   return (rhs < lhs);
				   };

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs){
						return !(lhs < rhs);
					};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y){
		x.swap(y);
	};
};

#endif