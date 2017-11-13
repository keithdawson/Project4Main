//Binary Search Tree Program by Blake Mizzell

#include <iostream>
#include <cstdlib>
using namespace std;

struct bstNode
{
	bstNode* left;
	bstNode* right;
	int data;
	int freq;
};

class BST
{
private:
	bstNode* sortedArrayToBST(int a[], int, int);
	bstNode* root = new bstNode;
	bstNode* newNode(int);
	bool isEmpty() const { return root==NULL; }
	void inorderTrav(bstNode*);
	void preorderTrav(bstNode*);
	void postorderTrav(bstNode*);
public:
	BST()
	{
		root = NULL;
	}
	BST(int a[], int);
	void inorder();
	void inorder(bstNode*);
	void preorder();
	void preorder(bstNode*);
	void postorder();
	void postorder(bstNode*);
	void insert(int);
	bool remove (int);
	bool remove(int, char);
	bstNode * search(int);
};

bstNode * BST::newNode(int data) {
	bstNode * tNode = new bstNode;
	tNode->data = data;
	tNode->left = NULL;
	tNode->right = NULL;
	return tNode;
}

bstNode * BST::sortedArrayToBST(int a[], int start, int end){
	if (start > end)
		return NULL;
	int mid = (start + end + 1) / 2;
	bstNode * localRoot = newNode(a[mid]);
	localRoot->left = sortedArrayToBST(a, start, mid-1);
	localRoot->right = sortedArrayToBST(a, mid+1, end);
	return localRoot;
}

BST::BST(int a[], int len) {
	int start = 0;
	root = sortedArrayToBST(a, start, len-1);
}

void BST::insert(int d)
{
	bstNode* t = new bstNode;
	bstNode* parent;
	t->data = d;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;

	// is this a new tree?
	if(isEmpty()) root = t;
	else
	{
		//Note: ALL insertions are as leaf bstNodes
		bstNode* curr;
		curr = root;
		// Find the Node's parent
		while(curr)
		{
			parent = curr;
			if(t->data > curr->data) curr = curr->right;
			else curr = curr->left;
		}

		if(t->data < parent->data)
			parent->left = t;
		else
			parent->right = t;
	}
}

bool BST::remove(int d)
{
	char c = 'p';
	//Locate the element
	bool found = false;
	if(isEmpty())
	{
		cout<<" This Tree is empty! "<<endl;
		return NULL;
	}

	bstNode* curr;
	bstNode* parent;
	curr = root;

	while(curr != NULL)
	{
		if(curr->data == d)
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if(d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if(!found)
	{
		return false;
	}


	// 3 cases :
	// 1. We're removing a leaf bstNode
	// 2. We're removing a bstNode with a single child
	// 3. we're removing a bstNode with 2 children

	// Node with single child
	if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL
	                                                  && curr->right == NULL))
	{
		if(curr->left == NULL && curr->right != NULL)
		{
			if(parent->left == curr)
			{
				parent->left = curr->right;
				delete curr;
			}
			else
			{
				parent->right = curr->right;
				delete curr;
			}
		}
		else // left child present, no right child
		{
			if(parent->left == curr)
			{
				parent->left = curr->left;
				delete curr;
			}
			else
			{
				parent->right = curr->left;
				delete curr;
			}
		}
		return true;
	}

	//We're looking at a leaf bstNode
	if( curr->left == NULL && curr->right == NULL)
	{
		if(parent->left == curr) parent->left = NULL;
		else parent->right = NULL;
		delete curr;
		return true;
	}


	//Node with 2 children and c == p
	// replace bstNode with smallest value in left subtree

	if (curr->left != NULL && curr->right != NULL)
	{
		bstNode* chkl;
		chkl = curr->left;
		if((chkl->right == NULL) && (chkl->left == NULL))
		{
			curr = chkl;
			delete chkl;
			curr->left = NULL;
		}
		else // left child has children
		{
			//if the bstNode's left child has a right child
			// Move all the way down right to locate smallest element

			if((curr->left)->right != NULL)
			{
				bstNode* rcurr;
				bstNode* rcurrp;
				rcurrp = curr->left;
				rcurr = (curr->left)->right;
				while(rcurr->right != NULL)
				{
					rcurrp = rcurr;
					rcurr = rcurr->right;
				}
				curr->data = rcurr->data;
				if (rcurr->left != NULL) rcurrp->right = rcurr->left;
				else rcurrp->right = NULL;
				delete rcurr;
			}
			else
			{
				bstNode* tmp;
				tmp = curr->left;
				curr->data = tmp->data;
				curr->left = tmp->left;
				delete tmp;
			}

		}
		return true;
	}

}

