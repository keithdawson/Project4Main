#include <iostream>
#include <fstream>
#include <set>
//#include "heap.cpp"
#include "nodeHeap.cpp"
//#include "btree.cpp"

using namespace std;
void printInorder(int index);
void printPreorder(int index);
void coutInorder(int index);
void coutPreorder(int index);
treeNode treeNodeArray[128];
ofstream infile;
ofstream prefile;

int main(int argc, char *argv[]){
	unsigned char ch;
	int countUp = 128;
	ifstream in(argv[1],ios::in|ios::binary|ios::ate);
	size_t size = 0; // here
	size = in.tellg() ; // get the length of the file
	cout << "Size of file: " << size << endl;
	int* fileArray;
	fileArray = new int[size];
	in.seekg(0, ios::beg); // set the pointer to the beginning
	for (int i =0; i<size; i++) {
		ch = in.get();
		fileArray[i] = ch;
	}
	int asciiArray[128];
	for (int i=0; i<128;i++){
		asciiArray[i]=0;
	}
	for (int i=0; i<size;i++){
		asciiArray[fileArray[i]]++;
	}
	Heap* myHeap = new Heap();
	for (int i=0;i<128;i++){
		if (asciiArray[i]!=0){
			myHeap->insert(asciiArray[i], i);
		}
	}

	for (int i =0; i<128;i++){
		treeNodeArray[i].treeFreq = NULL;
		treeNodeArray[i].treeVal = NULL;
		treeNodeArray[i].treeCode = NULL;
		treeNodeArray[i].leftTree = NULL;
		treeNodeArray[i].rightTree = NULL;
	}
	treeNode leafLeft, leafRight, parent;
	leafLeft.treeVal = myHeap->minval();
	leafLeft.treeFreq = myHeap->deletemin();
	treeNodeArray[leafLeft.treeVal].treeVal = leafLeft.treeVal;
	treeNodeArray[leafLeft.treeVal].treeFreq = leafLeft.treeFreq;
	treeNodeArray[leafLeft.treeVal].leftTree = NULL;
	treeNodeArray[leafLeft.treeVal].rightTree = NULL;
	leafRight.treeVal = myHeap->minval();
	leafRight.treeFreq = myHeap->deletemin();
	treeNodeArray[leafRight.treeVal].treeVal = leafRight.treeVal;
	treeNodeArray[leafRight.treeVal].treeFreq = leafRight.treeFreq;
	treeNodeArray[leafRight.treeVal].leftTree = NULL;
	treeNodeArray[leafRight.treeVal].rightTree = NULL;
	parent.treeVal = countUp;
	countUp++;
	parent.treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
	parent.leftTree = leafLeft.treeVal;
	parent.rightTree = leafRight.treeVal;
	treeNodeArray[parent.treeVal-128].treeVal = parent.treeVal;
	treeNodeArray[parent.treeVal-128].treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
	treeNodeArray[parent.treeVal-128].leftTree = leafLeft.treeVal;
	treeNodeArray[parent.treeVal-128].rightTree = leafRight.treeVal;
	myHeap->insert(parent.treeFreq, parent.treeVal);
	while(myHeap->size() != 1) {

		treeNode leafLeft, leafRight;
		leafLeft.treeVal = myHeap->minval();
		leafLeft.treeFreq = myHeap->deletemin();
		leafRight.treeVal = myHeap->minval();
		leafRight.treeFreq = myHeap->deletemin();
		if (leafLeft.treeVal < 128 && leafRight.treeVal < 128) {
			treeNode parent;
			treeNodeArray[leafLeft.treeVal].treeVal = leafLeft.treeVal;
			treeNodeArray[leafLeft.treeVal].treeFreq = leafLeft.treeFreq;
			treeNodeArray[leafLeft.treeVal].leftTree = NULL;
			treeNodeArray[leafLeft.treeVal].rightTree = NULL;
			treeNodeArray[leafRight.treeVal].treeVal = leafRight.treeVal;
			treeNodeArray[leafRight.treeVal].treeFreq = leafRight.treeFreq;
			treeNodeArray[leafRight.treeVal].leftTree = NULL;
			treeNodeArray[leafRight.treeVal].rightTree = NULL;
			parent.treeVal = countUp;
			countUp++;
			parent.treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			parent.leftTree = leafLeft.treeVal;
			parent.rightTree = leafRight.treeVal;
			treeNodeArray[parent.treeVal - 128].treeVal = parent.treeVal;
			treeNodeArray[parent.treeVal - 128].treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			treeNodeArray[parent.treeVal - 128].leftTree = leafLeft.treeVal;
			treeNodeArray[parent.treeVal - 128].rightTree = leafRight.treeVal;
			myHeap->insert(parent.treeFreq, parent.treeVal);

		}
		else if (leafLeft.treeVal >= 128 && leafRight.treeVal < 128) {
			treeNode tempLeaf, parent;
			tempLeaf.treeVal = leafRight.treeVal;
			tempLeaf.treeFreq = leafLeft.treeFreq;
			leafRight.treeVal = leafLeft.treeVal;
			leafRight.treeFreq = leafLeft.treeFreq;
			leafLeft.treeVal = tempLeaf.treeVal;
			leafLeft.treeFreq = tempLeaf.treeFreq;
			treeNodeArray[leafLeft.treeVal].treeVal = leafLeft.treeVal;
			treeNodeArray[leafLeft.treeVal].treeFreq = leafLeft.treeFreq;
			treeNodeArray[leafLeft.treeVal].leftTree = NULL;
			treeNodeArray[leafLeft.treeVal].rightTree = NULL;
			parent.treeVal = countUp;
			countUp++;
			parent.treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			parent.leftTree = leafLeft.treeVal;
			parent.rightTree = leafRight.treeVal;
			treeNodeArray[parent.treeVal - 128].treeVal = parent.treeVal;
			treeNodeArray[parent.treeVal - 128].treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			treeNodeArray[parent.treeVal - 128].leftTree = leafLeft.treeVal;
			treeNodeArray[parent.treeVal - 128].rightTree = leafRight.treeVal - 128;
			myHeap->insert(parent.treeFreq, parent.treeVal);

		}
		else if (leafLeft.treeVal < 128 && leafRight.treeVal >= 128) {
			treeNode parent;
			treeNodeArray[leafLeft.treeVal].treeVal = leafLeft.treeVal;
			treeNodeArray[leafLeft.treeVal].treeFreq = leafLeft.treeFreq;
			treeNodeArray[leafLeft.treeVal].leftTree = NULL;
			treeNodeArray[leafLeft.treeVal].rightTree = NULL;
			parent.treeVal = countUp;
			countUp++;
			parent.treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			parent.leftTree = leafLeft.treeVal;
			parent.rightTree = leafRight.treeVal;
			treeNodeArray[parent.treeVal - 128].treeVal = parent.treeVal;
			treeNodeArray[parent.treeVal - 128].treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			treeNodeArray[parent.treeVal - 128].leftTree = leafLeft.treeVal;
			treeNodeArray[parent.treeVal - 128].rightTree = leafRight.treeVal-128;
			myHeap->insert(parent.treeFreq, parent.treeVal);

		}
		else if (leafLeft.treeVal >= 128 && leafRight.treeVal >= 128) {
			treeNode parent;
			parent.treeVal = countUp;
			countUp++;
			parent.treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			parent.leftTree = leafLeft.treeVal;
			parent.rightTree = leafRight.treeVal;
			treeNodeArray[parent.treeVal - 128].treeVal = parent.treeVal;
			treeNodeArray[parent.treeVal - 128].treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			treeNodeArray[parent.treeVal - 128].leftTree = leafLeft.treeVal-128;
			treeNodeArray[parent.treeVal - 128].rightTree = leafRight.treeVal-128;
			myHeap->insert(parent.treeFreq, parent.treeVal);
		}
	}
	int rootIndex = countUp-129;
	infile.open("inorder.txt");
	prefile.open("preorder.txt");
	//coutInorder(rootIndex);
	//coutPreorder(rootIndex);
	printInorder(rootIndex);
	printPreorder(rootIndex);

	/*for (int i =0; i<128;i++){
		cout << treeNodeArray[i].treeFreq << ' ';
		cout << treeNodeArray[i].treeVal << ' ';
		//treeNodeArray[i].treeCode ;
		cout << treeNodeArray[i].leftTree << ' ';
		cout << treeNodeArray[i].rightTree << endl;
	}*/
	int leftDepth, rightdepth;
 }
