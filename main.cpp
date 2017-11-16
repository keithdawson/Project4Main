#include <iostream>
#include <fstream>
#include <set>
#include "heap.cpp"

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


	Heap* myheap = new Heap();
	for (int i;i<size;i++)	myheap->insert(fileArray[i]);
	myheap->print();

}