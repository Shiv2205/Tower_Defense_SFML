/**
 * @file Path.h
 * @author Shivam Veerabudren
 * @brief Declaration of Path cell class
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef PATH_H
#define PATH_H

#include "Cell.h"

/**
 * @brief Type of cell where Critters can move
 *
 */
class Path : public Cell
{
public:
  /**
   * @brief Construct a new Path object
   *
   */
  Path( void );

  /**
   * @brief Construct a new Path object
   *
   * @param is_entry Boolean value indicating if current cell is entry
   * point
   * @param is_exit Boolean value indicating if current cell is exit
   * point
   */
  Path( bool is_entry, bool is_exit );

  /**
   * @brief Destroy the Path object
   *
   */
  ~Path( void );

  /**
   * @brief Getter function for is_entry member var
   *
   * @return `true:` If the current Path cell is the entry point
   * @return `false:` If the current Path cell is not the entry point
   */
  bool isEntry() const { return this->is_entry; }

  /**
   * @brief Getter function for is_exit member var
   *
   * @return `true:` If the current Path cell is the exit point
   * @return `false:` If the current Path cell is not the exit point
   */
  bool isExit() const { return this->is_exit; }

  /**
   * @brief Get the position of the next Cell in the Path
   *
   * @return Position Struct containing row and col values of next
   * Cell in Path
   */
  Position getNext() const { return this->next; }

  /**
   * @brief Get the Next Path object
   * 
   * @return Path* Pointer to next Path cell
   */
  Path* getNextPath() const { return this->next_path; }

  /**
   * @brief Setter function for is_entry member var
   *
   * @param is_entry Boolean value indicating if current cell is entry
   * point
   */
  void setIsEntry( const bool is_entry ) { this->is_entry = is_entry; }

  /**
   * @brief Setter function for is_exit member var
   *
   * @param is_exit Boolean value indicating if current cell is exit
   * point
   */
  void setIsExit( const bool is_exit ) { this->is_exit = is_exit; }

  /**
   * @brief Set the position of the next Cell in Path
   *
   * @param next The `Position` of the next Cell in Path
   */
  void setNext( const Position& next );

  /**
   * @brief Set the Next Path object
   * 
   * @param next_path Pointer to next Path cell
   */
  void setNextPath( Path* next_path ) { this->next_path = next_path; }

private:
  /**
   * @brief Boolean, stores whether the Path cell is the entry cell
   *
   */
  bool is_entry;

  /**
   * @brief Boolean, stores whether the Path cell is the exit cell
   *
   */
  bool is_exit;

  /**
   * @brief Stores a `Position` to the next Path cell
   *
   */
  Position next;

  /**
   * @brief Pointer to next Path cell
   * 
   */
  Path* next_path;
};

#endif // PATH_H