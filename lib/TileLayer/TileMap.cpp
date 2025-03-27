#include "TileMap.h"
#include "TileCritters.h"
#include "TilePath.h"
#include "TileTowers.h"

TileMap::TileMap( void ) : Map(), TileLayer( SCENERY_TEXTURE, SCENE_TEX_POS, SCENE_TEX_SIZE ) {}

TileMap::TileMap( const Dimension& dimensions ) : Map( dimensions ), TileLayer( SCENERY_TEXTURE, SCENE_TEX_POS, SCENE_TEX_SIZE ) {}

TileMap::~TileMap( void )
{
  delete this->path_layer_ptr;
  delete this->tower_layer_ptr;
  delete this->critter_layer_ptr;
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
      { //* SCENERY CELLS
        this->RegisterTile( target_vertex_idx, target_pos );

        Scenery* scene_cell = static_cast<Scenery*>( target_cell );
        Tower*   cell_tower = scene_cell->getTower();

        if ( nullptr != cell_tower )
        { //* TOWERS
          this->tower_layer_ptr->RegisterTile( target_vertex_idx, target_pos, cell_tower->getName() );
        }
      }
      else if ( Cell_Type::PATH == target_cell->getCellType() )
      { //* PATH CELLS
        this->path_layer_ptr->RegisterTile( target_vertex_idx, target_pos );

        Path* path_cell = static_cast<Path*>( target_cell );

        if ( path_cell->isEntry() )
        { //* CRITTERS
          this->critter_layer_ptr->setEntryPoint( target_pos );
          this->critter_layer_ptr->setEntryCell( path_cell );
        }
      }
    }
  }

  this->critter_layer_ptr->WaveInit();

  return true;
}
