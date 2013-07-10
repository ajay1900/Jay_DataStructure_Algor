//http://www.youtube.com/watch?v=YRgOPvXhrHE
//bad space complexity

#include <iostream>

using namespace std;

const int m=20;

void merge(int P[], int Q[], int R[], int p, int q)
{
cout << "merge" << endl;
  int i,j,k;
  i=j=k=0;
  while(i<p && j<q)
  {
    if(P[i] < Q[j])
    R[k++]=P[i++];
	else
	  R[k++]=Q[j++];
  }
  
  while(i<p)
    R[k++]=P[i++];
	
  while(j<q)
    R[k++]=Q[j++];
	
  
}

void sort(int A[], int B[], int n)
{
  cout << "sort" << endl;
  int A1[m], A2[m];
  int n1,n2;
  if(n == 1) 
    B[0]=A[0];
  else
  {
    n1=n/2;
	n2=n-n1;
	sort(A, A1, n1);
	sort(A+n1, A2, n2);
	merge(A1, A2, B, n1, n2);
  }
}

int main()
{
  int N, i;
  int X[m], Y[m];
  cout << "enter the count of integers\n";
  cin >>N;
  cout<<"enter the integers\n";
  for(i=0; i<N; i++)
    cin>>X[i];
  sort(X, Y, N);
  cout << "sorted values : \n";
  for(i=0; i<N; i++)
    cout<<Y[i]<<" ";
  cout<<endl;
}
