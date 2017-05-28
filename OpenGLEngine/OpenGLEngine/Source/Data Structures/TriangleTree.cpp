#include "TriangleTree.h"
#include "PrimitiveCollisions.h"


enum Axis;
static std::vector<int> GetObjectsInNode(Node* node, std::vector<int> const& triangleIndexes, std::vector<ConvexHull> const& collideables);
static mAABB MergeBoundingBoxes(std::vector<ConvexHull> const& collideables);
static void Split(Node* node, std::vector<int> &triangleIndexes, std::vector<ConvexHull> const& collideables, Axis axis, int depth);

enum Axis
{
  X,
  Y,
  Z,
};

struct Node
{
  std::vector<int> triangleIndexes;
  mAABB box;

  Node* left = nullptr;
  Node* right = nullptr;
};


static void DeleteNodeRecursive(Node* pNode)
{
  Node& node = *pNode;
  if (node.left)
  {
    DeleteNodeRecursive(node.left);
    node.left = nullptr;
  }
  if (node.right)
  {
    DeleteNodeRecursive(node.right);
    node.right = nullptr;
  }
  delete pNode;
}

TriangleTree::~TriangleTree()
{
  if (root)
  {
    DeleteNodeRecursive(root);
    root = nullptr;
  }
}

//Expecting box in world space coords
static bool Intersects(mAABB const& box, Node const* node, std::vector<ConvexHull> const& collideables)
{
  //If box is colliding with the bounding volume in our node
  if (Intersects(box, node->box))
  {
    //If children aren't null
    if (node->left)
    {
      //Pass box down to my children
      if (!Intersects(box, node->left, collideables) && !Intersects(box, node->right, collideables))
        return false;
      else
        return true;
    }
    else
    {
      //End of tree reached 
      //If either node is null node is a leaf
      for (int i = 0; i < node->triangleIndexes.size(); i++)
      {
        if (Intersects(collideables[node->triangleIndexes[i]], box))       
          return true;
      }
    }
  }
  return false;
}

static bool Intersects(mOBB const& box, Node const* node, std::vector<ConvexHull> const& collideables)
{
  //If box is colliding with the bounding volume in our node
  if (Intersects(box, node->box))
  {
    //If children aren't null
    if (node->left)
    {
      //Pass box down to my children
      if (!Intersects(box, node->left, collideables) && !Intersects(box, node->right, collideables))
        return false;
      else
        return true;
    }
    else
    {
      //End of tree reached 
      //If either node is null node is a leaf
      for (int i = 0; i < node->triangleIndexes.size(); i++)
      {
        if (Intersects(collideables[node->triangleIndexes[i]], box))
          return true;
      }
    }
  }
  return false;
}

bool TriangleTree::Intersects(mAABB const& box) const
{
  return ::Intersects(box, root, collideables);
}

bool TriangleTree::Intersects(mOBB const & box) const
{
  return ::Intersects(box, root, collideables);
}


static void SplitX(Node* node)
{
  mAABB left = node->box;
  mAABB right = node->box;

  left.min.x = node->box.min.x;
  left.max.x = (node->box.min.x + node->box.max.x) / 2;

  right.min.x = left.max.x;
  right.max.x = node->box.max.x;

  node->left->box = left;
  node->right->box = right;
}

static void SplitY(Node* node)
{
  mAABB left = node->box;
  mAABB right = node->box;

  left.min.y = node->box.min.y;
  left.max.y = (node->box.max.y + node->box.min.y) / 2;

  right.min.y = left.max.y;
  right.max.y = node->box.max.y;

  node->left->box = left;
  node->right->box = right;
}

static void SplitZ(Node* node)
{
  mAABB left = node->box;
  mAABB right = node->box;

  left.min.z = node->box.min.z;
  left.max.z = (node->box.max.z + node->box.min.z) / 2;

  right.min.z = left.max.z;
  right.max.z = node->box.max.z;

  node->left->box = left;
  node->right->box = right;
}

