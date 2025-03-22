#include "TileMap.h"
#include "TilePath.h"
#include "TileTowers.h"

TileMap::TileMap( void ) : Map(), TileLayer( SCENERY_TEXTURE, SCENE_TEX_POS, SCENE_TEX_SIZE )
{
}

TileMap::TileMap( const Dimension& dimensions )
    : Map( dimensions ), TileLayer( SCENERY_TEXTURE, SCENE_TEX_POS, SCENE_TEX_SIZE )
{
}

TileMap::~TileMap( void )
{
  delete this->path_layer_ptr;
  delete this->tower_layer_ptr;
}

bool TileMap::Load( void )
{
  Dimension map = this->getDimensions();

  bool layers_loaded = TileLayer::Load() && this->path_layer_ptr->Load() && this->tower_layer_ptr->Load();

  if ( ! layers_loaded )
  {
    return false;
  }

  for ( u_32 row = 0; row < map.height; row++ )
  {
    for ( u_32 col = 0; col < map.width; col++ )
    {
      Position target_pos( row, col );
      Cell*    target_cell       = this->FetchCell( target_pos );
      u_32     target_vertex_idx = ( row + ( col * map.height ) ) * 6;

      if ( Cell_Type::SCENERY == target_cell->getCellType() )
      {
        this->RegisterTile( target_vertex_idx, target_pos );

        Scenery* scene_cell = static_cast<Scenery*>( target_cell );
        Tower*   cell_tower = scene_cell->getTower();
        if ( nullptr != cell_tower )
        {
          std::string tower_name = cell_tower->getName();
          this->tower_layer_ptr->RegisterTile( target_vertex_idx, target_pos, tower_name );
        }
      }
      else if ( Cell_Type::PATH == target_cell->getCellType() )
      {
        this->path_layer_ptr->RegisterTile( target_vertex_idx, target_pos );
      }
    }
  }

  return true;
}

const TilePath* TileMap::getPathLayer( void ) const
{
  return this->path_layer_ptr;
}

const TileTowers* TileMap::getTowerLayer( void ) const
{
  return this->tower_layer_ptr;
}

void TileMap::setPathLayer( TilePath* path_layer_ptr )
{
  this->path_layer_ptr = path_layer_ptr;
}

void TileMap::setTowerLayer( TileTowers* tower_layer_ptr )
{
  this->tower_layer_ptr = tower_layer_ptr;
}