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

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct, true);
	return (0);
}
