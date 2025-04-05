#ifndef SPLASH_DECORATOR_H
#define SPLASH_DECORATOR_H

#include "Critters/Critters.h"
#include "TowerDecorator.h"
#include <cmath>
#include <iostream>

class SplashDecorator : public TowerDecorator {
public:
    SplashDecorator(Tower* tower) : TowerDecorator(tower) {
        setName(tower->getName() + " + Splash");
    }

  
    void attack(vector<Critter*>& critters) override {
        wrappedTower->attack(critters);  

        for (auto* critter : critters) {  
            if (!critter->isDead()) {
                Position critterPos = critter->getPosition();

                for (auto* nearby : critters) {  
                    if (!nearby->isDead()) {
                        nearby->takeDamage(getPower() / 2);  
                        std::cout << getName() << " splashes critter at (" 
                                  << nearby->getPosition().row << ", " 
                                  << nearby->getPosition().col << ")!\n";
                    }
                }
            }
        }
    }
};

#endif
