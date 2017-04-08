#include <iostream>
#include "SortedDynamicArray.h"

int main() {
	SortedDynamicArray<int> sorted;
	sorted.add(2);
	sorted.serialize(std::cout);
	std::cout << std::endl;

	sorted.add(5);
	sorted.serialize(std::cout);
	std::cout << std::endl;

	sorted.add(1);
	sorted.serialize(std::cout);
	std::cout << std::endl;

	sorted.add(7);
	sorted.serialize(std::cout);
	std::cout << std::endl;

	sorted.add(3);
	sorted.serialize(std::cout);
	std::cout << std::endl;

	sorted.add(4);
	sorted.serialize(std::cout);
	system("pause");
	return 0;
}
