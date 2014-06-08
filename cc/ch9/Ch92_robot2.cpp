/*
Ch9.2 of CC
J@06/08/2014
*/
/*
0 0 0 0
1 1 0 1
0 1 0 0
0 0 1 0
*/

#include <iostream>
#include <stack>
using namespace std;

//destination is a,b
int a=0;
int b=0;
const int M = 3;  
const int N = 3;

int mx[4][4] = 
{
	{0, 0, 0, 0},
	{1, 1, 0, 1},
	{1, 0, 0, 0},
	{0, 0, 1, 0}
};

int dp[4][4] = 
{
	{-1, -1, -1, -1},
	{-1, -1, -1, -1},
	{-1, -1, -1, -1},
	{-1, -1, -1, -1}
};

typedef stack<pair<int, int> > vpt;
vpt path;

bool search_dfs(int i, int j)
{
  if(i==a && j==b)
	{
		path.push(make_pair(i,j));
	  return true;
	}
		
  if(mx[i][j] || i<0 || i>M || j<0 || j>N)
		return false;
	bool ret = search_dfs(i+1, j) || search_dfs(i, j+1);
	if(ret)
		path.push(make_pair(i,j));
	return ret;
}

bool search_dp(int i, int j)
{
  if(i==a && j==b)
	{
		path.push(make_pair(i,j));
	  return true;
	}
		
  if(mx[i][j] || i<0 || i>M || j<0 || j>N)
		return false;
	
	if(dp[i][j] > -1)
		return dp[i][j];
	dp[i][j] = search_dp(i+1, j) || search_dp(i, j+1);
	if(dp[i][j])
		path.push(make_pair(i,j));
	return dp[i][j];
}

int main()
{
	a = 3;
	b=3;
	// cout << "3,3  : " << search_dfs(0, 0) << endl;
	cout << "3,3  : " << search_dp(0, 0) << endl;
	// a=0;
	// b=3;
	// cout << "0,3  : " << search_dfs(0, 0) << endl;
	while(!path.empty())
	{
		cout << "<" << path.top().first << " " << path.top().second << ">";
		path.pop();
	}
	
	// cout << "2,0  : " << search_dp(0, 0) << endl;
	
	// a=3;
	// b=0;
	// cout << "3,0  : " << search_dfs(0, 0) << endl;
	// cout << "3,0  : " << search_dp(0, 0) << endl;
}