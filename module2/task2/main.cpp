#include <iostream>
#include <assert.h>

using namespace std;

class Box
{
public:
	Box(): X(0), Y(0), Z(0), position(0) {}
	Box(int x, int y, int z, int pos);
	~Box() {}
	void SetCoords(int x, int y, int z);
	friend bool operator< (Box&, Box&);
	int getPos() { return position; }
private:
	int X;
	int Y;
	int Z;
	int position;
	void sortCoord();
};

template <class T>
class Heap
{
public:
	Heap(int _bufferSize): bufferSize(_bufferSize), realSize(0) { buffer = new T[_bufferSize]; }
	~Heap() { delete[] buffer; }
	void buildHeap();
	void SiftDown(int);
	void SiftUp(int);
	T ExtractMin();
	void Add(T);
	bool IsEmpty() { return realSize == 0; }
private:
	Heap();
	void swap(int index1, int index2);
	T* buffer;
	int bufferSize;
	int realSize;
};

template <class T>
void heapSort(Heap<T>& arr, T* toArray);


int main()
{
	int n = 0;
	cin >> n;
	int x = 0, y = 0, z = 0;
	Heap<Box> heap(n);
	for(int i = 0; i < n; i++) {
		cin >> x >> y >> z;
		Box box(x, y, z, i);
		heap.Add(box);
	}
	Box* result = new Box[n];
	heapSort(heap, result);

	for(int i = 0; i < n; i++) {
		cout << result[i].getPos() << " ";
	}
	return 0;
}

Box::Box(int x, int y, int z, int pos): X(x), Y(y), Z(z), position(pos)
{
	//сразу сортируем по осям
	sortCoord();
}

void Box::sortCoord()
{
	if(Y < X) swap(X, Y);
	if(Z < Y) swap(Z, Y);
	if(Y < X) swap(X, Y);
}

void Box::SetCoords(int x, int y, int z)
{
	X = x;
	Y = y;
	Z = z;
	sortCoord();
}

bool operator< (Box& box1, Box& box2)
{
	return (box1.X < box2.X && box1.Y < box2.Y && box1.Z < box2.Z) ? true: false;
}

template <class T>
void Heap<T>::SiftDown(int i)
{
	int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    if( left < realSize && buffer[left] < buffer[i] )
        smallest = left;
    if( right < realSize && buffer[right] < buffer[smallest] )
        smallest = right;
    // Если больший сын есть, то проталкиваем корень в него.
    if( smallest != i ) {
        swap( i, smallest );
        SiftDown( smallest );
    }
}

template <class T>
void Heap<T>::swap(int index1, int index2)
{
	assert(index1 < realSize && index2 < realSize);
	T temp = buffer[index1];
	buffer[index1] = buffer[index2];
	buffer[index2] = temp;
}

template <class T>
void Heap<T>::SiftUp(int i)
{
	while(i > 0) {
		int parent = (i - 1) / 2;
		if(buffer[parent] < buffer[i])
			return;
		swap(i, parent);
		i = parent;
	}
}

template <class T>
T Heap<T>::ExtractMin()
{
	assert(realSize > 0);
	T min = buffer[0];
	buffer[0] = buffer[realSize-1];
	realSize--;
	if(realSize != 0) {
		SiftDown(0);
	}
	return min;
}

template <class T>
void Heap<T>::buildHeap()
{
	for(int i = realSize / 2 - 1; i >= 0; --i) {
		SiftDown(i);
	}
}

template <class T>
void Heap<T>::Add(T el)
{
	assert(realSize < bufferSize);
	buffer[realSize++] = el;
	SiftUp(realSize-1);
}

template <class T>
void heapSort(Heap<T>& arr, T* toArray)
{
	int i = 0;
	while(!arr.IsEmpty()) {
		toArray[i++] = arr.ExtractMin();
	}
}