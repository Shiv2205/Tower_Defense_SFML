/**
 * @file Map.cpp
 * @author Shivam Veerabudren
 * @brief Implementation of Map class
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Map.h"

Map::Map( void ) : Map( Dimension( 5, 5 ) )
{
}

Map::Map( const Dimension& map_dimensions ) : dimensions( map_dimensions )
{
  u_32 width  = this->dimensions.width;
  u_32 height = this->dimensions.height;

  InitGrid( width, height );
}

Map::~Map( void )
{
  for ( u_32 row = 0; row < this->dimensions.height; row++ )
  {
    for ( u_32 col = 0; col < this->dimensions.width; col++ )
    {
      delete this->grid[ row ][ col ];
    }
    delete[] this->grid[ row ]; // Delete each row individually
  }

  delete[] this->grid; // Delete the array of pointers

  this->grid = nullptr; // Set to nullptr to prevent dangling ref
}

Dimension Map::getDimensions() const
{
  return this->dimensions;
}

Position Map::getEntry() const
{
  return this->entry;
}

Position Map::getExit() const
{
  return this->exit;
}

void Map::setDimensions( const Dimension& dimensions )
{
  this->dimensions = dimensions;

  InitGrid( dimensions.width, dimensions.height );
}

void Map::setEntry( const Position& entry )
{
  this->entry = entry;
}

void Map::setExit( const Position& exit )
{
  this->exit = exit;
}

void Map::Display( void )
{
  LOG( *this );
}

bool Map::MakePath( Position& pos, bool is_entry, bool is_exit )
{
  u_32  width       = this->dimensions.width - 1;
  u_32  height      = this->dimensions.height - 1;
  Cell* target_cell = FetchCell( pos );

  if ( Cell_Type::PATH == target_cell->getCellType() )
  {
    return false;
  }
  else
  {
    Scenery* scene_target = static_cast<Scenery*>( target_cell );
    if ( nullptr != scene_target->getTower() )
    {
      return false;
    }
  }
  if ( ( pos.row > height ) || ( pos.col > width ) )
  {
    return false;
  }
  if ( ( is_entry ) && ( is_exit ) )
  {
    return false;
  }
  if ( ( is_entry ) || ( is_exit ) )
  {
    bool is_on_border = ( pos.row == 0 || pos.row == height ) || ( pos.col == 0 || pos.col == width );

    if ( ! is_on_border )
    {
      return false;
    }

    if ( is_entry )
    {
      this->entry = pos;
    }
    else
    {
      this->exit = pos;
    }
  }

  delete target_cell;
  this->grid[ pos.row ][ pos.col ] = new Path( is_entry, is_exit );

  return true;
}

bool Map::AddTower( Position& pos, Tower* new_tower )
{
  Cell* target_cell = FetchCell( pos );

  if ( Cell_Type::SCENERY != target_cell->getCellType() )
  {
    return false;
  }

  Scenery* scene_cell = static_cast<Scenery*>( target_cell );

  scene_cell->setTower( new_tower );

  return true;
}

bool Map::ValidatePath( void )
{
  if ( this->entry == this->exit )
  {
    return false;
  }

  Position next;      // Position of next Path
  Path*    curr_path; // Pointer to current Path object

  Position curr_pos = this->entry;             // Current Position (row, col)
  u_32     width    = this->dimensions.width;  // Map width
  u_32     height   = this->dimensions.height; // Map height

  while ( curr_pos != this->exit )
  {
    u_32 row   = curr_pos.row;
    u_32 col   = curr_pos.col;
    u_32 south = row + 1;
    u_32 east  = col + 1;
    int  north = row - 1;
    int  west  = col - 1;

    curr_path = static_cast<Path*>( FetchCell( curr_pos ) );

    if ( ( north >= 0 ) && IsPath( Position( north, col ) ) )
    {
      Position adj_pos( north, col );
      LinkPath( curr_path, adj_pos );
    }
    if ( ( south < height ) && IsPath( Position( south, col ) ) )
    {
      Position adj_pos( south, col );
      LinkPath( curr_path, adj_pos );
    }
    if ( ( west >= 0 ) && IsPath( Position( row, west ) ) )
    {
      Position adj_pos( row, west );
      LinkPath( curr_path, adj_pos );
    }
    if ( ( east < width ) && IsPath( Position( row, east ) ) )
    {
      Position adj_pos( row, east );
      LinkPath( curr_path, adj_pos );
    }

    if ( ! curr_path->getNext().linked )
    {
      return false;
    }

    curr_pos = curr_path->getNext();
  }

  return true;
}

std::ostream& operator<<( std::ostream& cout, const Map& current_map )
{
  u_32 map_height = current_map.dimensions.height;
  u_32 map_width  = current_map.dimensions.width;

  std::string        line  = "    ";
  std::string        space = "|  ";
  std::ostringstream buffer( "" );
  buffer << line;

  for ( u_32 col = 0; col < map_width; col++ )
  {
    if ( col > 9 )
    {
      space = "| ";
    }

    buffer << space << col;
    line += "————";
  }

  buffer << "|\n" << line << "—\n";

  space = "  |";
  for ( u_32 row = 0; row < map_height; row++ )
  {
    if ( row > 9 )
    {
      space = " |";
    }

    buffer << " " << row << space;

    for ( u_32 col = 0; col < map_width; col++ )
    {
      buffer << *( current_map.grid[ row ][ col ] );
    }
    buffer << "\n";
  }

  return cout << buffer.str();
}

void Map::InitGrid( u_32 width, u_32 height )
{
  this->grid = new Cell**[ height ];

  for ( u_32 row = 0; row < height; row++ )
  {
    this->grid[ row ] = new Cell*[ width ];

    for ( u_32 col = 0; col < width; col++ )
    {
      this->grid[ row ][ col ] = new Scenery();
    }
  }
}

bool Map::IsPath( const Position& pos )
{
  return this->grid[ pos.row ][ pos.col ]->getCellType() == Cell_Type::PATH;
}

Cell* Map::FetchCell( const Position& pos )
{
  return this->grid[ pos.row ][ pos.col ];
}

void Map::LinkPath( Path* curr_path, const Position& adj_pos )
{
  Path* adjacent = static_cast<Path*>( FetchCell( adj_pos ) );
  if ( ! adjacent->getNext().linked )
  {
    curr_path->setNext( adj_pos );
  }
}