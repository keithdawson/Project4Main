#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

struct node {
	int freq;
	int val;
};

typedef struct treeNode{
	int treeFreq;
	int treeVal;
	int treeCode;
	int leftTree;
	int rightTree;
};

class Heap {
public:
	Heap();
	~Heap();
	//Heap(int a[], int);
	//void increment(int value);
	void insert(int frequency, int value);
	int minfreq();
	int minval();
	int minval2();
	int deletemin();
	void print();
	int size() { return heap.size(); }
private:
	int left(int parent);
	int right(int parent);
	int parent(int child);
	void heapifyup(int index);
	void heapifydown(int index);
private:
	vector<node> heap;
};

Heap::Heap()
{
}
int Heap::minfreq() {
	return heap.front().freq;
}
int Heap::minval() {
	return heap.front().val;
}
int Heap::minval2() {
	return heap.at(1).val;
}
void Heap::insert(int frequency, int value)
{
	node element;
	element.freq = frequency;
	element.val = value;
	heap.push_back(element);
	heapifyup(heap.size() - 1);
}

int Heap::deletemin()
{
	int min = heap.front().freq;
	//print();
	heap[0].freq = heap.at(heap.size() - 1).freq;
	heap[0].val = heap.at(heap.size() - 1).val;
	heap.pop_back();
	//print();
	heapifydown(0);
	return min;
}

void Heap::print(){
	for (int i=0; i<heap.size();i++){
		cout<<heap[i].freq<< "  ";
	}
	cout<<endl;
	for (int i=0; i<heap.size();i++){
		cout<<heap[i].val<< ' ';
	}
	cout<<endl;
}
/*
void Heap::print()
{
	vector<int>::iterator pos = heap.begin();
	cout << "Heap = ";
	while ( pos != heap.end() ) {
		cout << *pos << " ";
		++pos;
	}
	cout << endl;
}
*/
void Heap::heapifyup(int index)
{
	while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
	        ( heap[parent(index)].freq > heap[index].freq ) )
	{
		int tmpFreq = heap[parent(index)].freq;
		int tmpVal = heap[parent(index)].val;
		heap[parent(index)].freq = heap[index].freq;
		heap[parent(index)].val = heap[index].val;
		heap[index].freq = tmpFreq;
		heap[index].val = tmpVal;
		index = parent(index);

	}
}

void Heap::heapifydown(int index)
{

	int child = left(index);
	//cout<<heap[child].freq<<" "<<heap[right(index)].freq << endl;
	if ( ( child > 0 ) && ( right(index) > 0 ) &&
	     ( heap[child].freq > heap[right(index)].freq ) )
	{
		//cout<<heap[child].freq<<" "<<heap[right(index)].freq << endl;
		child = right(index);
	}
	if ( heap[child].freq < heap[index].freq )
	{
		int tmpFreq = heap[index].freq;
		int tmpVal = heap[index].val;
		heap[index].freq = heap[child].freq;
		heap[index].val = heap[child].val;
		heap[child].val = tmpVal;
		heap[child].freq = tmpFreq;
		heapifydown(child);
	}
	else return;
}

int Heap::left(int parent)
{
	int i = ( parent << 1 ) + 1; // 2 * parent + 1
	return ( i < heap.size() ) ? i : -1;
}

int Heap::right(int parent)
{
	int i = ( parent << 1 ) + 2; // 2 * parent + 2
	return ( i < heap.size() ) ? i : -1;
}

int Heap::parent(int child)
{
	if (child != 0)
	{
		int i = (child - 1) >> 1;
		return i;
	}
	return -1;
}
