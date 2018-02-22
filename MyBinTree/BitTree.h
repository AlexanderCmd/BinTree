#ifndef BITTREE_H
#define BITTREE_H

#include <iostream>
#include <memory>  

template <typename V, typename K>
class BitTree {
private:
	class Node {
	public:
		V value;
		K key;
		std::unique_ptr <Node> right;
		std::unique_ptr <Node> left;
		Node(const V value, const K key, std::unique_ptr <Node> right, std::unique_ptr <Node> left) {
			this->value = value;
			this->key = key;
			this->right = std::move(right);
			this->left = std::move(left);
		};
	};

	std::unique_ptr <Node> root;
	size_t size;
public:
	BitTree() {
		root = nullptr;
		size = 0;
	};
	
	/*BitTree(BitTree &obj) { 
		
	};*/

	BitTree(BitTree &&obj) {
		size = obj.size;
		root = std::move(obj.root);
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
		root = std::move (obj.root);
		return *this;
	}
	
	size_t get_size() const {
		return this->size;
	};

	bool is_empty() const {
		return this->size != 0;
	};

	void insert(K key, V value)
	{
		if (size == 0) {
			root = std::unique_ptr<Node> (new Node(value, key, nullptr, nullptr));
			++size;
			return;
		}
		Node *tmp = this->root.get();
		while (1) {
			if (key > tmp->key) {
				if (tmp->left.get() == nullptr) {
					tmp->left = std::unique_ptr<Node>(new Node(value, key, nullptr, nullptr));
					++size;
					return;
				}
				tmp = tmp->left.get();
			}
			else {
				if (tmp->right.get() == nullptr) {
					tmp->right = std::unique_ptr<Node>(new Node(value, key, nullptr, nullptr));
					++size;
					return;
				}
				tmp = tmp->right.get();
			}
		}
	};

	bool get(K key, V& out) {
		Node *tmp = this->root.get();
		while (tmp != nullptr) {
			if (tmp->key == key) {
				out = tmp->value;
				return true;
			}
			else if (tmp->key > key) {
				tmp = tmp->right.get();
			}
			else {
				tmp = tmp->left.get();
			}
		}
		return false;
	};

	bool detach (K key, V& out)
	{
		Node *tmp = this->root.get();
		while (tmp != nullptr) {
			if (tmp->key > key) {
				if (tmp->right.get()->key == key) {
					// дописать перераспределеие дерева
					out = tmp->value;
					return true;
				}
				tmp = tmp->right.get();
			}
			else {
				if (tmp->left.get()->key == key) {
					// дописать перераспределение дерева
					out = tmp->value;
					return true;
				}
				tmp = tmp->left.get();
			}
		}
	};
};

#endif 

