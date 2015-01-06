/*
* ����������� ���������
* ���-12
* ���� ��� ������ ������������ ������� ����� ����� A[0..n) � B[0..m) � ����� k. ����� ���������� ����� ��� �������� (i, j), ��� A[i] + B[j] = k.
*/

#include <iostream>
//#include <assert.h>

using namespace std;

int getCountForSum(int*, int, int*, int, int);

int main()
{
	int n = 0, m = 0;
	cin>>n;
	//assert(n>0);
	int* A = new int[n];
	for(int i = 0; i < n; i++) {
		cin>>A[i];
	}
	cin>>m;
	//assert(m>0);
	int* B = new int[m];
	for(int i = 0; i < m; i++) {
		cin>>B[i];
	}
	int k = 0;
	cin>>k;

	
	int res = getCountForSum(A, n, B, m, k);

	cout<<res;

	delete[] A;
	delete[] B;

	return 0;
}

int getCountForSum(int* A, int n, int* B, int m, int k)
{
	int count = 0; //���-�� ������ ���

	for(int i = 0, j = m-1; i < n, j >= 0; ) {
		if(A[i] - k + B[j] < 0) {
			i++;
		} else 
			if(A[i] - k + B[j] > 0){
				j--;
			} else {
				count++;
				j--;
			}
	}

	return count;
}
