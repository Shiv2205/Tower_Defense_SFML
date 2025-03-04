#include "Util.h"

std::string Position::show( void ) const
{
  std::string pos  = "(";
  pos             += std::to_string( row ) + ", " + std::to_string( col ) + ")";

  return pos;
}

bool operator==( const Position& pos_1, const Position& pos_2 )
{
  return ( ( pos_1.row == pos_2.row ) && ( pos_1.col == pos_2.col ) );
}

bool operator!=( const Position& pos_1, const Position& pos_2 )
{
  return ! ( pos_1 == pos_2 );
}