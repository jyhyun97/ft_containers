#include "common.hpp"

#define TESTED_TYPE foo<int>
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

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it(vct.begin());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	printSize(vct, 1);

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;

	return (0);
}
