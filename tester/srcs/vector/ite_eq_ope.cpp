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
template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_0(vct.begin());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_1(vct.end());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_mid;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit_0 = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit_1;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	printSize(vct, 1);
	it_0 = vct.begin();
	cit_1 = vct.end();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	std::cout << std::boolalpha;
	//std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

	std::cout << "\t\tft_eq_ope:" << std::endl;
	// regular it
	ft_eq_ope(it_0 + 3, it_mid);
	ft_eq_ope(it_0, it_1);
	ft_eq_ope(it_1 - 3, it_mid);
	// const it
	ft_eq_ope(cit_0 + 3, cit_mid);
	ft_eq_ope(cit_0, cit_1);
	ft_eq_ope(cit_1 - 3, cit_mid);
	// both it
	// ft_eq_ope(it_0 + 3, cit_mid);
	// ft_eq_ope(it_mid, cit_0 + 3);
	// ft_eq_ope(it_0, cit_1);
	// ft_eq_ope(it_1, cit_0);
	// ft_eq_ope(it_1 - 3, cit_mid);
	// ft_eq_ope(it_mid, cit_1 - 3);

	return (0);
}
