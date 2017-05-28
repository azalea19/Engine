#ifndef TriangleTree_h__
#define TriangleTree_h__

/**
* @file TriangleTree.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief A class for creating a bounding volume hierarchy for the object instances.
* Which allows for fast collision testing.
*/


#include "GeometricPrimitives.h"
#include "ObjectInstance.h"

struct Node;

class TriangleTree
{

public:

  TriangleTree(ObjectInstance* const object, int depthLevel);

  ~TriangleTree();

  bool Intersects(mAABB const& box) const;

  bool Intersects(mOBB const& box) const;

private:

  Node* root;

  std::vector<ConvexHull> collideables;

};


#endif // TriangleTree_h__
