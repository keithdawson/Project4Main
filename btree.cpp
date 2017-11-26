//
// Created by blakemizzell on 11/26/2017.
//
#include <iostream>
using namespace std;

typedef struct treeNode{
	int treeFreq;
	int treeVal;
	int treeCode;
	treeNode *leftTree;
	treeNode *rightTree;
};

class btree
{
public:
	btree();
	~btree();

	void insert(int freq, int val);
	//node *search(int key);
	void destroy_tree();

private:
	void destroy_tree(treeNode *leaf);
	void insert(int key, treeNode *leaf);
	//node *search(int key, node *leaf);

	treeNode *root;
};

btree::btree()
{
	root=NULL;
}

void btree::destroy_tree(treeNode *leaf)
{
	if(leaf!=NULL)
	{
		destroy_tree(leaf->leftTree);
		destroy_tree(leaf->rightTree);
		delete leaf;
	}
}