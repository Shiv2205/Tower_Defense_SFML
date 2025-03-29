/**
 * @file Cell.h
 * @author Shivam Veerabudren
 * @brief Base Class for all cell types
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CELL_H
#define CELL_H

#include "Util/Util.h"
#include <iostream>
#include <string>

// Typedefs
/**
 * @brief Data type to store cell type
 *
 */
enum Cell_Type
{
  BASIC,
  SCENERY,
  PATH
};

/**
 * @brief Base class for all cell types
 *
 */
class Cell
{
public:
  /**
   * @brief Construct a new Cell object
   *
   */
  Cell( void );

  /**
   * @brief Construct a new Cell object
   *
   * @param cell_type Type of cell
   * @param cell_graphic Graphical representation of cell type (Ex:
   * Path cell -> #)
   */
  Cell( Cell_Type cell_type, std::string cell_graphic );

  /**
   * @brief Destroy the Cell object
   *
   */
  ~Cell( void );

  // Getters
  /**
   * @brief Get the Cell Type member var
   *
   * @return Cell_Type
   */
  Cell_Type getCellType( void ) const { return this->type; }

  /**
   * @brief Get the Graphic member var
   *
   * @return std::string
   */
  std::string getGraphic( void ) const { return this->graphic; }

  // Setters
  /**
   * @brief Set the Cell Type member var
   *
   * @param new_type
   */
  void setCellType( const Cell_Type& new_type ) { this->type = new_type; }

  /**
   * @brief Set the Graphic member var
   *
   * @param new_graphic
   */
  void setGraphic( std::string new_graphic ) { this->graphic = new_graphic; }

  friend std::ostream& operator<<( std::ostream& cout, const Cell& cell_obj );

private:
  /**
   * @brief Stores the type of cell
   *
   */
  Cell_Type type;

  /**
   * @brief Stores the graphical representation of the cell
   * `C` - Basic Cell
   * `~` - Scenery Cell (`T` -  Scenery with Tower)
   * `#` - Path Cell
   */
  std::string graphic;
};

#endif // CELL_H