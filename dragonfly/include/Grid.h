//
// Grid.h - A grid class for game objects.
//

#ifndef __GRID_H__
#define __GRID_H__

// System includes.
#include <tuple>
#include <vector>

// Engine includes.
#include "ObjectList.h"

namespace df {

const int GRID_WIDTH_DEFAULT = 20;
const int GRID_HEIGHT_DEFAULT = 8;

typedef std::tuple<int, int> Cell;

class Grid {

 private:
  ObjectList **m_p_grid;      ///< The grid.
  ObjectList m_out_of_bounds; ///< All out of bounds objects.
  int m_width;		      ///< Grid width.
  int m_height;		      ///< Grid height.

 public:

  // Constructor.
  Grid();

  // Destructor.
  ~Grid();

  /// Set dimensions. Deletes and re-creates grid.
  void setDimensions(int new_width, int new_height);

  /// Get height.
  int getHeight() const;

  /// Get width.
  int getWidth() const;

  /// Insert Object into grid.
  /// Return 0 if ok, else -1.
  int insertObject(Object *p_o);

  /// Remove Object from grid.
  /// Return 0 if ok, else -1.
  int removeObject(Object *p_o);

  /// Return Cell (x,y) for given location.
  Cell positionToCell(Vector where) const;

  /// Return list of Cells for given Object at given location.
  /// Out of bounds cell is (-1, -1).
  std::vector<Cell> positionToCells(Object *p_o, Vector where) const;

  /// Return all Objects that collide at given location.
  /// List is empty if none.
  ObjectList getCollisions(Object *p_o, Vector where) const;

  /// Move Object from old position, add to new position.
  /// Return 0 if ok, else -1.
  int updatePosition(Object *p_o, Vector where); 

  /// Get Objects in a given Cell.
  ObjectList getObjects(Cell cell) const;
  
  /// Return grid as string.
  std::string toString() const;

  /// Write grid to logfile.
  void print() const;

  // Startup (create grid).
  // Return 0 if ok, else -1.
  int startUp();

  /// Shutdown (delete grid).
  void shutDown();

#ifdef DEBUG_GRID
  /// Draw self.
  void draw();
#endif
};

} // end of namespace df

#endif // __GRID_H__
