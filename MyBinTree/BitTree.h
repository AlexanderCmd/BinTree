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
		
		V get_value() {
			return value;
		}

		K get_key() {
			return key;
		}

		Node* get_left() {
			return left.get();
		}

		Node* get_right() {
			return right.get();
		}
	};

	std::unique_ptr <Node> roof;
	size_t size;
public:
	BitTree() {
		roof = nullptr;
		size = 0;
	};
	
	/*BitTree(BitTree &obj) { 
		
	};*/

	BitTree(BitTree &&obj) {
		size = obj.size;
		roof = std::move(obj.roof);
	};

	/*BitTree& operator= (BitTree &obj) {
		if (this == obj)
			return *this;
		
		return *this;
	};*/

	BitTree& operator= (BitTree &&obj) {
		if (this == obj)
			return *this;
		clear();
		size = obj.size;
		roof = std::move (obj.roof);
		return *this;
	}
	
	size_t get_size() const {
		return this->size;
	};

	bool is_empty() const {
		return this->size != 0;
	};

	/*void insert(K key, V value)
	{

	};*/

	bool get(K key, V& out) {
		Node *tmp = this->roof.get();
		while (tmp != nullptr) {
			if (tmp->get_key() == key) {
				out = tmp->get_value();
				return true;
			}
			else if (tmp->get_key() > key) {
				tmp = tmp->get_right();
			}
			else {
				tmp = tmp->get_left();
			}
		}
		return false;
	};
};

#endif 

