#include "TileTowers.h"

TileTowers::TileTowers( void ) : TileLayer( TOWER_TEXTURE, TOWER_TEX_POS, TOWER_TEX_SIZE )
{
}

void TileTowers::RegisterTile( const u_32& vertex_idx, const Position& target_tile,
                                const std::string& tile_type )
{
  // Add Tower position to list
  this->tower_pos_list.push_back( target_tile );

  // Get ptr to target vertex
  sf::Vertex* tower_cell_vertices = this->getLayerVertex( vertex_idx );

  // Init Vertices for corresponding tower type
  if ( ICE_TOWER == tile_type )
  {
    InitVertices( tower_cell_vertices, target_tile );
  }
  else if ( POISON_TOWER == tile_type )
  {
    InitVertices( tower_cell_vertices, target_tile, { 1, 0 } );
  }
  else if ( ELEC_TOWER == tile_type )
  {
    InitVertices( tower_cell_vertices, target_tile, { 2, 0 } );
  }
}

TileTowers::~TileTowers( void )
{
}