#include "TileMap.h"
#include "TileCritters.h"
#include "TilePath.h"
#include "TileTowers.h"

TileMap::TileMap( void ) : Map(), TileLayer( SCENERY_TEXTURE, SCENE_TEX_POS, SCENE_TEX_SIZE ) {}

TileMap::TileMap( const Dimension& dimensions ) : Map( dimensions ), TileLayer( SCENERY_TEXTURE, SCENE_TEX_POS, SCENE_TEX_SIZE ) {}

TileMap::~TileMap( void ) {}

bool TileMap::Load( void )
{
  Dimension     map               = this->getDimensions();
  TileTowers*   tower_layer_ptr   = this->layer_reg.getLayerOf<TileTowers*>();
  TilePath*     path_layer_ptr    = this->layer_reg.getLayerOf<TilePath*>();
  TileCritters* critter_layer_ptr = this->layer_reg.getLayerOf<TileCritters*>();

  bool layers_loaded    = TileLayer::Load() && this->layer_reg.LoadLayers();
  bool layer_ptrs_valid = tower_layer_ptr || path_layer_ptr || critter_layer_ptr;
  
  if ( ( ! layers_loaded ) || ( ! layer_ptrs_valid ) )
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
          tower_layer_ptr->RegisterTile( target_vertex_idx, target_pos, cell_tower->getName() );
        }
      }
      else if ( Cell_Type::PATH == target_cell->getCellType() )
      { //* PATH CELLS
        path_layer_ptr->RegisterTile( target_vertex_idx, target_pos );
        
        Path* path_cell = static_cast<Path*>( target_cell );
        
        if ( path_cell->isEntry() )
        { //* CRITTERS
          critter_layer_ptr->setEntryPoint( target_pos );
          critter_layer_ptr->setEntryCell( path_cell );
          critter_layer_ptr->WaveInit();
        }
      }
    }
  }

  
  return true;
}
