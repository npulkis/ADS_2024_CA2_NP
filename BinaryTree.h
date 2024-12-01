#pragma once
#include "BSTNode.h"

#include <vector>
template <class T>
class BinaryTree
{
	void addItemToArray(BSTNode<T>* node, int& pos, T* arr) const;
public:
	BSTNode<T>* root;
	BinaryTree();
	BinaryTree(const BinaryTree<T>& other);
	BinaryTree<T> operator=(const BinaryTree<T>& other);
	void add(T& item);
	bool remove(T& item);
	void clear();
	int count() const;
	T& get(T& item);

	void printInOrder() const;
	void printInOrder(BSTNode<T>* node) const;
	void printPreOrder() const;
	void printPreOrder(BSTNode<T>* node) const;
	void printPostOrder() const;
	void printPostOrder(BSTNode<T>* node) const;
	T* toArray();
	~BinaryTree();
};

template <class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	root = nullptr;
	if (other.root != nullptr)
		root = new BSTNode<T>(*other.root);
}
template <class T>
BinaryTree<T> BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
	if (this == &other)
		return *this;
	if (other.root != nullptr)
		root = new BSTNode<T>(*other.root);
	else
		root = nullptr;
	return *this;

}
template <class T>
void BinaryTree<T>::add(T& item)
{
	if (root == nullptr)
	{
		root = new BSTNode<T>(item);
		root->setItem(item);
	}
	else
	{
		root->add(item);
	}
}
template <class T>
int BinaryTree<T>::count() const
{
	if (root == nullptr)
		return 0;
	return root->count();
}
template <class T>
bool BinaryTree<T>::remove(T& item)
{
	BSTNode<T>* toBeRemoved = root;
	BSTNode<T>* parent = nullptr;
	bool found = false;

	while (!found && toBeRemoved != nullptr)
	{

		if (toBeRemoved->getItem() == item)
		{

			found = true;
		}
		else
		{
			parent = toBeRemoved;
			if (toBeRemoved->getItem() > item)
			{
				toBeRemoved = toBeRemoved->getLeft();
			}
			else
			{
				toBeRemoved = toBeRemoved->getRight();
			}
		}
	}
	if (!found)
		return false;

	if (toBeRemoved->getLeft() == nullptr || toBeRemoved->getRight() == nullptr)
	{
		BSTNode<T>* newChild;
		if (toBeRemoved->getLeft() == nullptr)
		{
			newChild = toBeRemoved->getRight();
		}
		else
		{
			newChild = toBeRemoved->getLeft();
		}
		if (parent == nullptr)
		{
			root = newChild;
		}
		else if (parent->getLeft() == toBeRemoved)
		{
			parent->setLeft(newChild);
		}
		else
		{
			parent->setRight(newChild);
		}
		return true;
	}

	BSTNode<T>* smallestParent = toBeRemoved;
	BSTNode<T>* smallest = toBeRemoved->getRight();
	while (smallest->getLeft() != nullptr)
	{
		smallestParent = smallest;
		smallest = smallest->getLeft();
	}
	toBeRemoved->setItem(smallest->getItem());
	if (smallestParent == toBeRemoved)
	{
		smallestParent->setRight(smallest->getRight());
	}
	else
	{
		smallestParent->setLeft(smallest->getRight());
	}

}
template <class T>
T& BinaryTree<T>::get(T& item)
{
	bool found = false;
	BSTNode<T>* current = root;
	while (!found)
	{

		if (current == nullptr)
			break;
		if (current->getItem() == item)
			return current->getItem();
		else if (current->getItem() > item)
			current = current->getLeft();
		else
			current = current->getRight();
	}
	throw logic_error("ITem not found");
}
template <class T>
void BinaryTree<T>::addItemToArray(BSTNode<T>* node, int& pos, T* arr) const
{
	if (node != nullptr)
	{
		addItemToArray(node->getLeft(), pos, arr);
		arr[pos] = node->getItem();
		pos++;
		addItemToArray(node->getRight(), pos, arr);
	}

}

template <class T>
T* BinaryTree<T>::toArray()
{
	T* arr = new T[root->count()];
	int pos = 0;
	addItemToArray(root, pos, arr);
	return arr;
}

template <class T>
void BinaryTree<T>::clear()
{
	delete root;
	root = nullptr;
}
template <class T>
BinaryTree<T>::~BinaryTree()
{
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
	}
}

template<class T>
void BinaryTree<T>::printInOrder() const
{
	this->printInOrder(root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::printInOrder(BSTNode<T>* node) const {
	if (node == nullptr) return;
	printInOrder(node->getLeft());
	std::cout << node->getItem() << " ";
	printInOrder(node->getRight());
}

template<class T>
void BinaryTree<T>::printPreOrder() const
{
	this->printPreOrder(root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::printPreOrder(BSTNode<T>* node) const {
	if (node == nullptr) return;
	std::cout << node->getItem() << " ";
	printPreOrder(node->getLeft());
	printPreOrder(node->getRight());
}

template<class T>
void BinaryTree<T>::printPostOrder() const
{
	this->printPostOrder(root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::printPostOrder(BSTNode<T>* node) const {
	if (node == nullptr) return;
	printPostOrder(node->getLeft());
	printPostOrder(node->getRight());
	std::cout << node->getItem() << " ";
}