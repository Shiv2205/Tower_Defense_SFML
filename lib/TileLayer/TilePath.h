#ifndef TILEPATH_H
#define TILEPATH_H

#include "TileLayer.h"
#include "Util/Sfml_Util.h"

#define PATH_TEXTURE  std::string( "res/Maps/32x32/[A]_type1/Tile_4.png" )
#define PATH_TEX_POS  Vec_2i( { 0, 128 } )
#define PATH_TEX_SIZE Vec_2i( { 32, 32 } )

class TilePath : public TileLayer
{
public:
  TilePath( void );

  ~TilePath( void );

private:
};

#endif // TILEPATH_H