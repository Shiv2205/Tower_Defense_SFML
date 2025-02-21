/**
 * @file Scenery.cpp
 * @author Shivam Veerabudren
 * @brief Implementation of Scenery class
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Scenery.h"

Scenery::Scenery( void ) : Cell( Cell_Type::SCENERY, "~" ), tower( nullptr )
{
}

Scenery::Scenery( Tower* new_tower )
  : Cell( Cell_Type::SCENERY, "~" ), tower( new_tower )
{
  if ( nullptr != new_tower )
  {
    this->setGraphic( "T" );
  }
}

Scenery::~Scenery( void )
{
  if ( nullptr != tower )
  {
    delete this->tower;
  }
}

Tower* Scenery::getTower( void ) const
{
  return this->tower;
}

void Scenery::setTower( Tower* new_tower )
{
  this->tower = new_tower;
  this->setGraphic( "T" );
}