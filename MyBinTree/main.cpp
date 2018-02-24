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
	test.insert(0, 'j');
	BitTree<char, int> test_2;
	std::pair<int, int> test(1, 2);
	BitTree<int, int> pr {test, test};
	test_2 = test;
	char a;
	if (test.detach(1, a)) {
		std::cout << a << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
	if (test_2.get(1, a)) {
		std::cout << a << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
	system("PAUSE");
	return 0;
}