#include <iostream>
#include <fstream>
#include <set>
//#include "heap.cpp"
#include "nodeHeap.cpp"
//#include "btree.cpp"

using namespace std;


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
	treeNode treeNodeArray[128];
	cout<<myHeap->size()<<endl;
	myHeap->print();
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
	myHeap->print();
	while(myHeap->size() != 0) {
		if (myHeap->minval() < 128 && myHeap->minval2() < 128) {
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
			treeNodeArray[parent.treeVal - 128].treeVal = parent.treeVal;
			treeNodeArray[parent.treeVal - 128].treeFreq = leafLeft.treeFreq + leafRight.treeFreq;
			treeNodeArray[parent.treeVal - 128].leftTree = leafLeft.treeVal;
			treeNodeArray[parent.treeVal - 128].rightTree = leafRight.treeVal;
			myHeap->insert(parent.treeFreq, parent.treeVal);
		}
		else if (myHeap->minval() >= 128 && myHeap->minval2() < 128) {
			treeNode leafLeft, leafRight, parent;
			leafRight.treeVal = myHeap->minval();
			leafRight.treeFreq = myHeap->deletemin();
			leafLeft.treeVal = myHeap->minval();
			leafLeft.treeFreq = myHeap->deletemin();
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
		else if (myHeap->minval() < 128 && myHeap->minval2() >= 128) {
			treeNode leafLeft, leafRight, parent;
			leafLeft.treeVal = myHeap->minval();
			leafLeft.treeFreq = myHeap->deletemin();
			treeNodeArray[leafLeft.treeVal].treeVal = leafLeft.treeVal;
			treeNodeArray[leafLeft.treeVal].treeFreq = leafLeft.treeFreq;
			treeNodeArray[leafLeft.treeVal].leftTree = NULL;
			treeNodeArray[leafLeft.treeVal].rightTree = NULL;
			leafRight.treeVal = myHeap->minval();
			leafRight.treeFreq = myHeap->deletemin();
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
		else if (myHeap->minval() >= 128 && myHeap->minval2() >= 128) {
			treeNode leafLeft, leafRight, parent;
			leafLeft.treeVal = myHeap->minval();
			leafLeft.treeFreq = myHeap->deletemin();
			leafRight.treeVal = myHeap->minval();
			leafRight.treeFreq = myHeap->deletemin();
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
		myHeap->print();
	}


/*
	Heap* tempHeap = new Heap();
	for (int i;i<size;i++)	tempHeap->insert(fileArray[i]);
	tempHeap->print();
	int prevInt = tempHeap->deletemin();
	int insertInt = prevInt;
	Heap* myHeap = new Heap();
	myHeap->insert(insertInt);
	for (int i=1;i<size;i++){
		insertInt = tempHeap->deletemin();
		if (insertInt!=prevInt){
			myHeap->insert(insertInt);
		}
		prevInt = insertInt;
	}
	size = myHeap->size();
	myHeap->print();
*/
 }