#ifndef FREEZING_DECORATOR_H
#define FREEZING_DECORATOR_H
#include "Critters/Critters.h"
#include "TowerDecorator.h"
#include <iostream>

class FreezingDecorator : public TowerDecorator
{
public:
  FreezingDecorator( Tower* tower ) : TowerDecorator( tower )
  {
    setName( tower->getName() + " + Freezing" );
  }

  void attack( vector<Critter*>& critters ) override
  {
    wrappedTower->attack( critters );

    for ( auto* critter : critters )
    {
      if ( ! critter->isDead() )
      {                          
        critter->applySlow( 2 ); 

        std::cout << getName() << " slows critter at (" << critter->getPosition().row << ", " 
                  << critter->getPosition().col << ")!\n";
      }
    }
  }
};

#endif
