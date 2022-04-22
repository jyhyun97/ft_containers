#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include "util.hpp"
#include <limits>

namespace ft{
	template <class T>
	class node {
		public : 
			typedef T value_type;
			typedef node<T> *pointer;

			node() : value(), parent(), left(), right(){};
			node(value_type _value, pointer _parent, pointer _left, pointer _right) : value(_value), parent(_parent), left(_left), right(_right) {};
			node(const node &origin) {*this = origin;};
			~node(){};
			node &operator=(const node &origin) {
				//pair
				this->value = origin.value;
				this->parent = origin.parent;
				this->left = origin.left;
				this->right = origin.right;
				return (*this);
			}
			
			value_type value;//페어
			pointer parent;
			pointer left;
			pointer right;		
	};
	template <class T>
	class const_treeIterator;

	template <class T>
	class treeIterator
	{
	public:
		typedef typename std::bidirectional_iterator_tag iterator_category;
		typedef typename std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef typename ft::node<T> *node_pointer;

		treeIterator() { node = NULL; }
		treeIterator(const node_pointer _node) : node(_node) {}
		treeIterator(const treeIterator &origin) : node(origin.node) {}
		//treeIterator(const ft::const_treeIterator<T> &origin) : node(origin.base()) {}
		~treeIterator(){};
		
		treeIterator &operator=(const treeIterator &origin)
		{
			this->node = origin.node;
			return (*this);
		}
		treeIterator &operator++()
		{
			if (node->right != NULL)
			{
				node = node->right;
				while (node->left != NULL)
					node = node->left;
			}
			else
			{
				if (node->parent && node == node->parent->left)
					node = node->parent;
				else
				{
					while (node->parent && node != node->parent->left)
						node = node->parent;
					if (node->parent)
						node = node->parent;
				}
			}
			return (*this);
		}
		treeIterator operator++(int)
		{
			treeIterator tmp(*this);
			this->operator++();
			return (tmp);
		}
		treeIterator &operator--()
		{
			//만약 노드가 root면 더미 노드로 이동해야 하는데..
			if (node->left == NULL && node->parent->parent == NULL)
				node = node->parent;
			else if (node->left != NULL)
			{
				node = node->left;
				while (node->right != NULL)
					node = node->right;
			}
			else
			{
				if (node == node->parent->right)
					node = node->parent;
				else
				{
					while (node != node->parent->right)
						node = node->parent;
					node = node->parent;
				}
			}
			return (*this);
		}
		treeIterator operator--(int)
		{
			treeIterator tmp(*this);
			this->operator--();
			return (tmp);
		}
		reference operator*() const
		{
			return (node->value);
		}
		pointer operator->() const
		{
			return &(node->value);
		}
		node_pointer base() const
		{
			return node;
		};

