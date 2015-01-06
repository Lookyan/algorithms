#include <iostream>

using namespace std;

int BinarySearch(int*, int, double);
void printIndex(int*, int, int*, int);

int main()
{
	int n = 0, m = 0;
	cin>>n>>m;
	int* A = new int[n];
	for(int i = 0; i < n; i++) {
		cin>>A[i];
	}
	int* B = new int[m];
	for(int i = 0; i < m; i++) {
		cin>>B[i];
	}

	printIndex(A, n, B, m);

	delete[] A;
	delete[] B;
	return 0;
}

int BinarySearch( int* arr, int count, int element )
{
	int first = 0;
	int last = count; // Ёлемент в last не учитываетс€.
	while( first < last ) {
		int mid = ( first + last ) / 2;
		if( element <= arr[mid] )
			last = mid;
		else
			first = mid + 1;
	}
	return first;
}

void printIndex(int* A, int n, int* B, int m)
{
	for(int j = 0; j < m; j++) {
		int current = B[j];
		int k = 0;
		for(int i = 1; i < n; i*=2) {
			if(A[i] >= current) {
				break;
			}
			k = i;
		}
		int delta = 0;
		if(2*k+1 > n) {
			delta=n-k;
		} else {
			delta = k+1;
		}
		int res = BinarySearch(A+k, delta, B[j])+k;
		if(res == n+1 && B[j]>A[n-1]) {
			cout<<n<<" ";
		} else {
			cout<<res<<" ";
		}
	}
}