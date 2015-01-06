/*
����������� ���������
���-12
6_1. ������.
������� ��� ������ �� ���������� �������. � ������� ����� ������ ������ �����. ������� ����� ������� �� ����� K �����. ������ ����� ����� �� ����� K �����. �� ��� �� �������� ��������� ����� ������� �������, ������� ����� ������� ������������, ���������� �� ������� �������� � ������ ������� ������� � �������. ���� ����� ����� �������� ����� �����, �� ���������� ������� ��������. ����� ����� 1�� �� ������� ���������.
���������� �� ������� �������� ������� ����� ��� ������ � �������.
*/
#include <iostream>
#include <assert.h>

using namespace std;

class CArray
{
public:
	CArray(int _bufferSize): realSize(0), bufferSize(_bufferSize) { buffer = new int[_bufferSize]; }
	~CArray() { delete[] buffer; }
	int Size() { return realSize; }
	int GetAt(int index);
	void SetAt(int index, int el);
	int operator[]( int index ) { return GetAt( index ); }
	void swap(int index1, int index2);
	void Add(int el);
	int Last() { return buffer[realSize-1]; }
	void DeleteLast() { realSize--; }
	bool IsEmpty() { return realSize == 0; }
private:
	CArray();
	int* buffer;
	int bufferSize;
	int realSize;
};

class CStack
{
public:
	CStack(int _bufferSize): bufferSize(_bufferSize), now(0) { buffer = new int[_bufferSize]; }
	~CStack() { delete buffer; }
	int pop();
	void push(int);
	bool IsEmpty() { return now==0; }
private:
	int* buffer;
	int bufferSize;
	int now;
};

void BuildHeap(CArray& arr, int i);
void SiftDown(CArray& arr, int i);
void SiftUp(CArray& arr, int i);
int computeCount(CArray& arr, int k);
int ExtractMax(CArray& arr);

int main()
{
	int n = 0;
	cin>>n;
	CArray apples(n);
	int value = 0;
	for(int i = 0; i < n; i++) {
		cin>>value;
		apples.Add(value);
	}
	BuildHeap(apples, 0);

	int k = 0;
	cin>>k;

	int count = computeCount(apples, k);
	cout<<count;

	return 0;
}

int CArray::GetAt(int index)
{
	assert(index < bufferSize);
	return buffer[index];
}

void CArray::SetAt(int index, int el)
{
	assert(index < bufferSize);
	buffer[index] = el;
}

void CArray::Add(int el)
{
	assert(realSize < bufferSize);
	buffer[realSize++] = el;
}

void SiftDown(CArray& arr, int i)
{
	int left = 2 * i + 1;
    int right = 2 * i + 2;
    // ���� �������� ����, ���� ����� ����.
    int largest = i;
    if( left < arr.Size() && arr[left] > arr[i] )
        largest = left;
    if( right < arr.Size() && arr[right] > arr[largest] )
        largest = right;
    // ���� ������� ��� ����, �� ������������ ������ � ����.
    if( largest != i ) {
        arr.swap( i, largest );
        SiftDown( arr, largest );
    }

}

void SiftUp(CArray& arr, int i)
{
	while(i > 0) {
		int parent = (i - 1) / 2;
		if(arr[i] <= arr[parent])
			return;
		int temp = arr[i];
		arr.SetAt(i, arr[parent]);
		arr.SetAt(parent, temp);
		i = parent;
	}
}

void CArray::swap(int index1, int index2)
{
	int temp = buffer[index1];
	buffer[index1] = buffer[index2];
	buffer[index2] = temp;
}

int CStack::pop()
{
	assert(now > 0);
	return buffer[--now];
}

void CStack::push(int el)
{
	assert(now < bufferSize);
	buffer[now++] = el;
}

void BuildHeap(CArray& arr, int i)
{
	for(int i = arr.Size() / 2 - 1; i >= 0; --i) {
		SiftDown(arr, i);
	}
}

int computeCount(CArray& arr, int k)
{
	CStack stack(arr.Size());
	int j = 0; //���-�� ��������
	while(arr[0] != 0) {
		int curr = 0;
		while(curr != k) {
			if(arr.IsEmpty()) break;
			int now = ExtractMax(arr);
			if(curr + now <= k) {
				stack.push(now/2);
				curr += now;
			} else {
				stack.push(now);
				break;
			}
		}
		//������� �� ����� ������� � ����
		while(!stack.IsEmpty()) {
			arr.Add(stack.pop());
			SiftUp(arr, arr.Size()-1);
		}
		j++;
	}
	return j;
}

int ExtractMax(CArray& arr)
{
	assert(!arr.IsEmpty());
	int max = arr[0];
	arr.SetAt(0, arr.Last());
	arr.DeleteLast();
	if(!arr.IsEmpty()) {
		SiftDown(arr, 0);
	}
	return max;
}