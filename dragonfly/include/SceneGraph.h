///
/// A scene graph
///

#ifndef __SCENE_GRAPH_H__
#define __SCENE_GRAPH_H__

// Uncomment exactly one of the below.
#define SG_SIMP // simple scene graph (no Quadtree, no Grid)
//#define SG_QUAD // Quadtree scene graph
//#define SG_GRID // Grid scene graph

// System includes.
#include <map>

// Engine includes.
#ifdef SG_GRID
#include "Grid.h"
#endif
#include "Object.h"
#include "ObjectList.h"
#ifdef SG_QUAD
#include "QuadtreeNode.h"
#endif

// Check exactly one of SG_SIMP, SG_QUAD, SG_GRID is defined.
#if !defined(SG_SIMP) && !defined(SG_QUAD) && !defined(SG_GRID)
#pragma message "Must #define exactly one of: SG_SIMPLE, SG_QUAD, SG_GRID"
#elif defined(SG_SIMP) && (defined(SG_QUAD) || defined(SG_GRID))
#pragma message "Must #define exactly one of: SG_SIMPLE, SG_QUAD, SG_GRID"
#elif defined(SG_QUAD) && (defined(SG_SIMP) || defined(SG_GRID))
#pragma message "Must #define exactly one of: SG_SIMPLE, SG_QUAD, SG_GRID"
#elif defined(SG_GRID) && (defined(SG_SIMP) || defined(SG_QUAD))
#pragma message "Must #define exactly one of: SG_SIMPLE, SG_QUAD, SG_GRID"
#endif

namespace df {

const int MAX_ALTITUDE = 4;

class SceneGraph {

 private:
  ObjectList m_active_objects;   ///< All active Objects.
  ObjectList m_solid_objects;    ///< Solid Objects.
  ObjectList m_visible_objects[MAX_ALTITUDE+1]; ///< Visible Objects.
  ObjectList m_inactive_objects; ///< All inactive Objects.
  std::map<std::string, ObjectList> m_type; ///< Map of type:Object
#ifdef SG_GRID
  Grid m_grid;			 ///< Grid for collision detection.
#endif
#ifdef SG_QUAD
  QuadtreeNode *m_p_qt;		 ///< Quadtree for collision detection.
#endif
  
 public:
  SceneGraph();
  ~SceneGraph();
  
  /// Insert Object into SceneGraph.
  /// Return 0 if ok, else -1.
  int insertObject(Object *p_o);

  /// Remove Object from SceneGraph.
  /// Return 0 if ok, else -1.
  int removeObject(Object *p_o);

  /// Return all active Objects. Empty list if none.
  ObjectList activeObjects() const;

  /// Return all active, solid Objects. Empty list if none.
  ObjectList solidObjects() const;

  /// Return all active, visible Objects at altitude. Empty list if none.
  ObjectList visibleObjects(int altitude) const;

  /// Return list of Objects matching type.
  /// List is empty if none found.
  ObjectList objectsOfType(std::string type);

  /// Return all inactive Objects. Empty list if none.
  ObjectList inactiveObjects() const;
  
  /// Re-position Object in SceneGraph to new altitude.
  /// Return 0 if ok, else -1.
  int updateAltitude(Object *p_o, int new_alt);

  /// Re-position Object in SceneGraph to new solidness.
  /// Return 0 if ok, else -1.
  int updateSolidness(Object *p_o, Solidness new_solidness);

  /// Re-position Object in SceneGraph to new visibility.
  /// Return 0 if ok, else -1.
  int updateVisible(Object *p_vo, bool new_visible);

  /// Re-position Object in SceneGraph to new activeness.
  /// Return 0 if ok, else -1.
  int updateActive(Object *p_o, bool new_active);

  /// Set position of Object in SceneGraph Quadtree.
  /// Return 0 if ok, else -1.
  int updatePosition(Object *p_o, Vector new_position);
  
  /// Re-position Object in SceneGraph to new type.
  /// Return 0 if ok, else -1.
  int updateType(Object *p_o, std::string new_type);

  /// Return list of solid Objects collided with at position 'where'.
  /// Does not consider if p_o is solid or not.
  ObjectList getCollisions(Object *p_o, Vector where) const;

#ifdef SG_GRID
  /// Get Grid.
  Grid *getGrid();
#endif

#ifdef SG_QUAD
  /// Get Quadtree.
  QuadtreeNode *getQuadtree() const;
#endif
  
  /// Startup Scenegraph (create Grid).
  /// Return 0 if ok, else -1.
  int startUp();

  /// Shutdown Scenegraph (delete Quadtree, clear Grid).
  void shutDown();
};
  
} // end of namespace df
#endif // __SCENE_GRAPH_H__
