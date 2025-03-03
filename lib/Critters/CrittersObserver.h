#ifndef CRITTER_OBSERVER_H
#define CRITTER_OBSERVER_H

#include <iostream>
#include "Critters.h"

class CritterObserver {
private:
    Critter* critter;

public:
    CritterObserver(Critter* c) : critter(c) {
        critter->addObserver(this);  // Attach observer to critter
    }

    ~CritterObserver() {
        critter->removeObserver(this);  // Remove observer on destruction
    }

    void update() {
        cout << "Critter Observer: A change occurred in the critter!\n";
        cout << "Critter Position: (" << critter->getPosition().row << ", " << critter->getPosition().col << ")\n";
        cout << "HP: " << (critter->isDead() ? "Dead" : "Alive") << endl;
    }
};

#endif // CRITTER_OBSERVER_H
