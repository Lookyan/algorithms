/*
����������� ���������
���-12
5_2. �������� ���������.
���� ���� ���������� �������� ���������, ���� ���� ����� ����� �������� �� �������, ������� ������������������ �������� �������� � ��� ������� (����� ��������� ����� ��������� ����� � ��������� �� � ����; ����� ����� �� ����� � �������� �� � ����� ��������� �����).
��� �������� ���� ���� ��������� ����������, ����� �� ��������� ������������������ �������� ��������, ����������� ������ ����� �� ������.
*/
#include <iostream>
#include <assert.h>
#include <cstdio>

using namespace std;

bool checkAnagram(char*, char*);
int strlen(char*);

class CStack {
public:
	CStack(int _bufferSize):bufferSize(_bufferSize), realSize(0) { buffer = new char[_bufferSize]; }
	~CStack() { delete[] buffer; }
	void push(char symbol);
	char pop();
	char top();
	bool IsEmpty();
private:
	CStack();
	char* buffer;
	int bufferSize;
	int realSize;
};

class Word {
public:
	Word(): bufferSize(startSize), realSize(0) { buffer = new char[startSize]; }
	~Word() { delete[] buffer; }
	void push_char(char symbol);
	char* get_str();
private:
	void grow();
	int bufferSize;
	int realSize;
	char* buffer;
	static const int startSize = 10;
};

int main()
{
	Word word_1;
	Word word_2;
	char symbol = 0;
	while((symbol = getchar()) != ' ') {
		word_1.push_char(symbol);
	}
	while((symbol = getchar()) != '\n') {
		word_2.push_char(symbol);
	}

	if(checkAnagram(word_1.get_str(), word_2.get_str()) == true) {
		cout<<"YES";
	} else {
		cout<<"NO";
	}
	return 0;
}

bool checkAnagram(char* word1, char* word2)
{
	int i = 0; //�������� ��� ������� �����
	int j = 0; //�������� ��� ������� �����
	if(strlen(word1)!=strlen(word2)) return false;
	int length = strlen(word1);
	CStack stack(length); //���� ��� ����
	bool status = false; // ����� �� ������� ������� �����
	while(i != length || j != length) {
		if(!status) { //���� �� �������� ����� ������� �����
			if(word1[i] == word2[j]) { //���� ����� ���������� ������� ��� ���������
				i++;
				j++;
				if(i==length) status = true;
			}
		}
		if(!status || word1[i] != word2[j]) {
			if(stack.top() == word2[j]) { //���� �� ������� ����� ������ ���������
				stack.pop();
				j++;
			} else if(status) { //���� ������ ����� �������� �� ����� �������
				break;
			} else { //���� ����� ����� �� ������� ����� - ������ � ����
				stack.push(word1[i]);
				i++;
				if(i == length) status = true;
			}
		}
	}

	return stack.IsEmpty(); // ���� � ����� ���-�� ���� - ������ �� ������ �������������
}

void CStack::push(char symbol)
{
	assert(bufferSize!=realSize);
	buffer[realSize++] = symbol;
}

char CStack::pop()
{
	return buffer[--realSize];
}

char CStack::top()
{
	if(IsEmpty()) return 0;
	return buffer[realSize-1];
}

bool CStack::IsEmpty()
{
	return realSize==0;
}

int strlen(char* str)
{
	int i = 0;
	while(str[i]!='\0')
		i++;
	return i;
}

void Word::push_char(char symbol)
{
	if(realSize == bufferSize)
		grow();
	buffer[realSize++] = symbol;
}

void Word::grow()
{
	int newbufferSize = bufferSize * 2;
	char* newBuffer = new char[newbufferSize];
	for(int i = 0; i < realSize; i++) {
		newBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newbufferSize;
}

char* Word::get_str()
{
	push_char('\0');
	return buffer;
}