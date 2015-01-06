#include <iostream>
#include <assert.h>

using namespace std;


class CArray {
public:
	CArray(int n) : bufferSize( n ), realSize( 0 ) { buffer = new int[n]; }
	~CArray() { delete[] buffer; }
	// Доступ по индексу.
	int GetAt( int index ) const;
	void SetAt( int index, int el );
	int operator[]( int index ) const { return GetAt( index ); }
	//int& operator[]( int index ) {  }
	// Добавление нового элемента.
	void Add( int element );
private:
	int* buffer; // Буфер.
	int bufferSize; // Размер буфера.
	int realSize; // Количество элементов в массиве.
	void grow();
	CArray();
};

class CStack {
public:
	CStack( int _bufferSize );
	~CStack();
	// Добавление и извлечение элемента из стека.
	void Push( int a );
	int Pop();
	// Проверка на пустоту.
	bool IsEmpty() const { return realSize == 0; }
private:
	CArray* buffer;
	int realSize;
	int bufferSize;
	CStack();
};

class CQueue {
public:
	CQueue(int size) : realSize(0) { stack1 = new CStack(size/2); stack2 = new CStack(size/2); }
	~CQueue() { delete stack1; delete stack2; }
	void Enqueue(int el);
	int Dequeue();
private:
	CStack* stack1;
	CStack* stack2;
	int realSize;
	CQueue();
};

int main()
{
	//кол-во операций
	int count = 0;
	cin>>count;
	CQueue queue(count);
	for(int i = 0; i < count; i++) {
		int command = 0;
		cin>>command;
		int res = 0;
		cin>>res;
		if(command == 2) {
			if(!(res == queue.Dequeue())) {
				cout<<"NO";
				return 0;
			}
		} else if(command == 3) {
			queue.Enqueue(res);
		}
	}
	cout<<"YES";
	return 0;
}


// Доступ к элементу.
int CArray::GetAt( int index ) const
{
	assert( index >= 0 && index < realSize && buffer != 0 );
	return buffer[index];
}

void CArray::SetAt( int index, int el )
{
	assert( index >= 0 && buffer != 0 && index < realSize );
	buffer[index] = el;
	realSize++;
}

// Увеличение буфера.
void CArray::grow()
{
	int newBufferSize = bufferSize * 2;
	int* newBuffer = new int[newBufferSize];
	for( int i = 0; i < realSize; ++i )
		newBuffer[i] = buffer[i];
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}

// Добавление элемента.
void CArray::Add( int element )
{
	if( realSize == bufferSize )
		grow();
	assert( realSize < bufferSize && buffer != 0 );
	buffer[realSize++] = element;
}



/////////////////////////////////////////
// В конструкторе создаем буфер.
CStack::CStack( int _bufferSize ) :
bufferSize( _bufferSize ),
realSize( 0 )
{
	buffer = new CArray(_bufferSize);
}

// В деструкторе удаляем буфер.
CStack::~CStack()
{
	delete buffer;
}

// Добавление элемента.
void CStack::Push( int a )
{
	buffer->Add(a);
	realSize++;
}

// Извлечение элемента.
int CStack::Pop()
{
	if( realSize == 0 ) {
		return -1;
	}
	return buffer->GetAt(--realSize);
}

////////////////////////////

void CQueue::Enqueue(int el)
{
	stack1->Push(el);
}

int CQueue::Dequeue()
{
	if(stack2->IsEmpty()) {
		//переносим все из первого во второй
		while(!stack1->IsEmpty()) {
			int temp = stack1->Pop();
			stack2->Push(temp);
		}
	}
	return stack2->Pop();
}