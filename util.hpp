#ifndef UTIL_HPP
#define UTIL_HPP

#include <memory>

namespace ft
{
    template <class Iterator>
    class iterator_traits{
        public :
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T *>{
        public :
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>{
        public :
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    //enable_if//컴파일러가 올바른 오버로딩 함수 타입을 찾기 위해, 해당하지 않는 함수는 타입 치환 오류를 발생시켜야 함.
    //T가 존재하는 타입이라면 type가 반환되고, 없으면 반환되지 않는 원리.
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
    
    //is_integral
    //타입을 확인해 true false로 반환하기 위한 구조체
    template <class T, T v>
    struct integral_constant
    {
        //typedef T value_type;
        //typedef integral_constant<T, v> type;
        static const T value = v;
        //const operator T() { return v; } //c++14;
    };

	template <class T> struct is_integral : public ft::integral_constant<bool, false>{};
    //아무것도 해당하지 않으면 false 하게 만들어놓고 타입 있는것들은 true로 만들기
    template <> struct is_integral<bool> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<char> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<wchar_t> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<signed char> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<short int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<long int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<long long int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned char> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned short int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned long int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true>{};
    
    //굳이 constant 안만들고 아래처럼 해도 돌아가지 않을까
    //template <class T> struct is_integral{ value = false; };
    //template <> struct is_integral<type> { value = true; };

    //equal
    //두 이터레이터 돌면서 값이 일치하는 지 확인하기
    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    };

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred){
        while (first1 != last1)
        {
            if (!pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    };

    // lexicographical_compare
    // 대소비교, 첫번째 요소가 작으면 true, 크면 false,
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (*first1 < *first2)
                return true;
            else if (first2 == last2 || *first1 > *first2)
                return false;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    };

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Compare comp){
        while (first1 != last1)
        {
            if (comp(*first1, *first2))
                return true;
            else if (first2 == last2 || comp(*first2, *first1))
                return false;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    };

    //pair
    //두 클래스를 하나의 객체로 취급할 수 있게 해준다.

    template <class T1, class T2> struct pair{
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(), second() {};
        template<class U, class V>
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
        pair (const first_type& a, const second_type& b) : first(a), second(b) {};
        pair& operator= (const pair& pr){
            first = pr.first;
            second = pr.second;
            return *this;
        };
    };
    template <class T1, class T2> struct pair<const T1, T2>{
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(), second() {};
        template<class U, class V>
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
        pair (const first_type& a, const second_type& b) : first(a), second(b) {};
        pair& operator= (const pair& pr){
            first = pr.first;
            second = pr.second;
            return *this;
        };
    };
    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    };
    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){
        return !(lhs == rhs);
    };
    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){
        return (lhs.first < rhs.first || ((lhs.first == rhs.first) && lhs.second < rhs.second));
    };
    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){
        return !(rhs < lhs);
    };
    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){
        return rhs < lhs;
    };
    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){
        return !(lhs < rhs);
    };

    //make_pair
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    };

    template <class Iterator>
	class reverse_iterator
	{
		public :
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

			reverse_iterator() : current(){};
			explicit reverse_iterator(iterator_type it) : current(it){};
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : current(rev_it.base()){};
			iterator_type base() const {return current;}

            template<class U>
            reverse_iterator &operator=(const reverse_iterator<U> &rit)
            {
                current = rit.base();
                return (*this);
            }
			reverse_iterator operator+(difference_type n) const {return reverse_iterator(current - n);};
			reverse_iterator &operator++() {--current; return *this;};
			reverse_iterator operator++(int) {
                reverse_iterator tmp(current);
                --current;
                return (tmp);
            };
            reverse_iterator &operator+=(difference_type n){
                current -= n;
                return (*this);
            };
			reverse_iterator operator-(difference_type n) const {return reverse_iterator(current + n);};
			reverse_iterator &operator--(){++current; return *this;};
			reverse_iterator operator--(int) {
                reverse_iterator tmp(current);
                ++current;
                return (tmp);
            };
			reverse_iterator &operator-=(difference_type n){
                current += n;
                return (*this);
            };
            reference operator*() const {
                iterator_type tmp(current);
                tmp--;
                return *tmp;
                //return *current;
            };
            pointer operator->() const
            {
			    return &(operator*());
            };
            reference operator[](difference_type n) const
            {
                return (*(*this + n));
            };

        private :
			iterator_type current;
	};
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() == rhs.base());
    };
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() != rhs.base());
    };
    template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() > rhs.base());
    };
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() >= rhs.base());
    };
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() < rhs.base());
    };
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() <= rhs.base());
    };

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it){
            			return (rev_it + n);
    };

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs){
            			return (rhs.base() - lhs.base());
    };

}

#endif