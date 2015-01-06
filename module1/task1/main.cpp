/*
* ����������� ���������
* ���-12
* ���� ��� ������������ �����: a/b � c/d. ������� �� � ��������� ����������� � ���� ������������ ����� m/n. ������� ����� m � n
*/
#include <iostream>
#include <assert.h>

using namespace std;

int nod(long, long);
void sum(int, int, int, int);

int main()
{
	//������ �����:
	int a = 0, b = 0;
	cin>>a>>b;
	//������ �����:
	int c = 0, d = 0;
	cin>>c>>d;
	assert(a > 0 || b > 0 || c > 0 || d > 0);

	sum(a, b, c, d);

	return 0;
}

//���������� ��� (�������� �������)
int nod(long first, long second)
{
	while(first != 0 && second != 0) {
		if(first > second) {
			first = first % second;
		}
		else {
			second = second % first;
		}
	}
	return first + second;
}

//���������� ����� a/b+c/d � ������������� � ���� ������������ �����
void sum(int a, int b, int c, int d)
{
	long numerator = a*d + b*c;
	long denominator = b*d;
	long mult = nod(numerator, denominator);
	long m = numerator/mult;
	long n = denominator/mult;
	cout<< m << " " << n;
}