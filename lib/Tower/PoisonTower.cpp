#include "PoisonTower.h"
#include <iostream>
using namespace std;

// Constructor using Tower base class constructor
PoisonTower::PoisonTower() : Tower( "PoisonTower", 1, 120, 40, 1.0, 6.0 )
{
}

// Attack Method
void PoisonTower::attack() const
{
  cout << getName() << " sprays poison! Deals " << getPower() << " damage over time!\n";
}
void PoisonTower::attack( vector<Critter>& critters )
{
  for ( auto& critter : critters )
  {
    if ( ! critter.isDead() )
    {
      Position critterPos = critter.getPosition();
      double   dx         = abs( (double)critterPos.row - critterPos.row );
      double   dy         = abs( (double)critterPos.col - critterPos.col );

      if ( ( dx + dy ) <= this->getRange() )
      {
        critter.applyPoison( 3 ); // Apply poison for 3 turns
        cout << getName() << " poisons critter at (" << critterPos.row << ", " << critterPos.col << ")!"
             << endl;
      }
    }
  }
}
