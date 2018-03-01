#include "BitTree.h"

int
main() {
	char simvol = 'a';
	int num = 0;
	BitTree<char, int> test;
	test.insert(num, simvol);
	num = 10;
	test.insert(num, simvol); 
	num = -1;
	test.insert(num, simvol);
	num = 8;
	test.insert(num, simvol);
	num = 0;
	test.erase(num);
	num = 10;
	if (test.detach(num, simvol)) {
		std::cout << simvol << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
	if (test.get(num, simvol)) {
		std::cout << simvol << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
	system("PAUSE");
	return 0;
}