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

Path::Path( void )
  : Cell( Cell_Type::PATH, "#" ), is_entry( false ), is_exit( false ),
    next( Position() )
{
}

Path::Path( bool is_entry, bool is_exit )
  : Cell( Cell_Type::PATH, "#" ), is_entry( is_entry ), is_exit( is_exit ),
    next( Position() )
{
}

Path::~Path( void )
{
}

bool Path::isEntry() const
{
  return this->is_entry;
}

bool Path::isExit() const
{
  return this->is_exit;
}

Position Path::getNext() const
{
  return this->next;
}

Path* Path::getNextPath() const 
{
  return this->next_path; 
}

void Path::setIsEntry( const bool is_entry )
{
  this->is_entry = is_entry;
}

void Path::setIsExit( const bool is_exit )
{
  this->is_exit = is_exit;
}

void Path::setNext( const Position& next )
{
  this->next = next;
  this->next.linked = true;
}

void Path::setNextPath(Path* next_path) 
{
  this->next_path = next_path; 
}
