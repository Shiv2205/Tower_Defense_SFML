/**
 * @file Cell.cpp
 * @author Shivam Veerabudren
 * @brief Implementation of Cell class
 * @version 0.1
 * @date 2025-02-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Cell.h"

Cell::Cell( void ) : type( Cell_Type::BASIC ), graphic( "C" )
{
}

Cell::Cell( Cell_Type cell_type, std::string cell_graphic )
  : type( cell_type ), graphic( cell_graphic )
{
}

Cell::~Cell( void )
{ /*LOG("Cell deleted");*/
}

Cell_Type Cell::getCellType( void ) const
{
  return this->type;
}

std::string Cell::getGraphic( void ) const
{
  return this->graphic;
}

void Cell::setCellType( const Cell_Type& new_type )
{
  this->type = new_type;
}

void Cell::setGraphic( std::string new_graphic )
{
  this->graphic = new_graphic;
}

std::ostream& operator<<( std::ostream& cout, const Cell& cell_obj )
{
  return cout << " " << cell_obj.getGraphic() << " |";
}