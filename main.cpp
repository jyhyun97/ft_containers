#include <iostream>
#include <vector>
#include "vector.hpp"
#include "map.hpp"
#include <algorithm>
#include <string>
#include <list>
#include <__tree>
#include <map>
#include <stack>

#define T1 char
#define T2 int
#define TESTED_NAMESPACE ft
#define _pair TESTED_NAMESPACE::pair
typedef _pair<const T1, T2> T3;


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


void func(){
	std::list<T3> lst;

	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, lst_size - i));
	TESTED_NAMESPACE::map<T1, T2> foo(lst.begin(), lst.end());

	lst.clear(); lst_size = 4;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('z' - i, i * 5));
	TESTED_NAMESPACE::map<T1, T2> bar(lst.begin(), lst.end());

	TESTED_NAMESPACE::map<T1, T2>::const_iterator it_foo = foo.begin();
	TESTED_NAMESPACE::map<T1, T2>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
}

int main()
{
    func();
    
    return (0);
}