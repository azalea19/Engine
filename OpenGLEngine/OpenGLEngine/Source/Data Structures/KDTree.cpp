#include "KDTree.h"
#include "PrimitiveCollisions.h"

struct ObjectBoxPair;
enum Axis;
static std::vector<ObjectBoxPair> GetObjectsInNode(Node* node, std::vector<ObjectBoxPair> const& pairs);
static mAABB MergeBoundingBoxes(std::vector<ObjectBoxPair> const& pairs);
static void Split(Node* node, std::vector<ObjectBoxPair> &pairs, Axis axis, int depth);

enum Axis
{
  X,
  Y,
  Z,
};

struct Node
{
  std::vector<ObjectInstance*> objects;
  mAABB box;

  Node* left = nullptr;
  Node* right = nullptr;
};

struct ObjectBoxPair
{
  ObjectInstance* object;
  mOBB box;

  ObjectBoxPair(ObjectInstance* objectInstance, const mOBB &objectBox)
  {
    object = objectInstance;
    box = objectBox;
  }
};

static std::vector<ObjectBoxPair> CreateObjectBoxPairs(std::vector<ObjectInstance*> const& objects)
{
  std::vector<ObjectBoxPair> pairs;

  for (int i = 0; i < objects.size(); i++)
  {
    pairs.push_back(ObjectBoxPair(objects[i], objects[i]->GetBoundingBox()));
  }
  return pairs;
}

KDTree::KDTree(std::vector<ObjectInstance*> const& objects, int depthLevel)
  : root(nullptr)
{
  if (objects.size() > 0)
  {
    std::vector<ObjectBoxPair> pairs = CreateObjectBoxPairs(objects);
    root->box = MergeBoundingBoxes(pairs);
    Split(root, pairs, X, depthLevel);
  }
}

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

KDTree::~KDTree()
{
  if (root)
  {
    DeleteNodeRecursive(root);
    root = nullptr;
  }

}

static bool Intersects(mAABB const& box, Node const* node) 
{
  //If box is colliding with the bounding volume in our node
  if (Intersects(box, node->box))
  {
    //If children aren't null
    if (node->left)
    {
      //Pass box down to my children
      if (!Intersects(box, node->left) && !Intersects(box, node->right))
        return false;
      else
        return true;
    }
    else
    {
      //End of tree reached 
      //If either node is null node is a leaf
        for (int i = 0; i < node->objects.size(); i++)
        {
          if (Intersects(box, node->objects[i]->GetRenderableObject()->GetBoundingBox()))         
            return true;
        }
    }   
  }
  return false;
}

bool KDTree::Intersects(mAABB const& box) const
{
  return ::Intersects(box, root);
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
  left.max.y = node->box.max.y / 2;

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
  left.max.z = node->box.max.z / 2;

  right.min.z = left.max.z;
  right.max.z = node->box.max.z;

  node->left->box = left;
  node->right->box = right;
}

static void Split(Node* node, std::vector<ObjectBoxPair> &pairs, Axis axis, int depth)
{
  //Check if we have reached the depth limit for the tree
  if (depth > 0 && pairs.size() > 1)
  {
    node->left = new Node();
    node->right = new Node();

    if (axis == X)
      SplitX(node);
    if (axis == Y)
      SplitY(node);
    if (axis == Z)
      SplitZ(node);

    std::vector<ObjectBoxPair> leftPairs = GetObjectsInNode(node->left, pairs);
    std::vector<ObjectBoxPair> rightPairs = GetObjectsInNode(node->right, pairs);

    //We are done with 'pairs' now, free the memory before the recursive calls to avoid stack overflow
    pairs.clear();
    pairs.shrink_to_fit();

    if (leftPairs.empty())
    {
      node->box = node->right->box;
      delete node->left;
      delete node->right;
      node->left = nullptr;
      node->right = nullptr;
      Split(node, rightPairs, Axis((axis + 1) % 3), depth + 1);
    }
    else if (rightPairs.empty())
    {
      node->box = node->left->box;
      delete node->left;
      delete node->right;
      node->left = nullptr;
      node->right = nullptr;
      Split(node, leftPairs, Axis((axis + 1) % 3), depth + 1);
    }
    else
    {
      Split(node->left, leftPairs, Axis((axis + 1) % 3), depth + 1);
      Split(node->right, rightPairs, Axis((axis + 1) % 3), depth + 1);
    }

  }
  else
  {
    for (int i = 0; i < pairs.size(); i++)
      node->objects.push_back(pairs[i].object);
  }
}

static mAABB MergeBoundingBoxes(std::vector<ObjectBoxPair> const& pairs)
{
  mAABB finalBox;
  finalBox.min = vec3(FLT_MAX);
  finalBox.max = vec3(FLT_MIN);
  for (int i = 0; i < pairs.size(); i++)
  {
    for (int j = 0; j < 8; j++)
    {
      finalBox.min = glm::min(finalBox.min, pairs[i].box.corners[j]);
      finalBox.max = glm::max(finalBox.max, pairs[i].box.corners[j]);
    }
  }
  return finalBox;
}

static std::vector<ObjectBoxPair> GetObjectsInNode(Node* node, std::vector<ObjectBoxPair> const& pairs)
{
  std::vector<ObjectBoxPair> newList;

  for (int i = 0; i < pairs.size(); i++)
  {
    if (Intersects(node->box, pairs[i].box))
    {
      newList.push_back(pairs[i]);
    }      
  }
  return newList;
}

