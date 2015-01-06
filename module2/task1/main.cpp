#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
class CArray
{
public:
	CArray(): realSize(0), bufferSize(startSize) { buffer = new T[startSize]; }
	~CArray() { delete[] buffer; }
	void Add(T el);
	T Size() { return realSize; }
	T& operator[] (int index) { assert(index < realSize); return buffer[index]; }
private:
	T* buffer;
	int realSize;
	int bufferSize;
	static const int startSize = 10; 
	void grow();
};

template <class T>
void Selection(CArray<T>& arr, int left, int right)
{
	for (int i = left; i < right - 1; i++) {
        int min = i;
 
        for(int j = i + 1; j < right; j++) {
            if(arr[j] < arr[min])
                min = j;
        }
        if(min != i)
            swap(arr[i], arr[min]);
    }
}

int main()
{
	CArray<int> arr;
	while(true) {
		int number = 0;
		cin >> number;
		if(cin.fail() == true) {
			break;
		}
		arr.Add(number);
	}

	Selection(arr, 0, arr.Size());

	for(int i = 0; i < arr.Size(); i++) {
		cout << arr[i] << " ";
	}
	
	return 0;
}

template <class T>
void CArray<T>::Add(T el)
{
	if(realSize == bufferSize) {
		grow();
	}
	
	buffer[realSize++] = el;
}

template <class T>
void CArray<T>::grow()
{
	int newBufferSize = bufferSize * 2;
	int* newBuffer = new int[newBufferSize];
	for(int i = 0; i < bufferSize; i++) {
		newBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}