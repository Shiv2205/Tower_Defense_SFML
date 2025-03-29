#ifndef TILELAYERFACTORY_H
#define TILELAYERFACTORY_H

#include "Util/Util.h"

//? Forward Declare
class TileLayer;


class TileLayerFactory
{
public:
  TileLayer* create( const TileType& request_tile );
};

#endif // TILELAYERFACTORY_H