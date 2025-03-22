#ifndef TILETOWERS_H
#define TILETOWERS_H

#include "TileLayer.h"
#include "Util/Sfml_Util.h"
#include "Util/Util.h"
#include <vector>

#define TOWER_TEXTURE  std::string( "res/Towers/Towers_Tex.png" )
#define TOWER_TEX_POS  Vec_2i( { 0, 0 } )
#define TOWER_TEX_SIZE Vec_2i( { 96, 32 } )

class TileTowers : public TileLayer
{
public:
  TileTowers( void );

  ~TileTowers( void );

  void RegisterTile( const u_32& vertex_idx, const Position& target_tile,
                     const std::string& tile_type="" ) override;

private:
  std::vector<Position> tower_pos_list;
};

#endif // TILETOWERS_H