#include "ElectricTower.h"
#include <iostream>

/* Electric Tower:
   - The cheapest tower among all other towers.
   - Can attack critters within a 10cm range, meaning it starts attacking immediately.
   - Has the fastest build time.
   - Fires rapidly but deals moderate damage.
*/
ElectricTower::ElectricTower() : Tower( "ElectricTower", 1, 100, 10.0, 5.0, 3.0 )
{
}

void ElectricTower::attack() const
{
  std::cout << getName() << " fires a rapid electric pulse! Deals " << getPower() << " damage instantly.\n";
}
