#include <iostream>
#include <fstream>
#include <set>
//#include "heap.cpp"
#include "nodeHeap.cpp"

using namespace std;

int main(int argc, char *argv[]){
	unsigned char ch;
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
	cout<<myHeap->size()<<endl;
	myHeap->print();
	myHeap->deletemin();
	myHeap->print();
	for (int i=0;i<myHeap->size();i++){
		//cout << myHeap->minfreq()<< endl;
		//myHeap->deletemin();
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