//  JLu@07/23/2013
//

//http://gamedev.tutsplus.com/tutorials/implementation/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space/

#include <iostream>
#include <vector>

using namespace std;

static int MAX_C = 2;

struct Rect
{
  Rect(int ctXVal, int ctYVal, int xVal2, int yVal2):ctX(ctXVal), 
      ctY(ctYVal), x2(xVal2), y2(yVal2)
  {
  }
  
  bool Contains(Rect* rt)
  {
    return (rt->ctX>ctX)&&(rt->ctY>ctY)&&(rt->x2<x2)&&(rt->y2<y2);
  }
  
  int ctX;
  int ctY;
  int x2;//halfX
  int y2;//halfY
};

class Node
{
public:
  Node(int ctX, int ctY, int x, int y):_bd(ctX, ctY, x, y)
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
    
    if(_objs.size() > MAX_C)
    {
      Split();
      for(size_t i=0; i<_objs.size(); i++)
      {
        int idxT=_GetIndex(_objs[i]);
        if(idxT!=-1)
          _subNodes[idxT]->Insert(_objs[i]);
      }
    }
  }
  
  void Split()
  {
    if(_subNodes.size()<1)
    {
      _subNodes.push_back(new Node(_bd.ctX+_bd.x2/2, _bd.ctY+_bd.y2/2, _bd.x2/2, _bd.y2/2));
      _subNodes.push_back(new Node(_bd.ctX-_bd.x2/2, _bd.ctY+_bd.y2/2, _bd.x2/2, _bd.y2/2));
      _subNodes.push_back(new Node(_bd.ctX-_bd.x2/2, _bd.ctY-_bd.y2/2, _bd.x2/2, _bd.y2/2));
      _subNodes.push_back(new Node(_bd.ctX+_bd.x2/2, _bd.ctY-_bd.y2/2, _bd.x2/2, _bd.y2/2));
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
  vector<Node* > _subNodes;//size: 4, if octtree, then, 8
  
public:  
  Rect  _bd;
};

int main()
{
  Node* qtree = new Node(5,5,5,5);//0,0,1000,1000 square
  
  qtree->Insert(new Rect(3,3,3,3));
  qtree->Insert(new Rect(4,4,4,4));
  qtree->Insert(new Rect(4,4,2,1));
  qtree->Insert(new Rect(1,1,5,5));  
}
