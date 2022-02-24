#include <iostream>
#include <vector>
#include "vector.hpp"
#include <algorithm>

int main()
{
    ft::vector<int> A(3, 2);
    A[1] = 5;
    A[2] = 6;
    ft::vector<int>::iterator it1;
    ft::vector<int>::iterator it2;
    ft::vector<int>::iterator it3;

    std::cout << A[0] << std::endl;
    std::cout << A[1] << std::endl;
    std::cout << A[2] << std::endl;
    it1 = A.begin();
    it2 = A.end();
    it3 = std::find(it1, it2, 5);
    std::cout << *it3 << std::endl;
    it3++;
    std::cout << *it3 << std::endl;
    std::cout << "\n" << A.size() << std::endl;
    std::cout << A.capacity() << std::endl;

    A.push_back(42);//4개
    A.push_back(43);//5개
    A.push_back(44);//6개
    std::cout << "\n" << A.size() << std::endl;
    std::cout << A.capacity() << std::endl;
    A.push_back(45);//7개
    std::cout << "\n" << A.size() << std::endl;
    std::cout << A.capacity() << std::endl;

    return (0);
}