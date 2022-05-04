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

			node() : value(), parent(), left(), right(), max_depth(){};
			node(value_type _value, pointer _parent, pointer _left, pointer _right, int _max_depth) : value(_value), parent(_parent), left(_left), right(_right), max_depth(_max_depth) {};
			node(const node &origin) {*this = origin;};
			~node(){};
			node &operator=(const node &origin) {
				this->value = origin.value;
				this->parent = origin.parent;
				this->left = origin.left;
				this->right = origin.right;
				this->max_depth = origin.max_depth;
				return (*this);
			}
			value_type value;
			pointer parent;
			pointer left;
			pointer right;
			int		max_depth;
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
		typedef typename ft::node<const T>* 	const_pointer;
		typedef std::allocator< ft::node<T> >	alloc;
		typedef typename Alloc::size_type		size_type;
		typedef ft::treeIterator<T>				iterator;
		typedef ft::const_treeIterator<T>		const_iterator;

		public :
		tree(){
			_alloc = alloc();
			_dummy = _alloc.allocate(1);
			_alloc.construct(_dummy, node<T>());
			_root = NULL;
			_comp = Compare();
		}
		~tree(){
			//std::cout << "tree destructor" << std::endl;
			clear();
			_alloc.destroy(_dummy);
			_alloc.deallocate(_dummy, 1);
		};

		void preorder(iterator i){
			insert(*i);
			if (i.base()->left || i.base()->right)
			{
				if (i.base()->left)
					preorder(i.base()->left);
				if (i.base()->right)
					preorder(i.base()->right);
			}
		}

		tree(const ft::tree<T, Compare, Alloc> &origin){ *this = origin;}
		tree &operator=(const ft::tree<T, Compare, Alloc> &origin)
		{
			if (_root)
				clear();
			if (origin._root)
			{
				iterator i = origin._root;
				preorder(i);
			}
			return (*this);
		}
		pointer search(const T insert_pair)
		{
			pointer i = _root;

			if (!_root)
				return (_dummy);
			while (i->right != NULL || i->left != NULL)
			{
				if (i->value.first == insert_pair.first)
					return (i);
				if (i->right != NULL && _comp(i->value.first, insert_pair.first))
					i = i->right;
				else if (i->left != NULL && _comp(insert_pair.first, i->value.first ))
					i = i->left;
				else
					return i;
			}
			return (i);
		};
		int height(pointer p_root)
		{
			int l_tree, r_tree, rst;
			if (!p_root)
				return (0);
			l_tree = height(p_root->left);
			r_tree = height(p_root->right);
			if (l_tree > r_tree)
				rst = l_tree + 1;
			else
				rst = r_tree + 1;
			return (rst);
		}
		
		int height_diff(pointer p_root)
		{
			int l_tree = 0;
			int r_tree = 0;

			if (!p_root)
				return (0);
			if (p_root->left)
				l_tree = p_root->left->max_depth;
			if (p_root->right)
				r_tree = p_root->right->max_depth;
			return(l_tree - r_tree);
		}

		pointer LL(pointer i_node)
		{
			//std::cout << "LL" << std::endl;
			pointer main_node = i_node->left;
			pointer right_node = i_node;
			pointer left_node = i_node->left->left;

			if (i_node->parent->left == i_node)
				i_node->parent->left = main_node;
			else if(i_node->parent->right == i_node)
				i_node->parent->right = main_node;
			main_node->parent = i_node->parent;

			if (main_node->right)
			{
				right_node->left = main_node->right;
				main_node->right->parent = right_node;
			}
			else
				right_node->left = NULL;
			
			main_node->left = left_node;
			left_node->parent = main_node;
			main_node->right = right_node;
			right_node->parent = main_node;

			right_node->max_depth -= 2;
			return (main_node);
		}
		pointer LR(pointer i_node)
		{			
			//std::cout << "LR" << std::endl;
			pointer main_node = i_node->left->right;
			pointer left_node = i_node->left;
			pointer right_node = i_node;

			if (i_node->parent->left == i_node)
				i_node->parent->left = main_node;
			else if (i_node->parent->right == i_node)
				i_node->parent->right = main_node;
			main_node->parent = i_node->parent;
			
			if (main_node->left){
				left_node->right = main_node->left;
				main_node->left->parent = left_node;
			}
			else
				left_node->right = NULL;
			
			if (main_node->right)
			{
				right_node->left = main_node->right;
				main_node->right->parent = right_node;
			}
			else
				right_node->left = NULL;

			main_node->left = left_node;
			left_node->parent = main_node;
			main_node->right = right_node;
			right_node->parent = main_node;
			
			main_node->max_depth += 1;
			left_node->max_depth -= 1;
			right_node->max_depth -= 2;

			return (main_node);
		}
		pointer RR(pointer i_node)
		{
			//std::cout << "RR" << std::endl;
			pointer main_node = i_node->right;
			pointer left_node = i_node;
			pointer right_node = i_node->right->right;

			if (i_node->parent->left == i_node)
				i_node->parent->left = main_node;
			else if(i_node->parent->right == i_node)
				i_node->parent->right = main_node;
			main_node->parent = i_node->parent;

			if (main_node->left)
			{
				left_node->right = main_node->left;
				main_node->left->parent = left_node;
			}
			else
				left_node->right = NULL;
			
			main_node->left = left_node;
			left_node->parent = main_node;
			main_node->right = right_node;
			right_node->parent = main_node;

			left_node->max_depth -= 2;
			return (main_node);
		}
		pointer RL(pointer i_node)
		{
			//std::cout << "RL" << std::endl;
			pointer main_node = i_node->right->left;
			pointer left_node = i_node;
			pointer right_node = i_node->right;

			if (i_node->parent->left == i_node)
				i_node->parent->left = main_node;
			else if (i_node->parent->right == i_node)
				i_node->parent->right = main_node;
			main_node->parent = i_node->parent;

			if (main_node->left){
				left_node->right = main_node->left;
				main_node->left->parent = left_node;
			}
			else
				left_node->right = NULL;

			if (main_node->right)
			{
				right_node->left = main_node->right;
				main_node->right->parent = right_node;
			}
			else
				right_node->left = NULL;
			
			main_node->left = left_node;
			left_node->parent = main_node;
			main_node->right = right_node;
			right_node->parent = main_node;

			main_node->max_depth += 1;
			left_node->max_depth -= 2;
			right_node->max_depth -= 1;
			return (main_node);
		}
		
		void depth_update(pointer i_node, int root_value){
			pointer i_parent = i_node->parent;
			while (i_parent != _dummy)
			{
				if (i_node == i_parent->left && i_parent->right && i_parent->right->max_depth >= root_value)
						break;
				else if (i_node == i_parent->right && i_parent->left && i_parent->left->max_depth >= root_value)
						break;
				i_parent->max_depth = root_value;
				i_node = i_node->parent;
				i_parent = i_parent->parent;
				root_value++;
			}
		};

		// 1. 삽입한 노드부터 root까지 depth갱신 해주기.(부모 노드가 지금 노드와 같은 depth일 때만 갱신)
		// 2. LL, LR, RL, RR 등 로테이트 수행
		// 	 LL은 오른쪽 노드 depth -2, RR은 왼쪽 노드 depth -2
		// 	 LR은 RR수행하는 두 노드 depth를 먼저 하나씩 증가시킨 후 RR, LL 수행(RL은 반대로)
		// 3. 리밸런싱 후 부모 노드들의 depth 갱신(리밸런싱 노드 기준으로 형제노드 값이 작을 때만 부모 depth를 --한다.)
		void rebalance(pointer insert_node)
		{
			pointer i_node = insert_node;
			int depth = insert_node->max_depth;
			while (i_node != _dummy)
			{
				if (i_node->parent->max_depth != i_node->max_depth)//
					break;
				i_node = i_node->parent;
				depth++;
				i_node->max_depth = depth;
			}
			i_node = insert_node;
			int insu = 0;
			
			while (i_node != _dummy)
			{
				insu = height_diff(i_node);
				if ((insu > 1 || insu < -1))
					break;
				i_node = i_node->parent;
			}
			if (i_node == _dummy)
				return ;
			if (insu > 1)
			{
				int root_depth = i_node->max_depth;
				if (height_diff(i_node->left) >= 0)
					depth_update(LL(i_node), root_depth);
				else
					depth_update(LR(i_node), root_depth);
				
			}
			else if (insu < -1)
			{
				int root_depth = i_node->max_depth;

				if (height_diff(i_node->right) > 0)
					depth_update(RL(i_node), root_depth);
				else
					depth_update(RR(i_node), root_depth);
			}
			_root = _dummy->left;
		}
		
		ft::pair<treeIterator<T>, bool> insert(const T &insert_pair){
			pointer where = search(insert_pair);
			pointer insert_node = NULL;

			if (where != _dummy && where->value.first == insert_pair.first)
				return (ft::pair<treeIterator<T>, bool>(treeIterator<T>(where), false));
			insert_node = _alloc.allocate(1);
			if (where == _dummy)
			{
				_alloc.construct(insert_node, node<T>(insert_pair, where, NULL, NULL, 1));
				_root = insert_node;
				_dummy->left = _root;
				//insert_node->max_depth++;
				return(pair<treeIterator<T>, bool>(treeIterator<T>(insert_node), true));
			}
			if (_comp(where->value.first, insert_pair.first))
			{
				_alloc.construct(insert_node, node<T>(insert_pair, where, NULL, NULL, 1));
				where->right = insert_node;
				rebalance(insert_node);
				return (pair<treeIterator<T>, bool>(treeIterator<T>(insert_node), true));
			}
			else
			{
				_alloc.construct(insert_node, node<T>(insert_pair, where, NULL, NULL, 1));
				where->left = insert_node;
				rebalance(insert_node);
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
		
		pointer erase_LL(pointer i_node){
			//메인노드에 오른쪽 노드가 있는 케이스를 추가하기 이 경우 main + 1, right - 1
			//위 케이스 이외의 경우는 erase_depth_update하기.. 그냥 여기서 해주기...
			int depth = i_node->max_depth;
			pointer main_node = i_node->left;
			pointer right_node = i_node;
			pointer left_node = i_node->left->left;

			int flag = 0;
			if (main_node->right && main_node->right->max_depth == left_node->max_depth)//left depth, right depth 같을 경우
				flag = 1;
			//main 노드의 right가 있고, left노드에 자식이 없는 상황에서는 main +1, right -1 뎁스 조절 X
			//
			if (i_node->parent->left == i_node)
				i_node->parent->left = main_node;
			else if(i_node->parent->right == i_node)
				i_node->parent->right = main_node;
			main_node->parent = i_node->parent;

			if (main_node->right)
			{
				right_node->left = main_node->right;
				main_node->right->parent = right_node;
			}
			else
				right_node->left = NULL;
			
			main_node->left = left_node;
			left_node->parent = main_node;
			main_node->right = right_node;
			right_node->parent = main_node;

			if (flag == 1)
			{
				main_node->max_depth += 1;
				right_node->max_depth -= 1;
				return (main_node);
			}

			right_node->max_depth -= 2;
			depth_update(main_node, depth);
			return (main_node);
		};

		pointer erase_RR(pointer i_node){
		//동일함 main + 1, left -1
			int depth = i_node->max_depth;

			pointer main_node = i_node->right;
			pointer left_node = i_node;
			pointer right_node = i_node->right->right;
			int flag = 0;
			if (main_node->left && main_node->left->max_depth == right_node->max_depth)
				flag = 1;
			//
			if (i_node->parent->left == i_node)
				i_node->parent->left = main_node;
			else if(i_node->parent->right == i_node)
				i_node->parent->right = main_node;
			main_node->parent = i_node->parent;

			if (main_node->left)
			{
				left_node->right = main_node->left;
				main_node->left->parent = left_node;
			}
			else
				left_node->right = NULL;
			
			main_node->left = left_node;
			left_node->parent = main_node;
			main_node->right = right_node;
			right_node->parent = main_node;

			if (flag == 1)
			{
				main_node->max_depth += 1;
				left_node->max_depth -= 1;
				return (main_node);
			}

			left_node->max_depth -= 2;
			depth_update(main_node, depth);
			return (main_node);
			
		};
		 
		// void erase_depth_update(pointer p_root){
		// 	while (p_root != _dummy)
		// 	{
		// 		if (p_root->parent->left == p_root && p_root->parent->right && p_root->max_depth <= p_root->parent->right->max_depth)
		// 			break;
		// 		else if (p_root->parent->right == p_root && p_root->parent->left && p_root->max_depth <= p_root->parent->left->max_depth)
		// 			break;
		// 		p_root = p_root->parent;
		// 		if (p_root == _dummy)
		// 			return ;
		// 		p_root->max_depth--;
		// 	}
		// }
		void erase_rebalance(pointer i_node)
		{
			pointer i = i_node;
			// if (i_node->left)
			// {
			// 	if (i_node->max_depth - i_node->left->max_depth < 1)
			// 		std::cout << "왼쪽 으아아아아악!!!" << std::endl;
			// }
			// if (i_node->right)
			// {
			// 	if (i_node->max_depth - i_node->right->max_depth < 1)
			// 		std::cout << "오른쪽 으아아아아악!!!" << std::endl;
			// }
			while (i != _dummy)
			{
				int insu = 0;
				while (i_node != _dummy)
				{
					insu = height_diff(i_node);
					if ((insu > 1 || insu < -1))
						break;
					i_node = i_node->parent;
				}
				if (i_node == _dummy)
				{
					i = i->parent;
					continue;
				}
				if (insu > 1)
				{
					int root_depth = i_node->max_depth;
					if (height_diff(i_node->left) >= 0)
					{
						std::cout << "LL" << std::endl;
						erase_LL(i_node);
					}else{
						std::cout << "LR" << std::endl;
						depth_update(LR(i_node), root_depth);
					}
				}
				else if (insu < -1)
				{
					int root_depth = i_node->max_depth;

					if (height_diff(i_node->right) > 0){
						std::cout << "RL" << std::endl;
						depth_update(RL(i_node), root_depth);
					}
					else{
						std::cout << "RR" << std::endl;
						erase_RR(i_node);
					}
				}
				_root = _dummy->left;
				i = i->parent;
			}
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
			if (tmp->left == NULL && tmp->right == NULL)
			{
				//erase_depth_update(tmp);
				depth_update(tmp, tmp->max_depth);
				pointer rebalance_tmp = tmp->parent;//대체 노드, 없으면 그 부모...
				if (tmp->parent->left == tmp)
					tmp->parent->left = NULL;
				else
					tmp->parent->right = NULL;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
				erase_rebalance(rebalance_tmp);
			}
			else if (tmp->left != NULL && tmp->right == NULL)
			{
				//erase_depth_update(tmp);
				depth_update(tmp, tmp->max_depth);
				pointer rebalance_tmp = tmp->parent;
				if (tmp->parent->left == tmp)
					tmp->parent->left = tmp->left;
				else
					tmp->parent->right = tmp->left;
				tmp->left->parent = tmp->parent;
				if (tmp == _root)
					_root = tmp->left;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
				erase_rebalance(rebalance_tmp);
			}
			else if (tmp->left == NULL && tmp->right != NULL)
			{
				//erase_depth_update(tmp);
				depth_update(tmp, tmp->max_depth);
				pointer rebalance_tmp = tmp->parent;
				if (tmp->parent->left == tmp)
					tmp->parent->left = tmp->right;
				else
					tmp->parent->right = tmp->right;
				tmp->right->parent = tmp->parent;
				if (tmp == _root)
					_root = tmp->right;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
				erase_rebalance(rebalance_tmp);
			}
			else
			{
				iterator tmp2(tmp);
				--tmp2;
				pointer left_max = tmp2.base();
				depth_update(left_max, left_max->max_depth);
				//erase_depth_update(left_max);
				pointer rebalance_tmp = left_max->parent;
				tmp->value = left_max->value;
				if (left_max->left != NULL)
				{
					if (left_max->parent->left == left_max)
						left_max->parent->left = left_max->left;
					else
						left_max->parent->right = left_max->left;
					left_max->left->parent = left_max->parent;
				}
				else
				{
					if (left_max->parent->left == left_max)
						left_max->parent->left = NULL;
					else
						left_max->parent->right = NULL;
				}
				_alloc.destroy(left_max);
				_alloc.deallocate(left_max, 1);
				erase_rebalance(rebalance_tmp);
			}
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
			iterator i = begin();
			while (i != end())
			{
				if (!(_comp(i->first, pair.first)))
					return (i);
				i++;
			}
			return (i);
		}
		const_iterator lower_bound(const T &pair) const{
			const_iterator i = begin();
			while (i != end())
			{
				if (!(_comp(i->first, pair.first)))
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
		pointer _root;
		pointer _dummy;
		Compare _comp;
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