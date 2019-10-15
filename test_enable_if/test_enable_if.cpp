// test_enable_if.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

template<typename> struct int_ { typedef int type; };

template<class> struct type_sink { typedef void type; }; // consumes a type, and makes it `void`
template<class T> using type_sink_t = typename type_sink<T>::type;
template<class T, class = void> struct has_begin : std::false_type {}; \
template<class T> struct has_begin<
	T,
	type_sink_t< decltype(std::declval<T>().begin()) >
> : std::true_type {};

template<class T, class = void> struct has_c_str : std::false_type {}; \
template<class T> struct has_c_str<
	T,
	type_sink_t< decltype(std::declval<T>().substr()) >
> : std::true_type {};


template <class T , typename std::enable_if <has_begin<T>::value , int > ::type = 0>
void test(T t)
{
	std::cout << "yes" << std::endl;
}

template<>
void test<std::string>(std::string)
{
	std::cout << "no" << std::endl;
}

template <class T, typename std::enable_if <!has_begin<T>::value, int > ::type = 0>
void test(T t)
{
	std::cout << "other" << std::endl;
}

template<>
void test(int t)
{
	std::cout << "int" << std::endl;
}

int main()
{
	std::vector<int> a;
	std::string b;	
	test(a);
	test(b);
	test(1);
	test(1.1);

}
