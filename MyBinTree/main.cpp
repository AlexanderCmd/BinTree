#include "BitTree.h"

int
main() {
	setlocale(LC_ALL, "rus");
	BitTree<char, int> test;
	test.insert(1, 'a');
	test.insert(9, 'b');
	test.insert(2, 'c');
	test.insert(7, 'd');
	test.insert(3, 'e');
	test.insert(4, 'f');
	test.insert(3, 'g');
	test.insert(10, 'h');	
 	
	char a;
	if (test.get(3, a)) {
		std::cout << a << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
	system("PAUSE");
	return 0;
}