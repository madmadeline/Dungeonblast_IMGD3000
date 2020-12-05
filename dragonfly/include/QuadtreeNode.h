//
// QuadtreeNode.h - A Quadtree node class.
//

#ifndef __QUADTREENODE_H__
#define __QUADTREENODE_H__

#include "Object.h"
#include "ObjectList.h"

namespace df {

const int QUADTREE_THRESH_DEFAULT = 1;
const int QUADTREE_MAX_DEPTH = 10;

class QuadtreeNode {

 private:
  int m_depth;                 ///< Depth of this node.
  Box m_boundary;              ///< Bounding box of this node.
  QuadtreeNode *m_p_parent;    ///< Parent node (NULL if root).
  ObjectList m_objects;        ///< Objects contained in this node.
  bool m_split;                ///< True if already split children.
  QuadtreeNode *m_p_child[4];  ///< Child nodes (NULL when none).

  // Helper function.
  // Return all Objects that collide at location where.  Recurse in
  // delta direction (-1 up, 0 stay, +1 down).  If self is true, add
  // collisions with self node.  List is empty if none.
  ObjectList getCollisions(Object* p_o, Vector where, int delta,
			   bool self) const;

public:

  /// Construct new node with given parent, depth and boundary.
  QuadtreeNode(QuadtreeNode *p_parent, int depth, Box boundary);

  /// Destructor, free up child nodes.
  ~QuadtreeNode();

  /// Return list of Objects at this node.
  ObjectList getObjects() const;
  
  /// Get boundary.
  Box getBoundary() const; 

  /// Get depth.
  int getDepth() const;

  /// Insert Object at this node and split if count > threshold.
  /// Return 0 if ok, else -1.
  int insertObject(Object* p_o);

  /// Remove Object from this node.
  /// Return 0 if ok (found), else -1.
  int removeObject(Object* p_o);

  /// Split this node if it hasn't already.
  /// Return 0 if ok, else -1.
  int split();

  /// Return node in hierarchy where Object should be placed.
  /// Return NULL if error.
  QuadtreeNode* findOwner(Object* p_o);

  /// Return node in hierarchy where Object should be placed
  /// if moved to 'where'.
  /// Return NULL if error.
  QuadtreeNode* findOwner(Object* p_o, Vector where);

  /// Return node in hierarchy where Object should be placed
  /// if has new bounding box.
  /// Return NULL if error.
  QuadtreeNode* findOwner(Object* p_o, Box b);

  /// Return all Objects that collide at given location.
  /// List is empty if none.
  ObjectList getCollisions(Object *p_o, Vector where) const;

  /// Return current node as string.
  std::string toString() const;

#ifdef DEBUG_QUADTREE
  /// Write node and descendants to logfile.
  void print(std::string label="") const;

  /// Draw self and descendants.
  void draw();
#endif
};

} // end of namespace df

#endif // __QUADTREENODE_H__
