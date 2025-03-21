#ifndef POISON_DECORATOR_H
#define POISON_DECORATOR_H
#include "Critters.h"
#include "TowerDecorator.h"
#include <iostream>

class PoisonDecorator : public TowerDecorator
{
public:
  PoisonDecorator( Tower* tower ) : TowerDecorator( tower )
  {
    setName( tower->getName() + " + Poison" );
  }

  void attack( vector<Critter*>& critters ) override
  {
    wrappedTower->attack( critters );

    for ( auto& critter : critters )
    {
      if ( ! critter->isDead() )
      { 
        critter->applyPoison( 3 );
        std::cout << getName() << " poisons critter at (" << critter->getPosition().row << ", "
                  << critter->getPosition().col << ")!\n";
      }
    }
  }
};

#endif
