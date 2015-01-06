/*
* Лукьянченко Александр
* АПО-12
* Даны две рациональные дроби: a/b и c/d. Сложить их и результат представьте в виде несократимой дроби m/n. Вывести числа m и n
*/
#include <iostream>
#include <assert.h>

using namespace std;

int nod(long, long);
void sum(int, int, int, int);

int main()
{
	//Первая дробь:
	int a = 0, b = 0;
	cin>>a>>b;
	//Вторая дробь:
	int c = 0, d = 0;
	cin>>c>>d;
	assert(a > 0 || b > 0 || c > 0 || d > 0);

	sum(a, b, c, d);

	return 0;
}

//нахождение НОД (алгоритм Евклида)
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

//Вычисление суммы a/b+c/d и представление в виде несократимой дроби
void sum(int a, int b, int c, int d)
{
	long numerator = a*d + b*c;
	long denominator = b*d;
	long mult = nod(numerator, denominator);
	long m = numerator/mult;
	long n = denominator/mult;
	cout<< m << " " << n;
}