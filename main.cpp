#include <iostream>
#include <vector>
#include "vector.hpp"
#include <algorithm>
#include <string>
#include <list>

void checkErawe(ft::vector<std::string> &vct, ft::vector<std::string>::iterator &it)
{
    int i = it - vct.begin();
    std::cout << i << std::endl;
}


int main()
{
    // ft::vector<int> A(3, 4);
    // // ft::vector<int> C;
    // A[1] = 5;
    // A[2] = 6;
    // // ft::vector<int>::iterator it1;
    // // ft::vector<int>::iterator it2;
    // // ft::vector<int>::iterator it3;

    // // std::cout << A[0] << std::endl;
    // // std::cout << A[1] << std::endl;
    // // std::cout << A[2] << std::endl;
    // // it1 = A.begin();
    // // it2 = A.end();
    // // it3 = std::find(it1, it2, 5);
    // // std::cout << *it3 << std::endl;
    // // it3++;
    // // std::cout << *it3 << std::endl;
    // // std::cout << "\n" << A.size() << std::endl;
    // // std::cout << A.capacity() << std::endl;

    // // A.push_back(42);//4개
    // // A.push_back(43);//5개
    // // A.push_back(44);//6개
    // // std::cout << "\n" << A.size() << std::endl;
    // // std::cout << A.capacity() << std::endl;
    // // A.push_back(45);//7개
    // // std::cout << "\n" << A.size() << std::endl;
    // // std::cout << A.capacity() << std::endl;
    // std::cout << *A.begin() << std::endl;
    // //std::cout << A.begin()._ptr << std::endl;

    // std::cout << *A.end() << std::endl;
    // //std::cout << A.end()._ptr << std::endl;
    // ft::vector<int> B(A.begin(), A.end());
    // std::cout << (B.begin() != B.end()) << std::endl;
    // std::cout << *(A.begin() + 1) << std::endl;
    // //A.swap(B);
    // A.at(2) = 55;
    // std::cout << A.at(2) << std::endl;
    // std::cout << A[2] << std::endl;
    // swap(A, B);
    // A.insert(A.begin(), B.begin(), B.end());

    // B.erase(B.end());
    // B.erase(B.begin(), B.end());
    // ft::vector<std::string> v_str(5);
    // ft::vector<std::string>::reverse_iterator it_str(v_str.rbegin());
    // // ft::vector<std::string>::reverse_iterator ite_str(v_str.rend());

    // for (int i = 0; i < 5; i++)
    //     *it_str++ = "test" + std::to_string(i);
    // it_str = v_str.rend() - 1;

    // std::cout << *it_str << std::endl;
    // std::cout << it_str->c_str() << std::endl;    
    // return (0);

    ft::vector<int> vct(10);
}