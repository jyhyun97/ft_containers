#include <iostream>
#include <vector>
#include "vector.hpp"

int main()
{
    ft::vector<int> A(3, 2);

    std::cout << A[0] << std::endl;
    std::cout << A[1] << std::endl;
    std::cout << A[2] << std::endl;

    return (0);
}