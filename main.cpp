#include <iostream>
#include <string>
#include <deque>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>


#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int func_main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}

void func_vector(){
	ft::vector<std::string> my_vector;

	std::cout << "****** basic test ******" << std::endl;
	my_vector.push_back("hello world");
	my_vector.push_back("world hello");
	std::cout << my_vector.front() << std::endl;
	std::cout << my_vector.back() << std::endl;
	my_vector.insert(my_vector.end(), "insert end");
	my_vector.insert(my_vector.begin(), "insert begin");
	std::cout << my_vector.back() << std::endl;
	std::cout << "size : " << my_vector.size() << " capacity: " << my_vector.capacity() << std::endl;
	my_vector.erase(my_vector.begin());
	my_vector.pop_back();
	std::cout << "size : " << my_vector.size() << " capacity: " << my_vector.capacity() << std::endl;
	
	std::cout << "****** iterator ******" << std::endl;
	ft::vector<std::string> copy_vector(my_vector);
	ft::vector<std::string>::iterator it = copy_vector.begin();
	while (it != copy_vector.end())
	{
		std::cout << "copy vector : " << *it << std::endl;
		it++;
	}
	my_vector.clear();
	it = copy_vector.begin();
	while (it != copy_vector.end())
	{
		std::cout << "copy vector after empty my_vector : " << *it << std::endl;
		it++;
	}
	std::cout << "****** relational function ******" << std::endl;
	std::cout << "T/F test == : " << (copy_vector == my_vector) << std::endl;
	std::cout << "T/F test != : "  <<  (copy_vector != my_vector) << std::endl;
	std::cout << "T/F test == < "  << (copy_vector < my_vector) << std::endl;
	std::cout << "T/F test == > "  << (copy_vector > my_vector) << std::endl;

	ft::vector<int> A(1, 3);
	ft::vector<int>::iterator it1 = A.begin();
	ft::vector<int>::iterator it2 = A.end();
	
	std::cout << (it1 < it2) << std::endl;
	std::cout << (it2 < it1) << std::endl;
}

void func_stack(){
	ft::stack<std::string> my_stack;
	my_stack.push("push1");
	my_stack.push("push2");
	my_stack.push("push3");
	std::cout << "top : " << my_stack.top() << std::endl;
	std::cout << "size : " << my_stack.size() << std::endl;
	my_stack.pop();
	my_stack.pop();
	std::cout << "top : " << my_stack.top() << std::endl;
	std::cout << "size : " << my_stack.size() << std::endl;
}

void func_map(){
	ft::map<int, int> my_map;
	my_map.insert(ft::make_pair<int, int>(1, 0));
	my_map.insert(ft::make_pair<int, int>(2, 0));
	my_map.insert(ft::make_pair<int, int>(5, 0));
	my_map.insert(ft::make_pair<int, int>(4, 0));
	my_map.insert(ft::make_pair<int, int>(3, 0));
	
	ft::map<int, int>::iterator it = my_map.begin();
	while (it != my_map.end())
	{
		std::cout << "first : " << it->first << ", second : " << it->second << std::endl;
		it++;
	}
	std::cout << "before erase : " << my_map.find(3)->first << std::endl;
	my_map.erase(3);
	std::cout << "after erase : " << my_map.find(3)->first << std::endl;
	std::cout << "lower_bound : " << my_map.lower_bound(2)->first << std::endl;
	std::cout << "upper bound : "<< my_map.upper_bound(2)->first << std::endl;
	my_map.clear();
	it = my_map.begin();
	while (it != my_map.end())
	{
		std::cout << "first : " << it->first << ", second : " << it->second << std::endl;
		it++;
	}
}

int main(int argc, char **argv)
{
	if (func_main(argc, argv) == 1)
		return 1;
	std::cout << "--------------- vector test ---------------" << std::endl;
	func_vector();

	std::cout << "--------------- stack test ---------------" << std::endl;
	func_stack();

	std::cout << "--------------- map test ---------------" << std::endl;
	func_map();

	return (0);
}
