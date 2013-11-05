#include "LazyStream.h"
#include <iostream>

Stream<int> mkStream(int a, int b)
{
	//Stream<int> s([]()
	//{
	//	return std::unique_ptr<Cell<int>>(new Cell<int>());
	//});

	Stream<int> s;

	//Stream<int> s1([=]()
	//{
	//	return std::unique_ptr<Cell<int>>(new Cell<int>(13, s));
	//});

	Stream<int> s1(CellFun<int>(b, s));

	// int x = s1.get();
	// bool b3 = s1.tail().isEmpty();

	//Stream<int> s2([=]()
	//{
	//	return std::unique_ptr<Cell<int>>(new Cell<int>(14, s1));
	//});

	Stream<int> s2(CellFun<int>(a, s1));
	return s2;
}

template<class T>
void forcePrint(Stream<T> const & s)
{
	if (s.isEmpty())
	{
		std::cout << std::endl;
	}
	else
	{
		T v = s.get();
		auto tail = s.tail();
		std::cout << v << " ";
		forcePrint(tail);
	}
}

template<class T>
void lazyPrint(Stream<T> const & s)
{
	if (s.isEmpty())
	{
		std::cout << std::endl;
	}
	else if (s.isForced())
	{
		T v = s.get();
		auto tail = s.tail();
		std::cout << v << " ";
		lazyPrint(tail);
	}
	else
	{
		std::cout << "?\n";
	}
}

void main()
{
	auto s1 = mkStream(5, 10);
	auto s2 = mkStream(15, 20);
	auto s3 = concat<int>(s1, s2);
	auto s = concat(s3, s3);
	lazyPrint(s);
	int x = s.get();
	lazyPrint(s);
	auto tail = s.tail();
	lazyPrint(s);
	int y = tail.get();
	lazyPrint(s);

	auto front = s.take(4);
	std::cout << "Take 4: ";
	lazyPrint(front);
	lazyPrint(s);

	auto back1 = s.drop(3);
	std::cout << "Drop 3 (forces first stream): ";
	lazyPrint(back1);
	lazyPrint(s);

	/*
	auto back = s.drop(5);
	std::cout << "Drop 5 (forces both streams): ";
	lazyPrint(back);
	lazyPrint(s);
	*/

	auto rev = s.reverse();
	std::cout << "Reverse (forces the original): ";
	lazyPrint(rev);
	lazyPrint(s);
	std::cout << "Force reversed stream: ";
	forcePrint(rev);

	std::cout << "Force: \n";
	forcePrint(s);
}