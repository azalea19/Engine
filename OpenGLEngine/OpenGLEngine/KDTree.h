#ifndef KDTree_h__
#define KDTree_h__

#include "GeometricPrimitives.h"
#include "ObjectInstance.h"


enum Axis
{
  X,
  Y,
  Z
};

struct Node
{
  Axis splitter;
  mAABB box;

  Node* left = nullptr;
  Node* right = nullptr;
};

class KDTree
{

public:

  KDTree(std::vector<ObjectInstance> objects)
  {
    root->splitter = X;
    root->box = MergeBoundingBoxes(objects);
  }

private:


  void SplitX(Node* node)
  {
    mAABB left = node->box;
    mAABB right = node->box;

    left.min.x = node->box.min.x;
    left.max.x = node->box.max.x / 2;

    right.min.x = left.max.x;
    right.max.x = node->box.max.x;

    node->left->box = left;
    node->right->box = right;
  }

  void SplitY(Node* node)
  {
    mAABB left = node->box;
    mAABB right = node->box;

    left.min.y = node->box.min.y;
    left.max.y = node->box.max.y / 2;

    right.min.y = left.max.y;
    right.max.y = node->box.max.y;

    node->left->box = left;
    node->right->box = right;
  }

  void SplitZ(Node* node)
  {
    mAABB left = node->box;
    mAABB right = node->box;

    left.min.z = node->box.min.z;
    left.max.z = node->box.max.z / 2;

    right.min.z = left.max.z;
    right.max.z = node->box.max.z;

    node->left->box = left;
    node->right->box = right;
  }

  void Split(Node* node, int depth = 0)
  {

    depth++;

    if (depth < splitLevel)
    {
      if (node->left == nullptr)
      {
        node->left = new Node();
      }
      if (node->right == nullptr)
      {
        node->right = new Node();
      }

      if (node->splitter == X)
        SplitX(node);
      if (node->splitter == Y)
        SplitY(node);
      if (node->splitter == Z)
        SplitZ(node);

      Split(node->left, depth);
      Split(node->right, depth);
        
    }
   
  }

  Node* root;

  int splitLevel;

};


mAABB MergeBoundingBoxes(std::vector<ObjectInstance> objects)
{
  mAABB finalBox;
  for (int i = 0; i < objects.size; i++)
  {
    finalBox.min = glm::min(finalBox.min, objects[i].GetRenderableObject()->GetBoundingBox().min);
    finalBox.max = glm::max(finalBox.max, objects[i].GetRenderableObject()->GetBoundingBox().max);
  }
  return finalBox;
}




#endif // KDTree_h__