bool BST::remove(int d, char c)
{
	//Locate the element
	bool found = false;
	if(isEmpty())
	{
		cout<<" This Tree is empty! "<<endl;
		return NULL;
	}

	bstNode* curr;
	bstNode* parent;
	curr = root;

	while(curr != NULL)
	{
		if(curr->data == d)
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if(d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if(!found)
	{
		return false;
	}


	// 3 cases :
	// 1. We're removing a leaf bstNode
	// 2. We're removing a bstNode with a single child
	// 3. we're removing a bstNode with 2 children

	// Node with single child
	if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL
	                                                  && curr->right == NULL))
	{
		if(curr->left == NULL && curr->right != NULL)
		{
			if(parent->left == curr)
			{
				parent->left = curr->right;
				delete curr;
			}
			else
			{
				parent->right = curr->right;
				delete curr;
			}
		}
		else // left child present, no right child
		{
			if(parent->left == curr)
			{
				parent->left = curr->left;
				delete curr;
			}
			else
			{
				parent->right = curr->left;
				delete curr;
			}
		}
		return true;
	}

	//We're looking at a leaf bstNode
	if( curr->left == NULL && curr->right == NULL)
	{
		if(parent->left == curr) parent->left = NULL;
		else parent->right = NULL;
		delete curr;
		return true;
	}


	//Node with 2 children and c == s
	// replace bstNode with smallest value in right subtree
	if (curr->left != NULL && curr->right != NULL && c == 's')
	{
		bstNode* chkr;
		chkr = curr->right;
		if((chkr->left == NULL) && (chkr->right == NULL))
		{
			curr = chkr;
			delete chkr;
			curr->right = NULL;
		}
		else // right child has children
		{
			//if the bstNode's right child has a left child
			// Move all the way down left to locate smallest element

			if((curr->right)->left != NULL)
			{
				bstNode* lcurr;
				bstNode* lcurrp;
				lcurrp = curr->right;
				lcurr = (curr->right)->left;
				while(lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				curr->data = lcurr->data;
				if (lcurr->right != NULL) lcurrp->left = lcurr->right;
				else lcurrp->left = NULL;
				delete lcurr;
			}
			else
			{
				bstNode* tmp;
				tmp = curr->right;
				curr->data = tmp->data;
				curr->right = tmp->right;
				delete tmp;
			}

		}
		return true;
	}
	if (curr->left != NULL && curr->right != NULL && c == 'p')
	{
		bstNode* chkl;
		chkl = curr->left;
		if((chkl->right == NULL) && (chkl->left == NULL))
		{
			curr = chkl;
			delete chkl;
			curr->left = NULL;
		}
		else // right child has children
		{
			//if the bstNode's right child has a left child
			// Move all the way down left to locate smallest element

			if((curr->left)->right != NULL)
			{
				bstNode* rcurr;
				bstNode* rcurrp;
				rcurrp = curr->left;
				rcurr = (curr->left)->right;
				while(rcurr->right != NULL)
				{
					rcurrp = rcurr;
					rcurr = rcurr->right;
				}
				curr->data = rcurr->data;
				if (rcurr->left != NULL) rcurrp->right = rcurr->left;
				else rcurrp->right = NULL;
				delete rcurr;
			}
			else
			{
				bstNode* tmp;
				tmp = curr->left;
				curr->data = tmp->data;
				curr->left = tmp->left;
				delete tmp;
			}

		}
		return true;
	}

}

bstNode* BST::search(int val){
	//Locate the element
	if(isEmpty())
	{
		cout<<" This Tree is empty! "<<endl;
		return NULL;
	}

	bstNode* curr;
	curr = root;

	while(curr != NULL)
	{
		if(curr->data == val)
		{
			return curr;
		}
		else
		{

			if(val>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
}

void BST::inorderTrav(bstNode* p)
{
	if(p != NULL)
	{
		if(p->left) inorderTrav(p->left);
		cout<<p->data<<" ";
		if(p->right) inorderTrav(p->right);
	}
	else return;
}

void BST::inorder()
{
	bstNode * p = root;
	if(p != NULL)
	{
		if(p->left) inorderTrav(p->left);
		cout<<p->data<<" ";
		if(p->right) inorderTrav(p->right);
	}
	cout<<endl;
	return;
}

void BST::inorder(bstNode* p)
{
	if(p != NULL)
	{
		if(p->left) inorderTrav(p->left);
		cout<<p->data<<" ";
		if(p->right) inorderTrav(p->right);
	}
	cout<<endl;
	return;
}

void BST::preorder()
{
	bstNode * p = root;
	if(p != NULL)
	{
		cout<<p->data<<" ";
		if(p->left) preorderTrav(p->left);
		if(p->right) preorderTrav(p->right);
	}
	cout<<endl;
	return;
}

void BST::preorderTrav(bstNode* p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
		if(p->left) preorderTrav(p->left);
		if(p->right) preorderTrav(p->right);
	}
	else return;
}

void BST::preorder(bstNode* p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
		if(p->left) preorderTrav(p->left);
		if(p->right) preorderTrav(p->right);
	}
	cout<<endl;
	return;
}

void BST::postorder()
{
	bstNode * p = root;
	if(p != NULL)
	{
		if(p->left) postorderTrav(p->left);
		if(p->right) postorderTrav(p->right);
		cout<<p->data<<" ";
	}
	cout<<endl;
	return;
}

void BST::postorderTrav(bstNode* p)
{
	if(p != NULL)
	{
		if(p->left) postorderTrav(p->left);
		if(p->right) postorderTrav(p->right);
		cout<<p->data<<" ";
	}
	else return;
}

void BST::postorder(bstNode* p)
{
	if(p != NULL)
	{
		if(p->left) postorderTrav(p->left);
		if(p->right) postorderTrav(p->right);
		cout<<p->data<<" ";
	}
	cout<<endl;
	return;
}