/*
Лукьянченко Александр
АПО-12
6_1. Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
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
    // Ищем большего сына, если такой есть.
    int largest = i;
    if( left < arr.Size() && arr[left] > arr[i] )
        largest = left;
    if( right < arr.Size() && arr[right] > arr[largest] )
        largest = right;
    // Если больший сын есть, то проталкиваем корень в него.
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
	int j = 0; //кол-во подходов
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
		//заносим из стека обратно в кучу
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