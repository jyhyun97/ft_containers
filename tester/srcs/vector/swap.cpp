#include "common.hpp"

#define TESTED_TYPE int
/*
const_iterator과 iterator을 비교하는 부분이 있었으나 98버전에 맞지 않는 케이스로 생각하여 수정함.
아래 11버전처럼 구현한다면 서로 다른 이터레이터도 동작하지만
template <class Iterator1, class Iterator2>
  bool operator== (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs);
98버전은 한가지 이터레이터만 받아와서 서로 다른 이터레이터를 비교할 수 없음
template <class Iterator>
  bool operator== (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs);
*/

int main ()
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> foo(3, 15);
	TESTED_NAMESPACE::vector<TESTED_TYPE> bar(5, 42);
	
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_foo = foo.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_bar = bar.begin();

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

	return (0);
}
