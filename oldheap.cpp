//This is the Heap program by Blake Mizzell

#include <vector>

using namespace std;

typedef struct node {
	int freq;
	int val;
};

class MyDynamicArray {
private:
	int size, limit, error;
	node *a;
public:
	MyDynamicArray() {
		a = new node[limit = 2];
		size = error = 0;
	}
	MyDynamicArray(int s) {
		a = new node[limit = size = s];
		error = 0;
	}
	~MyDynamicArray() {
		delete a;
	}
	int& operator[](node i){
		if (i>=size || i < 0) {return error;}
		return *(a+i);
	}
	void add(int v) {
		if(size == limit) {
			int *temp = new int[limit *= 2];
			//cout << "Doubling to : " << limit << endl;
			for (int i = 0; i<size; i++)  temp[i]=a[i];
			delete a;
			a = temp;
		}
		a[size++] = v;
	}
	void del() {
		size--;
		if (size <= limit/4) {
			node *temp = new node[limit /= 2];
			//cout << "Reducing to : "<< limit << endl;
			for (int i = 0; i<size; i++)  temp[i]=a[i];
			delete a;
			a = temp;
		}
	}
	int length() { return size;}
	void clear() {
		delete a;
		a = new node[limit=2];
		size = 0;
	}
};

class Heap
{
private:
	void BubbleDownMin(int index);
	void BubbleUpMin(int index);
	void BubbleDownMax(int index);
	void BubbleUpMax(int index);
	void minHeapify();
	//void maxHeapify();
	MyDynamicArray dynA;
	int maxormin = 1; //min = 1 max = 0
public:
	Heap(node a[], int, string);
	Heap(node a[], int);
	Heap();

	//void insert(int newValue);
	int extract();
	void out();
};


Heap::Heap(node* array, int length)
{
	for (int i = 0; i < length; i++) dynA.add(array[i]);
	minHeapify();
}

Heap::Heap(node* array, int length, string s)
{
	std::string str(s);
	if (str.compare("max") == 0){
		for(int i = 0; i < length; ++i)
		{
			dynA.add(array[i]);
		}
		maxHeapify();
	}
	else {
		for(int i = 0; i < length; ++i)
		{
			dynA.add(array[i]);
		}
		minHeapify();
	}
}

Heap::Heap()
{
}

void Heap::minHeapify()
{
	int length = dynA.length();
	for(int i=length-1; i>=0; --i)
	{
		BubbleDownMin(i);
	}
}

/*void Heap::maxHeapify()
{
	int length = dynA.length();
	maxormin = 0;
	for(int i=length-1; i>=0; --i)
	{
		BubbleDownMax(i);
	}
}*/

void Heap::BubbleDownMin(int index)
{
	int length = dynA.length();
	int leftChildIndex = 2*index + 1;
	int rightChildIndex = 2*index + 2;

	if(leftChildIndex >= length)
		return; //index is a leaf

	int minIndex = index;

	if(dynA[index].val > dynA[leftChildIndex].val)
	{
		minIndex = leftChildIndex;
	}

	if((rightChildIndex < length) && (dynA[minIndex].val > dynA[rightChildIndex].val))
	{
		minIndex = rightChildIndex;
	}

	if(minIndex != index)
	{
		//need to swap
		int temp = dynA[index].val;
		dynA[index].val = dynA[minIndex].val;
		dynA[minIndex].val = temp;
		BubbleDownMin(minIndex);
	}
}
/*
void Heap::BubbleDownMax(int index)
{
	int length = dynA.length();
	int leftChildIndex = 2*index + 1;
	int rightChildIndex = 2*index + 2;

	if(leftChildIndex >= length)
		return; //index is a leaf

	int minIndex = index;

	if(dynA[index] < dynA[leftChildIndex])
	{
		minIndex = leftChildIndex;
	}

	if((rightChildIndex < length) && (dynA[minIndex] < dynA[rightChildIndex]))
	{
		minIndex = rightChildIndex;
	}

	if(minIndex != index)
	{
		//need to swap
		int temp = dynA[index];
		dynA[index] = dynA[minIndex];
		dynA[minIndex] = temp;
		BubbleDownMin(minIndex);
	}
}


void Heap::BubbleUpMax(int index)
{
	if(index == 0)
		return;

	int parentIndex = (index-1)/2;

	if(dynA[parentIndex] < dynA[index])
	{
		int temp = dynA[parentIndex];
		dynA[parentIndex] = dynA[index];
		dynA[index] = temp;
		BubbleUpMin(parentIndex);
	}
}
*/
void Heap::BubbleUpMin(int index)
{
	if(index == 0)
		return;

	int parentIndex = (index-1)/2;

	if(dynA[parentIndex].val > dynA[index].val)
	{
		int temp = dynA[parentIndex].val;
		dynA[parentIndex].val = dynA[index].val;
		dynA[index].val = temp;
		BubbleUpMin(parentIndex);
	}
}
/*
void Heap::insert(int newValue)
{
	int length = dynA.length();
	dynA.add(newValue);

	if (maxormin == 1) {
		BubbleUpMin(length);
	}
	else BubbleUpMax(length);
}
*/
void Heap::out(){
	for (int i=0; i < dynA.length(); i++) {
		cout<<dynA[i]<<' ';
	}
	cout<<endl;
}

int Heap::extract()
{
	int length = dynA.length();
	int returner = dynA[0];
	if(length == 0)
	{
		return 0;
	}

	dynA[0] = dynA[length-1];
	if (maxormin == 1){
		dynA.del();
		BubbleDownMin(0);
	}
	else {
		dynA.del();
		BubbleDownMax(0);
	}
	return returner;
}
