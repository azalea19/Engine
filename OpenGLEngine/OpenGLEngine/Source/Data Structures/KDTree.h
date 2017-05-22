#ifndef KDTree_h__
#define KDTree_h__

#include "GeometricPrimitives.h"
#include "ObjectInstance.h"

struct Node;

class KDTree
{
public:
  KDTree(std::vector<ObjectInstance*> const& objects, int depthLevel);
  ~KDTree();

  bool Intersects(mAABB const& box) const;

private:
  Node* root;
};




#endif // KDTree_h__