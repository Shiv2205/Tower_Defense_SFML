/**
 * @file Map.h
 * @author Shivam Veerabudren
 * @brief Declaration of Map class
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MAP_H
#define MAP_H

#include "Observer/Observable.h"
#include "Cell/Path.h"
#include "Cell/Scenery.h"
#include "Util/Util.h"
#include <iostream>
#include <sstream>

// Typedef
/**
 * @brief Structure to store map dimensions
 *
 */
struct Dimension
{
  u_32 width;
  u_32 height;

  Dimension( void ) : width( 5 ), height( 5 )
  {
  }

  Dimension( u_32 width, u_32 height ) : width( width ), height( height )
  {
  }
};

/**
 * @brief Class to store and handle the cell grid that make up the Map
 *
 */
class Map: public Observable
{
public:
  /**
   * @brief Construct a new Map object
   *
   */
  Map( void );

  /**
   * @brief Construct a new Map object
   *
   * @param map_dimensions The dimensions of the map
   */
  Map( const Dimension& map_dimensions );

  /**
   * @brief Destroy the Map object
   *
   */
  ~Map( void );

  /**
   * @brief Get the dimensions member var
   *
   * @return Dimension A `struct` containing the width and height of
   * the Map
   */
  Dimension getDimensions( void ) const;

  /**
   * @brief Get the entry member var
   *
   * @return Position A `struct` conataining the row and col of the
   * Entry Cell
   */
  Position getEntry( void ) const;

  /**
   * @brief Get the exit member var
   *
   * @return Position A `struct` conataining the row and col of the
   * Exit Cell
   */
  Position getExit( void ) const;

  /**
   * @brief Set the dimensions member var
   *
   * @param dimensions A `Dimension` struct that specifies the width
   * and height of the Map
   */
  void setDimensions( const Dimension& dimensions );

  /**
   * @brief Set the entry member var
   *
   * @param entry A `Position` struct containing the row and col
   * values of the entry cell
   */
  void setEntry( const Position& entry );

  /**
   * @brief Set the exit member var
   *
   * @param exit A `Position` struct containing the row and col values
   * of the exit cell
   */
  void setExit( const Position& exit );

  /**
   * @brief Display the current map
   *
   */
  void Display( void );

  /**
   * @brief Change a Scenery cell to a Path cell
   *
   * @param pos Position ref indicating the row and col number of the
   * cell
   * @param is_entry boolean to indicate if cell is entry point
   * @param is_exit boolean to indicate if cell is exit point
   *
   * @return `true:` If cell was successfully changed to Path cell
   * @return `false:`If an error occurred during checks
   */
  bool MakePath( const Position& pos, bool is_entry = false, bool is_exit = false );

  /**
   * @brief Add a Tower to a Scenery cell
   *
   * @param pos Position ref indicating the row and col number of the
   * cell
   * @param new_tower `Tower*` Pointer to a Tower object
   *
   * @return `true:` If Tower was successfully added to Scenery cell
   * @return `false:`If an error occurred during checks
   */
  bool AddTower( Position& pos, Tower* new_tower );

  /**
   * @brief Method to validate the path created
   *
   * @return `true` If path is valid (Path cells are properly connected)
   * @return `false` If path is not valid (Path cells are not properly
   * connected)
   */
  bool ValidatePath( void );

  /**
   * @brief Method to fetch a `grid` cell given a `Position`
   *
   * @param pos `Position` ref of the target cell
   * @return `Cell*` Pointer to cell at `pos`
   */
  Cell* FetchCell( const Position& pos );

  /**
   * @brief Overloading of "<<" operator. Standard output of Map
   * object
   *
   * @param cout std output stream ref
   * @param current_map Constant ref to current Map object
   * @return std::ostream& std output stream containing Map specific
   * info
   */
  friend std::ostream& operator<<( std::ostream& cout, const Map& current_map );

private:
  /**
   * @brief Helper function to initialiaze the `grid` of cells
   *
   * @param width Width of grid
   * @param height Height of grid
   */
  void InitGrid( u_32 width, u_32 height );

  /**
   * @brief Private method to determine if a `Cell` at a given
   * `Position` is a `Path` or not
   *
   * @param pos `Position` (row, col) of the given `Cell`
   * @return `true` If the `Cell` is a `Path`
   * @return `false` If the `Cell` is not a `Path`
   */
  bool IsPath( const Position& pos );

  /**
   * @brief Link two `Path` cells together
   *
   * @param curr_path
   * @param adj_pos
   */
  void LinkPath( Path* curr_path, const Position& adj_pos );

  /**
   * @brief Stores the dimensions (width and height) of the Map
   *
   */
  Dimension dimensions;

  /**
   * @brief Stores the `Position` (row, col) of the entry Cell
   *
   */
  Position entry;

  /**
   * @brief Stores the `Position` (row, col) of the exit Cell
   *
   */
  Position exit;

  /**
   * @brief Triple pointer. A pointer to a Cell grid (2D Array)
   *
   */
  Cell*** grid;
};

#endif // MAP_H