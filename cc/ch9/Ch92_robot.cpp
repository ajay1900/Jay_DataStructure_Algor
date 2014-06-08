/*
//ch9.2
J@06-06-2014
0 1 1 1
1 2 3 4
1 3 6 10
1 4 10 20
*/
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > v2d;
v2d dp;
int CalcSteps(int i, int j)
{
	int M=dp.size();
	int N=dp[0].size();
	
	if(i>=M||j>=N)
		return 0;
	if(dp[i][j]>0)
		return dp[i][j];
	dp[i][j] = CalcSteps(i-1, j) + CalcSteps(i, j-1);
	return dp[i][j];
}

int main()
{
	int m=4;
	int n=4;
	vector<int> r1(n, 1);
	dp.push_back(r1);	
	
	vector<int> v(n, 0);
	v[0]=1;
	for(int i=1; i<m+1; i++)
		dp.push_back(v);
	dp[0][0] = 0;
	
	cout << CalcSteps(3, 2) << endl;
}