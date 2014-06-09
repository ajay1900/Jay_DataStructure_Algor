//JLU@06/09/2014
//use AdjacencyList--cc ch4

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
  vector<Node* > adjNodes;
  bool bVisited;
  int val;

  Node(int v):val(v), bVisited(false)
  {}  
};

void InitGraph(Node*& root)
{
//use example from https://en.wikipedia.org/wiki/Graph_(mathematics)
  Node* n1=new Node(1);
  Node* n2=new Node(2);
  Node* n3=new Node(3);
  Node* n4=new Node(4);
  Node* n5=new Node(5);
  Node* n6=new Node(6);
  
  n1->adjNodes.push_back(n2);
  n1->adjNodes.push_back(n5);
  
  n2->adjNodes.push_back(n1);
  n2->adjNodes.push_back(n3);
  n2->adjNodes.push_back(n5);
  
  n3->adjNodes.push_back(n2);
  n3->adjNodes.push_back(n4);
  
  n4->adjNodes.push_back(n3);
  n4->adjNodes.push_back(n5);
  n4->adjNodes.push_back(n6);
  
  n5->adjNodes.push_back(n1);
  n5->adjNodes.push_back(n2);
  n5->adjNodes.push_back(n4);
  
  n6->adjNodes.push_back(n4);
  
  root = n1;
}

void output(Node* root)
{
  cout << "\t" <<root->val;
}

void BFS(Node* root)
{
	if(!root)
		return;
	
	Queue<Node* > q;
	q.push(root);	
	while(!q.empty())
	{
		Node* nd = q.front();
		output(nd);
		q.pop();
		nd->bVisited=true;
		for(size_t i=0; i<root->nd->adjNodes.size(); i++)
		{
			Node* node=root->adjNodes[i];
			if(!node->bVisited)
				q.push(node);
		}			
	}
	
  return;	
}

void DFS(Node* root)
{
  if(!root)
    return;
  
  output(root);  
  root->bVisited=true;
  for(size_t i=0; i<root->adjNodes.size(); i++)
  {
    Node* node=root->adjNodes[i];
    if(!node->bVisited)
      DFS(node);
  }
  return;
}

int main()
{
  cout << endl << "DFS" << endl;
  Node* root1=NULL;
  InitGraph(root1);
  DFS(root1);
  
  cout << endl << "BFS" << endl;
  Node* root2=NULL;
  InitGraph(root2);
  BFS(root2);
  
  return 0;
}