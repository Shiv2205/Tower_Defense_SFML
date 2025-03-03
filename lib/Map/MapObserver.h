#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include "Observer/Observer.h"
#include "TileMap.h"

class MapObserver: public Observer
{
public:

  void update( Observable* subject ) const override;

};

#endif // MAPOBSERVER_H