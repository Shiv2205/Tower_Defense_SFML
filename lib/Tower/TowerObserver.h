#ifndef TOWER_OBSERVER_H
#define TOWER_OBSERVER_H

#include "Tower.h"
#include <iostream>

class TowerObserver{
public:
virtual void update (const Tower & tower)=0;
virtual ~TowerObserver() {} // Virtual destructor
};

class TowerDisplay : public TowerObserver {
public:
    void update(const Tower& tower) override {
        std::cout << "\n[Tower Updated]\n";
        tower.display();
    }
};

#endif // TOWER_OBSERVER_H