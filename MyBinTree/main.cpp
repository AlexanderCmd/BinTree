#include "BitTree.h"

int
main() {
	setlocale(LC_ALL, "rus");
	BitTree<int, int> test;
	int a;
	if (test.get(4, a)) {
		std::cout << "+" << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
	system("PAUSE");
	return 0;
}