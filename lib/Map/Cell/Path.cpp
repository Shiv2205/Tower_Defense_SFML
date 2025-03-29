/**
 * @file Path.cpp
 * @author Shivam Veerabudren
 * @brief Implementation of Path class
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Path.h"

Path::Path( void ) : Cell( Cell_Type::PATH, "#" ), is_entry( false ), is_exit( false ), next( Position() ) {}

Path::Path( bool is_entry, bool is_exit ) : Cell( Cell_Type::PATH, "#" ), is_entry( is_entry ), is_exit( is_exit ), next( Position() ) {}

Path::~Path( void ) {}

void Path::setNext( const Position& next )
{
  this->next        = next;
  this->next.linked = true;
}
