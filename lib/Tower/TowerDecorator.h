// TowerDecorator.h
#ifndef TOWER_DECORATOR_H
#define TOWER_DECORATOR_H
#include "Critters/Critters.h"
#include "Tower.h"

class TowerDecorator : public Tower {
protected:
    Tower* wrappedTower;

public:
    TowerDecorator(Tower* tower)
        : Tower(tower->getName(), tower->getLevel(), tower->getCost(),
                tower->getRange(), tower->getFireRate(), tower->getPower()),
          wrappedTower(tower) {}

    virtual void attack(vector<Critter*>& critters) {
        wrappedTower->attack(critters);
    }

    virtual ~TowerDecorator() {
        delete wrappedTower;
    }
};

#endif
