// IceTower.cpp
#include "IceTower.h"
#include <iostream>
using namespace std;

// Constructor with base class initializer list
IceTower::IceTower() 
    : Tower("IceTower", 1, 100, 6.0, 1.5, 4.0) {}

// Attack Method
void IceTower::attack() const {
    cout << getName() << " launches an ice blast! Slows enemies within "
         << getRange() << " cm.\n";
}
void IceTower::attack(vector<Critter> &critters) {
    for (auto &critter : critters) {
        if (!critter.isDead()) {
            Position critterPos = critter.getPosition();
            double dx = abs((double)critterPos.row - critterPos.row);
            double dy = abs((double)critterPos.col - critterPos.col);

            if ((dx + dy) <= this->getRange()) {
                critter.applySlow(2);  // Slow for 2 turns
                cout << getName() << " slows critter at (" << critterPos.row << ", " << critterPos.col << ")!" << endl;
            }
        }
    }
}

