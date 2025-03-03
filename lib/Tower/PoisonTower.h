// PoisonTower.h
#ifndef POISONTOWER_H
#define POISONTOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class PoisonTower : public Tower {
public:
    // Constructor
    PoisonTower();

    // Attack method
    void attack() const override;

    void attack(vector<Critter> &critters) ;
};

#endif
