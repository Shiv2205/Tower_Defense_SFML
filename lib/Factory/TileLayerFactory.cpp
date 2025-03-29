#include "TileLayerFactory.h"
#include "TileLayer/TileCritters.h"
#include "TileLayer/TileLayer.h"
#include "TileLayer/TileMap.h"
#include "TileLayer/TilePath.h"
#include "TileLayer/TileTowers.h"

TileLayer* TileLayerFactory::create( const TileType& request_tile )
{
  switch ( request_tile )
  {
  case TileType::LAYER:
    return new TileLayer();
    break;

  case TileType::MAP:
    return new TileMap();
    break;

  case TileType::PATH:
    return new TilePath();
    break;

  case TileType::TOWERS:
    return new TileTowers();
    break;

  case TileType::CRITTERS:
    return new TileCritters();
    break;
  }

  return nullptr;
}