void coutInorder(int index)
{
	if (treeNodeArray[index].leftTree == NULL && treeNodeArray[index].rightTree == NULL) {
		cout << (treeNodeArray[index].treeVal) << endl;
		return;
	}

	if(treeNodeArray[index].leftTree != NULL) coutInorder(treeNodeArray[index].leftTree);

	cout << (treeNodeArray[index].treeVal) << endl;

	if(treeNodeArray[index].rightTree != NULL) coutInorder(treeNodeArray[index].rightTree);
}
void coutPreorder(int index)
{
	if (treeNodeArray[index].leftTree == NULL && treeNodeArray[index].rightTree == NULL){
		cout << (treeNodeArray[index].treeVal) << endl;
		return;
	}
	cout << (treeNodeArray[index].treeVal) << endl;

	if(treeNodeArray[index].leftTree != NULL) coutPreorder(treeNodeArray[index].leftTree);

	if(treeNodeArray[index].rightTree != NULL) coutPreorder(treeNodeArray[index].rightTree);
}
void printInorder(int index)
{
	if (treeNodeArray[index].leftTree == NULL && treeNodeArray[index].rightTree == NULL) {
		infile.put(treeNodeArray[index].treeVal);
		return;
	}

	if(treeNodeArray[index].leftTree != NULL) printInorder(treeNodeArray[index].leftTree);

	infile.put(treeNodeArray[index].treeVal);

	if(treeNodeArray[index].rightTree != NULL) printInorder(treeNodeArray[index].rightTree);
}

void printPreorder(int index)
{
	if (treeNodeArray[index].leftTree == NULL && treeNodeArray[index].rightTree == NULL){
		prefile.put(treeNodeArray[index].treeVal);
		return;
	}
	prefile.put(treeNodeArray[index].treeVal);

	if(treeNodeArray[index].leftTree != NULL) printPreorder(treeNodeArray[index].leftTree);

	if(treeNodeArray[index].rightTree != NULL) printPreorder(treeNodeArray[index].rightTree);
}