static void Split(Node* node, std::vector<int> &triangleIndexes, std::vector<ConvexHull> const& collideables, Axis axis, int depth)
{
  float xLength = node->box.max.x - node->box.min.x;
  float yLength = node->box.max.y - node->box.min.y;
  float zLength = node->box.max.z - node->box.min.z;
  float longestAxis = xLength;
  axis = X;
  if (yLength > longestAxis)
  {
    axis = Y;
    longestAxis = yLength;
  }
  if (zLength > longestAxis)
  {
    axis = Z;
    longestAxis = zLength;
  }

  //Check if we have reached the depth limit for the tree
  if (depth > 0 && triangleIndexes.size() > 20)
  {
    node->left = new Node();
    node->right = new Node();

    if (axis == X)
      SplitX(node);
    if (axis == Y)
      SplitY(node);
    if (axis == Z)
      SplitZ(node);

    std::vector<int> leftPairs = GetObjectsInNode(node->left, triangleIndexes, collideables);
    std::vector<int> rightPairs = GetObjectsInNode(node->right, triangleIndexes,collideables);

    //if (leftPairs.size() + rightPairs.size() < triangleIndexes.size())
    //{
      //std::vector<int> missingIndices;
      //for (int i = 0; i < triangleIndexes.size(); i++)
      //{
      //  bool found = false;
      //  for (int j = 0; j < leftPairs.size() && !found; j++)
      //    if (leftPairs[j] == triangleIndexes[i])
      //      found = true;

      //  for (int j = 0; j < rightPairs.size() && !found; j++)
      //    if (rightPairs[j] == triangleIndexes[i])
      //      found = true;

      //  if (!found)
      //    missingIndices.push_back(triangleIndexes[i]);
      //}

      //if (missingIndices.size() > 0)
      //{
      //  missingIndices = missingIndices;
      //}

    //}

    //We are done with 'pairs' now, free the memory before the recursive calls to avoid stack overflow
    int indexParentCount = triangleIndexes.size();
    triangleIndexes.clear();
    triangleIndexes.shrink_to_fit();

    //if (leftPairs.size() == rightPairs.size() && leftPairs.size() == indexParentCount)
    //{
    //  delete node->left;
    //  delete node->right;
    //  node->left = nullptr;
    //  node->right = nullptr;
    //  leftPairs.clear();
    //  leftPairs.shrink_to_fit();
    //  Split(node, rightPairs, collideables, Axis((axis + 1) % 3), 0);
    //}
    //else if (leftPairs.empty())
    //{
    //  node->box = node->right->box;
    //  delete node->left;
    //  delete node->right;
    //  node->left = nullptr;
    //  node->right = nullptr;
    //  Split(node, rightPairs, collideables, Axis((axis + 1) % 3), depth);
    //}
    //else if (rightPairs.empty())
    //{
    //  node->box = node->left->box;
    //  delete node->left;
    //  delete node->right;
    //  node->left = nullptr;
    //  node->right = nullptr;
    //  Split(node, leftPairs, collideables, Axis((axis + 1) % 3), depth);
    //}
    //else
    //{
      Split(node->left, leftPairs,collideables, Axis((axis + 1) % 3), depth - 1);
      Split(node->right, rightPairs,collideables, Axis((axis + 1) % 3), depth - 1);
   // }

  }
  else
  {
    for (int i = 0; i < triangleIndexes.size(); i++)
      node->triangleIndexes.push_back(triangleIndexes[i]);
  }
}

static mAABB MergeBoundingBoxes(std::vector<ConvexHull> const& collideables)
{
  mAABB finalBox;
  finalBox.min = vec3(FLT_MAX);
  finalBox.max = vec3(-FLT_MAX);

  for (int i = 0; i < collideables.size(); i++)
  {
    for (int j = 0; j < collideables[i].vertices.size(); j++)
    {
      finalBox.min = glm::min(finalBox.min, collideables[i].vertices[j]);
      finalBox.max = glm::max(finalBox.max, collideables[i].vertices[j]);
    }
  }

  for (int i = 0; i < 3; i++)
    if (finalBox.max[i] == finalBox.min[i])
      finalBox.max[i] += 0.1f;

  return finalBox;
}

static std::vector<int> GetObjectsInNode(Node* node, std::vector<int> const& triangleIndexes, std::vector<ConvexHull> const& collideables)
{
  std::vector<int> newList;

  for (int i = 0; i < triangleIndexes.size(); i++)
  {
    if (Intersects(node->box, collideables[triangleIndexes[i]]))
    {
      newList.push_back(triangleIndexes[i]);
    }
  }
  return newList;
}


TriangleTree::TriangleTree(RenderableObject* const object, int depthLevel)
{
  std::vector<mTriangle> const& triangles = object->GetTriangleFaces();
  root = nullptr;

  if (triangles.size() > 0)
  {
    collideables.reserve(triangles.size());

    for (int i = 0; i < triangles.size(); i++)
    {
      collideables.emplace_back(triangles[i]);
    }

    std::vector<int> triangleIndexes;
    triangleIndexes.resize(triangles.size());
    for (int i = 0; i < triangles.size(); i++)
    {
      triangleIndexes[i] = i;
    }
    root = new Node();
    root->box = object->GetBoundingBox();
    Split(root, triangleIndexes, collideables, X, depthLevel);
  }
 
}