	private:
		node_pointer node;
	};
	template <class T>
	bool operator!=(const ft::treeIterator<T> &lhs, const ft::treeIterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class T>
	bool operator==(const ft::treeIterator<T> &lhs, const ft::treeIterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T>
	bool operator!=(const ft::treeIterator<T> &lhs, const ft::const_treeIterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class T>
	bool operator==(const ft::treeIterator<T> &lhs, const ft::const_treeIterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T>
	class const_treeIterator
	{
	public:
		typedef typename std::bidirectional_iterator_tag iterator_category;
		typedef typename std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef typename ft::node<T> *node_pointer;

		const_treeIterator() { node = NULL; }
		const_treeIterator(const node_pointer _node) : node(_node) {}
		const_treeIterator(const const_treeIterator &origin) : node(origin.node) {}
		const_treeIterator(const ft::treeIterator<T> &origin) : node(origin.base()) {}
		~const_treeIterator(){};

		const_treeIterator &operator=(const const_treeIterator &origin)
		{
			this->node = origin.node;
			return (*this);
		}
		const_treeIterator &operator++()
		{
			if (node->right != NULL)
			{
				node = node->right;
				while (node->left != NULL)
					node = node->left;
			}
			else
			{
				if (node->parent && node == node->parent->left)
					node = node->parent;
				else
				{
					while (node->parent && node != node->parent->left)
						node = node->parent;
					if (node->parent)
						node = node->parent;
				}
			}
			return (*this);
		}
		const_treeIterator operator++(int)
		{
			const_treeIterator tmp(*this);
			this->operator++();
			return (tmp);
		}
		const_treeIterator &operator--()
		{
			if (node->left == NULL && node->parent->parent == NULL)
				node = node->parent;
			else if (node->left != NULL)
			{
				node = node->left;
				while (node->right != NULL)
					node = node->right;
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent;
				}
				else
				{
					while (node != node->parent->right)
						node = node->parent;
					node = node->parent;
				}
			}
			return (*this);
		}
		const_treeIterator operator--(int)
		{
			const_treeIterator tmp(*this);
			this->operator--();
			return (tmp);
		}
		reference operator*() const
		{
			return (node->value);
		}
		pointer operator->() const
		{
			return &(node->value);
		}
		node_pointer base() const
		{
			return node;
		};

	private:
		node_pointer node;
	};
	template <class T>
	bool operator!=(const ft::const_treeIterator<T> &lhs, const ft::const_treeIterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class T>
	bool operator==(const ft::const_treeIterator<T> &lhs, const ft::const_treeIterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T>
	bool operator!=(const ft::const_treeIterator<T> &lhs, const ft::treeIterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class T>
	bool operator==(const ft::const_treeIterator<T> &lhs, const ft::treeIterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T, class Compare, class Alloc>
	class tree {
		typedef typename ft::node<T>* 			pointer;
		typedef std::allocator< ft::node<T> >	alloc;
		typedef typename Alloc::size_type		size_type;
		typedef ft::treeIterator<T>				iterator;
		typedef ft::const_treeIterator<T>		const_iterator;

		public :
		tree(){
			_alloc = alloc();//pair<>
			_dummy = _alloc.allocate(1);
			_alloc.construct(_dummy, node<T>());//위치, 노드
			_root = NULL;
			_comp = Compare();//
		}
		~tree(){
			//clear();
			//_alloc.destroy(_dummy);
			//_alloc.deallocate(_dummy, 1);
		};
		tree(const ft::tree<T, Compare, Alloc> &origin){ *this = origin;}
		tree &operator=(const ft::tree<T, Compare, Alloc> &origin)
		{
			if (_root)
				clear();
			// this->_dummy = origin._dummy;
			const_iterator i = origin.begin();//
			while (i != origin.end())
			{
				this->insert(*i);
			 	i++;
			}
			return (*this);
		}
		pointer search(const T insert_pair)
		{
			pointer i = _root;

			if (!_root)
				return (_dummy);
			while (i->right != NULL || i->left != NULL)//자식 노드가 존재할 동안. != 둘다
			{
				if (i->value.first == insert_pair.first)
					return (i);

				if (i->right != NULL && _comp(i->value.first, insert_pair.first))
				//if (i->right != NULL && i->value.first < insert_pair.first)
					i = i->right;
				else if (i->left != NULL && _comp(insert_pair.first, i->value.first ))
				//else if (i->left != NULL && i->value.first > insert_pair.first)
					i = i->left;
				else
					return i;
			}
			return (i);
		};

		ft::pair<treeIterator<T>, bool> insert(const T &insert_pair){
			pointer where = search(insert_pair);
			pointer insert_node = NULL;

			if (where != _dummy && where->value.first == insert_pair.first)
				return (ft::pair<treeIterator<T>, bool>(treeIterator<T>(where), false));
			insert_node = _alloc.allocate(1);
			if (where == _dummy)
			{
				_alloc.construct(insert_node, node<T>(insert_pair, where, NULL, NULL));
				_root = insert_node;
				_dummy->left = _root;
				return(pair<treeIterator<T>, bool>(treeIterator<T>(insert_node), true));
			}
			if (_comp(where->value.first, insert_pair.first))
//			if (where->value.first < insert_pair.first)
			{
				_alloc.construct(insert_node, node<T>(insert_pair, where, NULL, NULL));
				where->right = insert_node;
				return (pair<treeIterator<T>, bool>(treeIterator<T>(insert_node), true));
			}
			else
			{
				_alloc.construct(insert_node, node<T>(insert_pair, where, NULL, NULL));
				where->left = insert_node;
				return (ft::pair<treeIterator<T>, bool>(treeIterator<T>(insert_node), true));
			}
		}
		iterator begin() {
			pointer tmp = _root;
			if (!_root)
				return (_dummy);
			while (tmp->left != NULL)
				tmp = tmp->left;
			return iterator(tmp);
		}
		const_iterator begin() const{
			pointer tmp = _root;
			if (!_root)
				return (_dummy);
			while (tmp->left != NULL)
				tmp = tmp->left;
			return const_iterator(tmp);
		}
		iterator end() {
			return iterator(_dummy);
		}
		const_iterator end() const {
			return const_iterator(_dummy);
		}
		iterator find (const T& k_pair) {
			iterator it = begin();
			while (it != end())
			{
				if (it->first == k_pair.first)
					return (it);
				++it;
			}
			return (it);
		}
		const_iterator find (const T& k_pair) const{
			const_iterator it = begin();
			while (it != end())
			{
				if (it->first == k_pair.first)
					return (it);
				++it;
			}
			return (it);
		}
		size_type size () const {
			size_type tmp = 0;
			const_iterator i = begin();
			const_iterator final = end();
			while (i != final)
			{
				tmp++;
				i++;
			}
			return (tmp);
		}
		size_type erase (const T& k_pair){
			pointer tmp = find(k_pair).base();
			if (tmp == end().base())
				return 0;
			if (tmp == _root && tmp->left == NULL && tmp->right == NULL)
			{
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
				_dummy->left = NULL;
				_root = NULL;
				return 1;
			}
			//노드 destroy, deallocate, _dummy->left = NULL;
			if (tmp->left == NULL && tmp->right == NULL)
			{
				if (tmp->parent->left == tmp)
					tmp->parent->left = NULL;
				else
					tmp->parent->right = NULL;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
			}//지울 노드의 자식이 없다면 -> 부모자식 연 끊고 free
			else if (tmp->left != NULL && tmp->right == NULL)
			{
				if (tmp->parent->left == tmp)
					tmp->parent->left = tmp->left;
				else
					tmp->parent->right = tmp->left;
				tmp->left->parent = tmp->parent;
				if (tmp == _root)
					_root = tmp->left;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
			}
			else if (tmp->left == NULL && tmp->right != NULL)
			{//right만..
				if (tmp->parent->left == tmp)
					tmp->parent->left = tmp->right;
				else
					tmp->parent->right = tmp->right;
				tmp->right->parent = tmp->parent;
				if (tmp == _root)
					_root = tmp->right;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
			}
			else
			{
				iterator tmp2(tmp);
				--tmp2;
				pointer left_max = tmp2.base();
				//pointer left_max = (--iterator(tmp)).base();
				tmp->value = left_max->value;
				if (left_max->left != NULL)
				{
					if (left_max->parent->left == left_max)
						left_max->parent->left = left_max->left;
					else
						left_max->parent->right = left_max->left;
					left_max->left->parent = left_max->parent;
					// 부모의 자식은 교환노드의 왼쪽자식으로 해주기,
					// 교환노드 왼쪽 자식의 부모는 부모로 해주기.
				}
				else//자식이 없다?
				{
					if (left_max->parent->left == left_max)
						left_max->parent->left = NULL;
					else
						left_max->parent->right = NULL;
				}
				_alloc.destroy(left_max);
				_alloc.deallocate(left_max, 1);
			}
			//지울 노드의 자식이 두개라면 -> 왼쪽에서 최댓값과 교환, 교환노드가 자식 있으면 교환노드의 부모와 연결후 교환노드는 free
			return 1;
		}
		void clear(){
			if (!_root)
				return ;
			while (_root->left != NULL || _root->right != NULL)
			{
				pointer i = _root;
				while (i->left != NULL || i->right != NULL)
				{
					if (i->left != NULL)
						i = i->left;
					else if (i->right != NULL)
						i = i->right;
				}
				if (i->parent->left == i)
					i->parent->left = NULL;
				else if (i->parent->right == i)
					i->parent->right = NULL;
				_alloc.destroy(i);
				_alloc.deallocate(i, 1);
			}
			_alloc.destroy(_root);
			_alloc.deallocate(_root, 1);
			_root = NULL;
			_dummy->left = NULL;
		}
		iterator lower_bound(const T &pair) {
			//k 보다 같거나 큰 값 이터 반환
			iterator i = begin();
			while (i != end())
			{
				if (!(_comp(i->first, pair.first)))
				//if (i->first >= pair.first)
					return (i);
				i++;
			}
			return (i);
		}
		const_iterator lower_bound(const T &pair) const{
			//k 보다 같거나 큰 값 이터 반환
			const_iterator i = begin();
			while (i != end())
			{
				if (!(_comp(i->first, pair.first)))
				//if (i->first >= pair.first)
					return (i);
				i++;
			}
			return (i);
		}
		iterator upper_bound(const T &pair) {
			iterator i = begin();
			while (i != end())
			{
				if ((_comp(pair.first, i->first)))
				//if (i->first > pair.first)
					return (i);
				i++;
			}
			return (i);
		}
		const_iterator upper_bound(const T &pair) const{
			const_iterator i = begin();
			while (i != end())
			{
				if ((_comp(pair.first, i->first)))
				//if (i->first > pair.first)
					return (i);
				i++;
			}
			return (i);
		}
		void swap(ft::tree<T, Compare, Alloc> &origin){
			alloc tmp_alloc = _alloc;
			pointer tmp_root = _root;
			pointer tmp_dummy = _dummy;
			Compare tmp_comp = _comp;

			this->_alloc = origin._alloc;
			this->_root = origin._root;
			this->_dummy = origin._dummy;
			this->_comp = origin._comp;

			origin._alloc = tmp_alloc;
			origin._root = tmp_root;
			origin._dummy = tmp_dummy;
			origin._comp = tmp_comp;
		}

		private : 
		alloc _alloc;
		pointer _root;//
		pointer _dummy;//
		Compare _comp;//
	};

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
				value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
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
		typedef ft::treeIterator<value_type>                iterator;//treeIterator
		typedef ft::const_treeIterator<value_type>          const_iterator;//treeIterator
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
		~map(){
			clear();
		};
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
			//return (find(k))->second;
		}
		ft::pair<iterator,bool> insert (const value_type& val){return(_tree.insert(val));};
		iterator insert (iterator position, const value_type& val){
			_tree.insert(val);
			position = _tree.find(val);
			return (position);//삽입된 이터레이터 반환..
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