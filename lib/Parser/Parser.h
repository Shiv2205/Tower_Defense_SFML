/**
 * @file Parser.h
 * @author Shivam Veerabudren
 * @brief Declaration of namespace Parser. Parses user commands
 * @version 0.1
 * @date 2025-02-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PARSER_H
#define PARSER_H

#include "Map/Cell/Cell.h"
#include <string>
#include <vector>

using str_itr = std::string::iterator;

namespace Parser
{
// Core
std::vector<Position> ParseCommand( std::string& user_command );

// Util
/**
 * @brief Helper function. Checks if a char is a number
 *
 * @param character The char to check
 * @return `true` If char is a number
 * @return `false` If char is not a number
 */
bool IsNum( const char& character );

/**
 * @brief Helper function. Parse and store the row Position value
 *
 * @param row Var to store row Position value
 * @param row_itr `std::string::iterator` Iterator to current char
 * @return str_itr The iterator position after extracting row value
 */
static inline str_itr GetRowPos( u_32& row, str_itr row_itr );

/**
 * @brief Helper function. Parse and store the col Position value
 *
 * @param col Var to store col Position value
 * @param col_itr `std::string::iterator` Iterator to current char
 */
static inline void GetColPos( u_32& col, str_itr& col_itr );

void HandleRange( std::vector<Position>& path_cells, u_32& row, str_itr& itr );

void HandleRange( std::vector<Position>& path_cells, u_32& row, u_32& col,
                  str_itr& itr );
} // namespace Parser

// Definitions of inline functions
inline str_itr Parser::GetRowPos( u_32& row, str_itr row_itr )
{
  while ( ( 'c' != *row_itr ) && ( Parser::IsNum( *row_itr ) ) )
  {
    // Convert char to num and add to row
    row = ( row * 10 ) + ( *row_itr - '0' );
    row_itr++;
  }

  return ( 'c' == *row_itr ) ? ( row_itr - 1 ) : ( row_itr );
}

inline void Parser::GetColPos( u_32& col, str_itr& col_itr )
{
  while ( ( ' ' != *col_itr ) && ( Parser::IsNum( *col_itr ) ) )
  {
    // Convert char to num and add to col
    col = ( col * 10 ) + ( *col_itr - '0' );
    col_itr++;
  }
}

#endif // PARSER_H