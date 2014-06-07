/*
J@06-06-2014
*/
#include <cstring>
#include <iostream>

using namespace std;

//O(2^N)
int Fibonacci(int n)
{
	if(n==0 || n==1)
		return 1;
	
	return Fibonacci(n-1) + Fibonacci(n-2);
}

int* r;

//O(N)
int Fibonacci_DP(int n)
{
	if(n==0 || n==1)
		return 1;
	
	if(r[n] > 0)
		return r[n];
	
	r[n] = Fibonacci_DP(n-1) + Fibonacci_DP(n-2);
	
	return r[n];
}

int main()
{
	int N=40;
	r = new int[N+1];
	memset(r, 0, sizeof(int)*(N+1));
	cout << Fibonacci(N) << endl;
	cout << Fibonacci_DP(N) << endl;
	delete[] r;
}
