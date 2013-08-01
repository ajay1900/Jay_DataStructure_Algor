//  JLu@07/23/2013
//

//http://gamedev.tutsplus.com/tutorials/implementation/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static int MAX_C = 2;

struct Rect
{
  Rect(float xVal, float yVal, float wVal, float hVal):x(xVal), 
    y(yVal), w(wVal), h(hVal)
  {
  }

  bool Contains(Rect* rt)
  {
    return (rt->x > x)
      &&(rt->y > y)
      &&(rt->x+rt->w < x+w)
      &&(rt->y+rt->h < y+h);
  }

  float x;
  float y;
  float w;
  float h;
};

class Node
{
public:
  Node(float x, float y, float w, float h):_bd(x, y, w, h)
  {
  }

  void Insert(Rect* obj)
  {
    if(_subNodes.size()>0)
    { //if there are subNodes already, don't try to put this obj to parent again!
      int idxT=_GetIndex(obj);
      if(idxT!=-1)
      {
        _subNodes[idxT]->Insert(obj);
        return;
      }
    }

    _objs.push_back(obj);

    //if splited already, then, _objs should only contain objs which don't belong to any subnodes,
    //so, don't bother to split again!

    if( _subNodes.size()<1 && _objs.size() > MAX_C)
    {
      Split();
      vector<Rect* > objsT=_objs;
      _objs.clear();
      for(size_t i=0; i<objsT.size(); i++)
      {
        int idxT=_GetIndex(objsT[i]);
        cout << "insert:   " << objsT[i]->x << " " << objsT[i]->y << " " << idxT << endl;
        if(idxT!=-1)
          _subNodes[idxT]->Insert(objsT[i]);
        else
          _objs.push_back(objsT[i]);
      }
    }
  }

  void Split()
  {
    if(_subNodes.size()<1)
    {
      _subNodes.push_back(new Node(_bd.x+_bd.w/2, _bd.y+_bd.h/2, _bd.w/2, _bd.h/2));
      _subNodes.push_back(new Node(_bd.x,         _bd.y+_bd.h/2, _bd.w/2, _bd.h/2));
      _subNodes.push_back(new Node(_bd.x,         _bd.y,         _bd.w/2, _bd.h/2));
      _subNodes.push_back(new Node(_bd.x+_bd.w/2, _bd.y,         _bd.w/2, _bd.h/2));
    }
  }

  //find an object which contains (x,y)
  Rect* Search(float x, float y)
  {
    Rect rect(x,y,0,0);
    //to search _objs first might not be a good idea, it depends on the requirements anyway
    //if we want to find all _objs who contains (x,y), then, do it.
    //otherwise, just search subNodes first    
    int idx=_GetIndex(&rect);
    if(idx!=-1 && _subNodes.size()>0)
    {
      Rect* obj= _subNodes[idx]->Search(x,y);
      return obj;
    }

    for(size_t i=0; i<_objs.size(); i++)
    {
      if(_objs[i]->Contains(&rect))
        return _objs[i];
    }

    return NULL;
  }

  void Output()
  {
    cout << "Node: " << endl;
    for(size_t i=0; i<_objs.size(); i++)
    {
      cout << _objs[i]->x << "\t" <<_objs[i]->y <<endl;  
    }
  }  
private:
  int _GetIndex(Rect* obj)
  {
    int idx=-1;
    for(size_t i=0; i<_subNodes.size(); i++)
    {
      if(_subNodes[i]->_bd.Contains(obj))
      {
        idx = i;
        break;
      }
    }
    return idx;
  }

  vector<Rect* > _objs;  
public:  
  vector<Node* > _subNodes;//size: 4, if octtree, then, 8
  Rect  _bd;
};

void Output_BFS(Node* root)
{
  queue<Node* > que;
  que.push(root);   
  while(!que.empty())
  {
    Node* nd = que.front();
    que.pop();
    nd->Output();      
    for(size_t i=0; i<nd->_subNodes.size(); i++)
    {
      que.push(nd->_subNodes[i]);
    }
  }
}

int main()
{
  Node* qtree = new Node(0,0,10,10);

  qtree->Insert(new Rect(3,3,0.5,0.5));
  qtree->Insert(new Rect(8,8,0.5,0.5));
  qtree->Insert(new Rect(7.1,7.1,0.5,0.5));
  qtree->Insert(new Rect(8,3,0.5,0.5));
  qtree->Insert(new Rect(4,2,0.5,0.5));
  qtree->Insert(new Rect(3,8,0.5,0.5));
  qtree->Insert(new Rect(8.3,8.3,0.5,0.5));
  qtree->Insert(new Rect(8,6,0.5,0.5));
  qtree->Insert(new Rect(4.8,4.8,0.5,0.5));

  Output_BFS(qtree);

  cout << endl;
  cout << "search (8.4, 8.45)" << endl;
  Rect* rt = qtree->Search(8.4,8.45);
  if(rt != NULL)
    cout << rt->x << "\t" << rt->y;
  else
    cout << "found nothing!"<<endl;
}
