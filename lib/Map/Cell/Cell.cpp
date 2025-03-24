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

Cell::Cell( void ) : type( Cell_Type::BASIC ), graphic( "C" ) {}

Cell::Cell( Cell_Type cell_type, std::string cell_graphic ) : type( cell_type ), graphic( cell_graphic ) {}

Cell::~Cell( void ) { /*LOG("Cell deleted");*/ }

std::ostream& operator<<( std::ostream& cout, const Cell& cell_obj ) { return cout << " " << cell_obj.getGraphic() << " |"; }