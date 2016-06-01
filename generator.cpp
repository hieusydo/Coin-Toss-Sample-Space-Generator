/*
Hieu Do
Coin Toss Sample Space Generator
*/

#include <iostream>
#include <math.h> 
using namespace std;

// define a node of a binary tree
typedef struct BinaryTreeNode {
	BinaryTreeNode(int intData, BinaryTreeNode* leftChild = nullptr, BinaryTreeNode* rightChild = nullptr) : data(intData), left(leftChild), right(rightChild) {}
	BinaryTreeNode* left; 
	BinaryTreeNode* right;
	int data;
}BTNode;

// generate a tree representing all posible combinations of heads and tails 
BinaryTreeNode* generateTree(BinaryTreeNode* root, int value, int height);

/*
Reference: geeksforgeeks.org/given-a-binary-tree-print-all-root-to-leaf-paths/
*/
// routine function for printPaths
void printArray(int ints[], int len);
// recursive driver function for printPaths
void printPathsRecur(BTNode* node, int path[], int pathLen);
// print out the entire sample space
void printPaths(BTNode* node);

/*
Specific to the problem: how many times does 
at least two heads in a row show up? 
*/
// condition check
bool checkArray(int ints[], int len);

// recursive driver function for find2HeadInARow
void find2HeadInARowRecur(BTNode* node, int path[], int pathLen, int& consec);

// find the number of occurences of having at least two heads in a row
int find2HeadInARow(BTNode* node);

// print the probability 
void getProb(BTNode* node, int numToss);

/*
main
*/
int main() {
	int numToss = 20;
	BinaryTreeNode* root = generateTree(new BinaryTreeNode(-1), -1, numToss+1);
	// printPaths(root);
	getProb(root, numToss);
	return 0;
}

BinaryTreeNode* generateTree(BinaryTreeNode* root, int value, int height) {
	if (height == 0) return nullptr;
	--height;	
	root = new BTNode(value);
	root->left = generateTree(root->left, 0, height);
	root->right = generateTree(root->right, 1, height);
	return root;
}

void printArray(int ints[], int len) {
	for (int i = 1; i < len; ++i) {
		cout << (ints[i] ? 'H' : 'T');		
	}
	cout << endl;
}

void printPathsRecur(BTNode* node, int path[], int pathLen) {
	if (!node) return;

	path[pathLen] = node->data;
	pathLen++;

	if (!node->left && !node->right) printArray(path, pathLen);
	else {
		printPathsRecur(node->left, path, pathLen);
		printPathsRecur(node->right, path, pathLen);
	}
}

void printPaths(BTNode* node) {
	int path[1000];
	printPathsRecur(node, path, 0);
}

bool checkArray(int ints[], int len) {
	for (int i = 1; i < len; ++i) {
		// if at least two heads in a row occurs, return true
		if (((i+1) < len) && ints[i] && ints[i+1]) {
			return true;
		}
	}
	return false;
}

void find2HeadInARowRecur(BTNode* node, int path[], int pathLen, int& consec) {
	if (!node) return;

	path[pathLen] = node->data;
	pathLen++;

	if (!node->left && !node->right) {
		if (checkArray(path, pathLen)) ++consec;
	}
	else {
		find2HeadInARowRecur(node->left, path, pathLen, consec);
		find2HeadInARowRecur(node->right, path, pathLen, consec);
	}
}

int find2HeadInARow(BTNode* node) {
	int path[1000];
	int consec = 0;
	find2HeadInARowRecur(node, path, 0, consec);
	return consec;
}

void getProb(BTNode* node, int numToss) {
	cout << "Probability of having at least two heads in a row when tossing " << numToss << " coins\n= "  
		<< find2HeadInARow(node) << "/" << pow(2, numToss) << " = " << find2HeadInARow(node)/pow(2, numToss) << endl;
}