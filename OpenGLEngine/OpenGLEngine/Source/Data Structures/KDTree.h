#ifndef KDTree_h__
#define KDTree_h__

/**
* @file KDTree.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief A class for creating a "KDTree" style bounding volume hierarchy for the world.
* Which allows for fast collision testing.
*/


#include "GeometricPrimitives.h"
#include "ObjectInstance.h"

struct Node;

class KDTree
{
public:
  KDTree(std::vector<ObjectInstance*> const& objects, int depthLevel);
  ~KDTree();

  bool Intersects(mAABB const& box) const;

  bool Intersects(mOBB const& box) const;

private:
  Node* root;
};




#endif // KDTree_h__