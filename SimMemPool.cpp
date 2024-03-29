// SimMemPool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "mempool_heap.hpp"
#include "memory_pool.hpp"
#include <iostream>

class A
{
private:
	typedef memory_pool<A, mempool_heap<A, 16> > MemoryPool;
	static MemoryPool mem;
private:
	int data; 
public:
	A(int data) : data(data) {}
	virtual ~A() {}

	void * operator new(unsigned int n)
	{
		return mem.alloc(n);
	}

	void operator delete(void * p)
	{
		mem.free(p);
	}
};

A::MemoryPool A::mem; 

int main(int, char **)
{
	A * a[64];
	std::cout << "Memory size = " << sizeof(A) << std::endl;
	for (int i = 0; i < 16; ++i)
	{
		a[i] = new A(i);
		std::cout << a[i] << std::endl;
	}

	std::cout << "\nDelete Memonry " << std::endl;
	for (int i = 0; i < 16; ++i) {
		delete a[i];
		
		std::cout << a[i] << std::endl;
		a[i] = NULL;
	}
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
