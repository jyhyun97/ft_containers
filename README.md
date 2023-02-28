# ft_containers

## 실행

make && ./ft_containers [0 이상의 시드값]

## 요구사항

c++의 STL 컨테이너 중 vector, stack, map을 템플릿을 사용해 구현하는 과제.(c++98 버전)

## 구현 과정 요약

vector 이터레이터와 관련 오버로딩 구현, allocator 사용한 벡터 할당 알고리즘 구현 등

stack은 구현한 vector을 바탕으로 기능을 제한해 스택처럼 사용할 수 있는 컨테이너 어댑터로 구현

map은 맵을 사용해 데이터를 관리하기 위해 AVL트리를 사용.

그 외 위 세 컨테이너 구현에 필요한 아래 템플릿 클래스/함수 구현

```
std::iterator_traits
std::reverse_iterator
std::enable_if
std::is_integral
std::equal and/or std::lexicographical_compare
std::pair
std::make_pair
```
