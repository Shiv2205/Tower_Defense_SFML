#ifndef TOWER_OBSERVER_H
#define TOWER_OBSERVER_H

#include "Observer/Observer.h"
#include "Tower.h"
#include <iostream>

class TowerObserver{
public:
virtual void update (const Tower & tower)=0;
virtual ~TowerObserver() {} // Virtual destructor
};

class TowerDisplay : public Observer {
public:
    void update(Observable* subject) const override {
        Tower* tower = static_cast<Tower*>(subject);
        std::cout << "\n[Tower Updated]\n";
        tower->display();
    }
};

#endif // TOWER_OBSERVER_H