#ifndef BITTREE_H
#define BITTREE_H

#include <iostream>
#include <memory>  
#include <exception>

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
	
	BitTree (std::initializer_list<std::pair <K, V>>tree) {
		for (const auto &i : tree)
			this->insert(i.first, i.second);
	};

	BitTree(BitTree &obj) { 
		Node *tmp = obj.root.get();
		copytree (tmp);
	};

	BitTree(BitTree &&obj) {
		size = obj.size;
		root = std::move(obj.root);
	};
	void clear()
	{
		root = nullptr;
		size = 0;
	};
	BitTree& operator= (BitTree &obj) {
		if (this == &obj)
			return *this;
		clear();
		Node *tmp = obj.root.get();
		copytree(tmp);
		return *this;
	};

	BitTree& operator= (BitTree &&obj) {
		if (this == &obj)
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
		if (root.get()->key == key) {
			out = root.get()->value;
			if (root.get()->right.get() != nullptr && root.get()->left.get() != nullptr) {
				Node *tmp = root.get()->left.get();
				while (tmp->right.get() != nullptr) {
					tmp = tmp->right.get();
				}
				tmp->right = std::move(root->right);
				root = std::move(root->left);
			}
			else if (root.get()->right.get() != nullptr) {
				root = std::move(root->right);
			}
			else if (root.get()->left.get() != nullptr) {
				root = std::move(root->left);
			}
			else {
				root = nullptr;
			}
			--size;
			return true;
		}
		Node *tmp = this->root.get();
		while (tmp != nullptr) {
			if (tmp->key > key) {
				if (tmp->right.get()->key == key) {
					out = tmp->right.get()->value;
					if (tmp->right.get()->right.get() != nullptr && tmp->right.get()->left.get() != nullptr) {
						Node* tmp_2 = tmp->right.get()->left.get();
						while (tmp_2->right.get() != nullptr) {
							tmp_2 = tmp_2->right.get();
						}
						tmp_2->right = std::move(tmp->right.get()->right);
						tmp->right = std::move(tmp->right.get()->left);
					}
					else if (tmp->right.get()->right.get() != nullptr) {
						tmp->right = std::move(tmp->right.get()->right);
					}
					else if (tmp->right.get()->left.get() != nullptr) {
						tmp->right = std::move(tmp->right.get()->left);
					}
					else {
						tmp->right = nullptr;
					}
					--size;
					return true;
				}
				tmp = tmp->right.get();
			}
			else {
				if (tmp->left.get()->key == key) {
					out = tmp->left.get()->value;
					if (tmp->left.get()->right.get() != nullptr && tmp->left.get()->left.get() != nullptr) {
						Node* tmp_2 = tmp->left.get()->left.get();
						while (tmp_2->right.get() != nullptr) {
							tmp_2 = tmp_2->right.get();
						}
						tmp_2->right = std::move(tmp->left.get()->right);
						tmp->left = std::move(tmp->left.get()->left);
					}
					else if (tmp->left.get()->right.get() != nullptr) {
						tmp->left = std::move(tmp->left.get()->right);
					}
					else if (tmp->left.get()->left.get() != nullptr) {
						tmp->left = std::move(tmp->left.get()->left);
					}
					else {
						tmp->left = nullptr;
					}
					--size;
					return true;
				}
				tmp = tmp->left.get();
			}
		}
		return false;
	};

	void copytree (Node* tmp) {
		insert(tmp->key, tmp->value);
		if (tmp->right != nullptr) {
			copytree(tmp->right.get());
		}
		if (tmp->left != nullptr) {
			copytree(tmp->left.get());
		}
	};

	V& operator[](K& key) {
		V tmp;
		if (get(key, tmp))
			return tmp;
		insert (key, NULL);
		return NU ;
	};

	const V& operator[](K& val) const {
		V tmp;
		if (get(key, tmp))
			return tmp;
		throw Exception("Нет элемента с данным ключом");
	};
};

#endif 

