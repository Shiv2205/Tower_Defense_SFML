/**
 * @file Parser.cpp
 * @author Shivam Veerabudren
 * @brief Implementation of namespace Parser
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Parser.h"

std::vector<Position> Parser::ParseCommand( std::string& user_command )
{
  str_itr itr      = user_command.begin();
  u_32    row      = 0;
  u_32    col      = 0;
  char    token    = ' ';
  bool    pos_flag = false;

  std::vector<Position> path_cells;

  while ( user_command.end() > itr )
  {
    token = *itr;

    switch ( token )
    {
    case 'r':
      if ( itr >= user_command.end() )
      {
        break;
      }
      itr = GetRowPos( row, ( itr + 1 ) );
      if ( ':' == *itr )
      {
        itr++;
        HandleRange( path_cells, row, itr );
      }
      break;

    case 'c':
      itr++;
      if ( itr >= user_command.end() )
      {
        break;
      }
      GetColPos( col, itr );
      if ( ':' == *itr )
      {
        itr++;
        HandleRange( path_cells, row, col, itr );
      }
      else
      {
        pos_flag = true;
      }
      break;
    }

    if ( pos_flag )
    {
      path_cells.push_back( Position( row, col ) );
      pos_flag = false;
      row      = 0;
      col      = 0;
    }

    itr++;
  }

  return path_cells;
}

bool Parser::IsNum( const char& character )
{
  return ( ( character >= '0' ) && ( character <= '9' ) );
}

void Parser::HandleRange( std::vector<Position>& path_cells, u_32& row, str_itr& itr )
{
  u_32 limit = 0;
  u_32 col   = 0;

  itr = GetRowPos( limit, itr );

  if ( row > limit )
  {
    u_32 temp = row;
    row       = limit;
    limit     = temp;
  }

  while ( 'c' != *itr )
  {
    itr++;
  }

  itr++;
  GetColPos( col, itr );

  for ( u_32 i = row; i <= limit; i++ )
  {
    Position pos = Position( i, col );
    path_cells.push_back( pos );
  }

  // Reset row
  row = 0;
}

void Parser::HandleRange( std::vector<Position>& path_cells, u_32& row, u_32& col, str_itr& itr )
{
  u_32 limit = 0;

  while ( ! Parser::IsNum( *itr ) )
  {
    itr++;
  }

  GetColPos( limit, itr );

  if ( col > limit )
  {
    u_32 temp = col;
    col       = limit;
    limit     = temp;
  }

  for ( u_32 i = col; i <= limit; i++ )
  {
    Position pos = Position( row, i );
    path_cells.push_back( pos );
  }

  // reset row and col
  row = 0;
  col = 0;
}
