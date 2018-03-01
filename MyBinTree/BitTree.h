#ifndef BITTREE_H
#define BITTREE_H

#include <iostream>
#include <memory>  
#include <exception>
#include <algorithm>

enum Descendant {
	right,
	left
};

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

	void insert(K &key, V &value)
	{
		if (size == 0) {
			root = std::unique_ptr<Node> (new Node(value, key, nullptr, nullptr));
			++size;
			return;
		}
		std::less<K> comp;
		Node *tmp = this->root.get();
		while (1) {
			if (comp(tmp->key, key)) {
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

	bool get(K &key, V& out) {
		std::less<K> comp;
		Node *tmp = this->root.get();
		while (tmp != nullptr) {
			if (!comp(key, tmp->key) && !comp(tmp->key, key)) { // keys are equal
				out = tmp->value;
				return true;
			}
			else if (comp (key, tmp->key)) {
				tmp = tmp->right.get();
			}
			else {
				tmp = tmp->left.get();
			}
		}
		return false;
	};

	bool detach (K &key, V& out)
	{
		if (get(key, out)) {
			erase(key);
			return true;
		}
		return false;
	};

	void erase(K &key) {
		std::less<K> comp;
		Descendant descendant_tmp_2 = left;
		Node *tmp_1 = root.get();
		Node *tmp_2 = root.get();
		while (tmp_1 != nullptr) {
			if (!comp(tmp_1->key, key) && !comp(key, tmp_1->key)) { 
				if (tmp_1->right.get() == nullptr) { // right child is missing
					if (tmp_1->left.get() != nullptr) { // there is a left descendant
						if (!comp(root.get()->key, key) && !comp(key, root.get()->key)) // delete root
							root = std::move(root->left);
						else if (descendant_tmp_2 == left)  
							tmp_2->left = std::move(tmp_1->left);
						else // descendant_tmp_2 == right
							tmp_2->right = std::move(tmp_1->left);
						--size;
						return;
					}
					// left child is missing
					if (!comp(root.get()->key, key) && !comp(key, root.get()->key)) // delete root
						root = nullptr;
					else if (descendant_tmp_2 == left) 
						tmp_2->left = nullptr;
					else // descendant_tmp_2 == right
						tmp_2->right = nullptr; 
					--size;
					return;
				}
				else if (tmp_1->left.get() == nullptr) {
					if (!comp(root.get()->key, key) && !comp(key, root.get()->key)) // delete root
						root = std::move (root.get()->right);
					else if (descendant_tmp_2 == left)
						tmp_2->left = std::move(tmp_1->right);
					else // descendant_tmp_2 == right
						tmp_2->right = std::move(tmp_1->right);
					--size;
					return;
				}
				else { // tmp_1->left.get() != nullptr 
					tmp_1 = tmp_1->left.get();
					while (tmp_1->right.get() != nullptr) {
						tmp_1 = tmp_1->right.get();
					}
					if (!comp(root.get()->key, key) && !comp(key, root.get()->key)) {
						tmp_1->right = std::move(root.get()->right);
						root = std::move(root.get()->left);
					}
					else if (descendant_tmp_2 == right) {
						tmp_1->right = std::move(tmp_2->right.get()->right);
						tmp_2->right = std::move(tmp_2->right.get()->left);
					}
					else { // descendant_tmp_2 == left
						tmp_1->right = std::move(tmp_2->left.get()->right);
						tmp_2->left = std::move(tmp_2->left.get()->left);
					}
					--size;
					return;
				}
			}
			else if (comp(tmp_1->key, key)) {
				tmp_2 = tmp_1;
				tmp_1 = tmp_1->left.get();
				descendant_tmp_2 = left;
			}
			else {
				tmp_2 = tmp_1;
				tmp_1 = tmp_1->right.get();
				descendant_tmp_2 = right;
			}
		}
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
		throw Exception("Element with this key is missing");
	};
};

#endif 