#include "MapObserver.h"

void MapObserver::update( Observable* subject ) const
{
  TileMap* my_map = static_cast<TileMap*>( subject );

  if ( ! my_map->Load() )
  {
    LOG( "Failed to load map" );
  }
}