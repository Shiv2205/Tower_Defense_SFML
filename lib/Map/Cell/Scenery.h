/**
 * @file Scenery.h
 * @author Shivam Veerabudren
 * @brief Declaration of Scenery cell class
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef SCENERY_H
#define SCENERY_H

#include "Cell.h"
#include "Tower/Tower.h"

/**
 * @brief Type of cell where towers can be placed
 *
 */
class Scenery : public Cell
{
public:
  /**
   * @brief Construct a new Scenery object
   *
   */
  Scenery( void );

  /**
   * @brief Construct a new Scenery object
   *
   * @param new_tower Pointer to a Tower object
   */
  Scenery( Tower* new_tower );

  /**
   * @brief Destroy the Scenery object
   *
   */
  ~Scenery( void );

  // Getters
  /**
   * @brief Get the Tower member var
   *
   * @return `Tower*` Pointer to the Tower object currently on the
   * cell. If no Tower present, returns `nullptr`
   */
  Tower* getTower( void ) const;

  // Setters
  /**
   * @brief Set the Tower member var
   *
   * @param new_tower `Tower*` Pointer to the Tower object
   * to be placed on the cell
   */
  void setTower( Tower* new_tower );

private:
  /**
   * @brief Pointer to a `Tower` object
   *
   */
  Tower* tower;
};

#endif // SCENERY_H