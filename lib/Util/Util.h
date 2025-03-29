/**
 * @file Util.h
 * @author Shivam Veerabudren
 * @brief Header containing some utility functions and defines
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

/**
 * @brief Macro for easier standard output to console
 *
 */
#define LOG( message ) ( std::cout << message << std::endl )

/**
 * @brief Alias for C++ unsigned int type.
 * Introduced to reduce verbosity while preserving portability
 */
typedef unsigned int u_32;


/**
 * @brief Data type to store and handle cell positions
 *
 */
struct Position
{
  int row;
  int col;
  bool linked;

  Position( void ) : row( 0 ), col( 0 ), linked( false )
  {
  }

  Position( int row_val, int col_val )
    : row( row_val ), col( col_val ), linked( false )
  {
  }

  std::string show( void ) const;

  friend bool operator==( const Position& pos_1, const Position& pos_2 );

  friend bool operator!=( const Position& pos_1, const Position& pos_2 );
};

//? TileLayer Types
enum class TileType
{
  LAYER,
  MAP,
  PATH,
  TOWERS,
  CRITTERS
};

#endif // UTIL_H