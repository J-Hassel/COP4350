#ifndef BST_H
#define BST_H
//Name: Jonathan Hassel
//Date: 3/24/17
//Class: cop4530 - Duan

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

namespace cop4530
{

template <typename T>
class BST
{
	public:
		//CONSTRUCTORS-------------------------------------------------------------------------------
		BST(int th = default_threshold_value);							//1 parameter constructor	|
		BST(const std::string input, int th = default_threshold_value);	//2 parameter constructor	|
		BST(const BST& t);												//copy constructor			|
		BST(BST&& t);													//move constructor			|
		~BST();															//destructor				|
		//-------------------------------------------------------------------------------------------

		//ASSIGNMENT OPERATORS---------------------------------------------------
		const BST& operator=(const BST& t);			//copy assignment operator	|
		const BST& operator=(BST&& t);				//move assignment operator	|
		//-----------------------------------------------------------------------

		//PUBLIC INTERFACES---------------------------------------
		void buildFromInputString(const std::string input);
		bool empty();

		void printInOrder() const;
		void printLevelOrder() const;
		int numOfNodes() const;
		int height() const;
		void makeEmpty();
		void insert(const T& v);
		void insert(T&& v);
		void remove(const T& v);
		bool contains(const T& v);
		//--------------------------------------------------------

	private:

		//BSTNode STRUCT
		struct BSTNode
		{
			int searchCount = 0;
			T element;
			BSTNode* left;
			BSTNode* right;

			//for constructing new nodes
			BSTNode(const T& e, BSTNode* l, BSTNode* r, int h = 0): element{e}, left{l}, right{r}{}
			BSTNode(T&& e, BSTNode* l, BSTNode* r, int h = 0): element{std::move(e)}, left{l}, right{r}{}
		};

		static const int default_threshold_value = 1;
		int threshold_value;
		BSTNode* root = nullptr;

		//PRIVATE INTERFACES--------------------------------------
		void printInOrder(BSTNode* t) const;
		void printLevelOrder(BSTNode* t) const;
		int numOfNodes(BSTNode* t) const;
		int height(BSTNode* t) const;
		void makeEmpty(BSTNode*& t);
		void insert(const T& v, BSTNode*& t);
		void insert(T&& v, BSTNode*& t);
		void remove(const T& v, BSTNode*& t);
		const BSTNode* findMin(BSTNode*& t) const;
		bool contains(const T& v, BSTNode*& t, BSTNode*& p);
		void rotateWithLeftChild(BSTNode*& k2);
		void rotateWithRightChild(BSTNode*& k2);
		BSTNode* clone(BSTNode* t) const;
		//--------------------------------------------------------


};

#include "bst.hpp"

}//end of namespace cop4530
#endif
