#ifndef BITTREE_H
#define BITTREE_H

#include <iostream>
#include <memory>  

template <typename V, typename K>
class BitTree {
private:
	class Node {
	private:
		V value;
		K key;
		std::unique_ptr <Node> right;
		std::unique_ptr <Node> left;
	public:
		Node(const V value, const K key, std::unique_ptr <Node> right, std::unique_ptr <Node> left) {
			this->value = velue;
			this->key = key;
			this->right = std::move(right);
			this->left = std::move(left);
		};
	};
	std::unique_ptr <Node> roof;
	size_t size;
public:
	BitTree() {
		roof = nullptr;
		size = 0;
	};
};

#endif 

