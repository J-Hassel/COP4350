#ifndef BST_HPP
#define BST_HPP
//Name: Jonathan Hassel
//Date: 3/25/17
//Class: cop4530 - Duan

#include "bst.h"

//BST CLASS----------------------------------------------------------------------------------------------------------

//PUBLIC MEMBER FUNCTIONS--------------------------------------------------------------------------------------------
template <typename T>
BST<T>::BST(int th): threshold_value{th}
{
	//1 parameter constructor
}

template <typename T>
BST<T>::BST(const std::string input, int th): threshold_value{th}
{	//2 parameter constructor
	buildFromInputString(input);
}

template <typename T>
BST<T>::BST(const BST& t): root{clone(t.root)}, threshold_value{t.threshold_value}
{	//copy constructor

}

template <typename T>
BST<T>::BST(BST&& t): root{std::move(t.root)}, threshold_value{std::move(t.threshold_value)}
{	//move constructor
	t.root = nullptr;
}

template <typename T>
BST<T>::~BST()
{	//cleans up dynamically allocated memory
	makeEmpty();
}

template <typename T>
const typename BST<T>::BST& BST<T>::operator=(const BST& t)
{	//copy assignment operator
	BST<T> copy = t;
	std::swap(*this, copy);
	return *this;
}

template <typename T>
const typename BST<T>::BST& BST<T>::operator=(BST&& t)
{	//move assignment operator
	std::swap(root, t.root);
}



template <typename T>
void BST<T>::buildFromInputString(const std::string input)
{
	makeEmpty();

	std::stringstream inputStream(input);

	std::vector<T> tempVec;
	T tempElement;

	//seperates every element and pushes them into a vector
	while(inputStream >> tempElement)
		tempVec.push_back(tempElement);

	//inserts each value into the tree
	for(int i = 0; i < tempVec.size(); ++i)
		insert(tempVec[i]);
}

template <typename T>
bool BST<T>::empty()
{	//height of -1 == empty
	if(height() == -1)
		return true;

	return false;
}



template <typename T>
void BST<T>::printInOrder() const
{
	printInOrder(root);
	std::cout << '\n';
}

template <typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder(root);
	std::cout << '\n';
}

template <typename T>
int BST<T>::numOfNodes() const
{
	return numOfNodes(root);
}

template <typename T>
int BST<T>::height() const
{
	return height(root);
}

template <typename T>
void BST<T>::makeEmpty()
{
	makeEmpty(root);
}

template <typename T>
void BST<T>::insert(const T& v)
{
	insert(v, root);
}

template <typename T>
void BST<T>::insert(T&& v)
{
	insert(std::move(v), root);
}

template <typename T>
void BST<T>::remove(const T& v)
{
	remove(v, root);
}

template <typename T>
bool BST<T>::contains(const T& v)
{
	if(v == root->element)
	{
		root->searchCount = 0;
		return true;
	}

	contains(v, root, root);
}


//PRIVATE MEMBER FUNCTIONS---------------------------------------------------------------------------------------------
template <typename T>
void BST<T>::printInOrder(BSTNode* t) const
{	//if t == nullptr, then tree is empty and nothing will be printed
	if(t == nullptr)
		return;

	printInOrder(t->left);

	std::cout << t->element << ' ';

	printInOrder(t->right);
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode* t) const
{	//if t == nullptr, then tree is empty and nothing will be printed
	if(t == nullptr)
		return;

	std::queue<BSTNode*> tempQueue;

	//breadth first traversal to print elements in level order
	tempQueue.push(t);
	while(tempQueue.size() > 0)
	{
		BSTNode* node = tempQueue.front();
		tempQueue.pop();

		std::cout << node->element << ' ';

		if(node->left != nullptr)
			tempQueue.push(node->left);

		if(node->right != nullptr)
			tempQueue.push(node->right);
	}
}

template <typename T>
int BST<T>::numOfNodes(BSTNode* t) const
{
	int count = 1;

	//if t == nullptr then there are no elements
	if(t == nullptr)
		return 0;
	else
	{	//adds 1 recursively every time it encounters a child
		count += numOfNodes(t->left);
		count += numOfNodes(t->right);
		return count;
	}
}

template <typename T>
int BST<T>::height(BSTNode* t) const
{	//if t == nullptr, then there are no nodes ans the height == -1
	if(t == nullptr)
		return -1;

	//returns 1 + the largest height between left and right children nodes
	return 1 + std::max(height(t->left), height(t->right));
}

template <typename T>
void BST<T>::makeEmpty(BSTNode*& t)
{
	if(t != nullptr)
	{	//recursively deletes left and right children, then the parent node
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template <typename T>
void BST<T>::insert(const T& v, BSTNode*& t)
{
	if(t == nullptr)		//if there is no root, create a new root
		t = new BSTNode{v, nullptr, nullptr};
	else if(v < t->element)		//if the element is less than t->element, then insert into left side(recursively checks to find position to insert to)
		insert(v, t->left);
	else if(v > t->element)		//if the element is greater than t->element, then insert into right side(recursively checks to find position to insert to)
		insert(v, t->right);
}

template <typename T>
void BST<T>::insert(T&& v, BSTNode*& t)
{	//move version of insert above
	if(t == nullptr)
		t = new BSTNode{std::move(v), nullptr, nullptr};
	else if(v < t->element)
		insert(std::move(v), t->left);
	else if(v > t->element)
		insert(std::move(v), t->right);
}

template <typename T>
void BST<T>::remove(const T& v, BSTNode*& t)
{
	if (t == nullptr)		//cant remove something from an empty node
		return;
	if(v < t->element)			//locating element
		remove(v, t->left);
	else if(v > t->element)
		remove(v, t->right);	//locating element
	else if(t->left != nullptr && t->right != nullptr)
	{	//if element has two children, replace it with the smallest value in the subtree
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{	//if the element has one child, point it to the child
		BSTNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template <typename T>
const typename BST<T>::BSTNode* BST<T>::findMin(BSTNode*& t) const
{	//finds the minimum value in a node
	if(t == nullptr)
		return nullptr;
	if(t->left == nullptr)
		return t;
	return findMin(t->left);
}

template <typename T>
bool BST<T>::contains(const T& v, BSTNode*& t, BSTNode*& p)
{
	if(t == nullptr)		//if the sub tree is empty, it contains no nodes
		return false;
	else if(v < t->element)			//finding element
		return contains(v, t->left, t);
	else if(v > t->element)			//finding element
		return contains(v, t->right, t);
	else
	{
		t->searchCount++;
		if(t->searchCount >= threshold_value)
		{	//reset search count
			t->searchCount = 0;

			//rotations
			if(p->left == nullptr)
				rotateWithRightChild(p);
			else if(p->right == nullptr)
				rotateWithLeftChild(p);
			else if((p->left->element >= t->element) && (p->left->element <= t->element))
				rotateWithLeftChild(p);
			else
				rotateWithRightChild(p);
		}
		return true;
	}
}

template <typename T>
void BST<T>::rotateWithLeftChild(BSTNode*& p)
{
	BSTNode* t = p->left;
	p->left = t->right;
	t->right = p;
	p = t;
}

template <typename T>
void BST<T>::rotateWithRightChild(BSTNode*& p)
{
	BSTNode* t = p->right;
	p->right = t->left;
	t->left = p;
	p = t;
}

template <typename T>
typename BST<T>::BSTNode* BST<T>::clone(BSTNode* t) const
{
	if(t == nullptr)		//cant clone anything that is not there
		return nullptr;
	else					//creates a new node that is a clone of t
		return new BSTNode{t->element, clone(t->left), clone(t->right)};
}

#endif
