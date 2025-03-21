#ifndef BURNING_DECORATOR_H
#define BURNING_DECORATOR_H
#include "Critters.h"
#include "TowerDecorator.h"
#include <iostream>

class BurningDecorator : public TowerDecorator
{
public:
  BurningDecorator( Tower* tower ) : TowerDecorator( tower )
  {
    setName( tower->getName() + " + Burning" );
  }

  void attack( vector<Critter*>& critters ) override
  {
    wrappedTower->attack( critters );

    for ( auto* critter : critters )
    { 
      if ( ! critter->isDead() )
      {                          
        critter->takeDamage( 2 ); 
        std::cout << getName() << " burns critter at (" << critter->getPosition().row << ", "
                  << critter->getPosition().col << ")!\n";
      }
    }
  }
};

#endif
