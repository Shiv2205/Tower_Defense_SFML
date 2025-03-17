// Tower.cpp
#include "Tower.h"
#include "TowerObserver.h"
#include <iostream>
using namespace std;

// Constructor using initializer list
Tower::Tower( string name, int level, int cost, double range, double fireRate, double power )
    : name( name ), level( level ), cost( cost ), refundValue( cost / 2 ), range( range ), power( power ),
      fireRate( fireRate )
{
}

// Upgrading Tower
// Upgrading Tower (Now Notifies Observers)
void Tower::upgrade()
{
  setLevel( getLevel() + 1 );
  setCost( getCost() + 50 );
  setRefundValue( getRefundValue() + 25 );
  setRange( getRange() * 1.1 );
  setPower( getPower() * 1.2 );
  setFireRate( getFireRate() * 1.1 );

  cout << getName() << " upgraded to level: " << getLevel() << "!\n";
  notify(); // ✅ Notify observers when upgrade happens
}

// Selling Tower (Now Notifies Observers)
void Tower::sell()
{
  cout << getName() << " sold for " << getRefundValue() << " credits.\n";
  notify(); // ✅ Notify observers when tower is sold
}
void Tower::attack( vector<Critter>& critters )
{
  for ( auto& critter : critters )
  {
    if ( ! critter.isDead() )
    {
      Position critterPos = critter.getPosition();
      double   dx         = abs( (double)critterPos.row - critterPos.row );
      double   dy         = abs( (double)critterPos.col - critterPos.col );

      if ( ( dx + dy ) <= range )
      { // Manhattan Distance for range check
        critter.takeDamage( power );
        cout << name << " attacks critter at (" << critterPos.row << ", " << critterPos.col << ") for "
             << power << " damage!" << endl;
      }
    }
  }
}

// Displaying Tower Info
void Tower::display() const
{
  cout << "Tower: " << getName() << "\n"
       << "Level: " << getLevel() << "\n"
       << "Cost: " << getCost() << "\n"
       << "Refund: " << getRefundValue() << "\n"
       << "Range: " << getRange() << "\n"
       << "Power: " << getPower() << "\n"
       << "Fire Rate: " << getFireRate() << "\n";
  cout << "------------------" << "\n";
}
