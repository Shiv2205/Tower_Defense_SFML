#ifndef CRITTER_OBSERVER_H
#define CRITTER_OBSERVER_H

#include "Critters.h"
#include "Observer/Observer.h"
#include <iostream>

class CritterObserver : public Observer
{
private:
  Critter* critter;

public:
  CritterObserver( Critter* c ) : critter( c )
  {
    critter->attach( this ); // Attach observer to critter
  }

  ~CritterObserver()
  {
    critter->detach( this ); // Remove observer on destruction
  }

  void update( Observable* subject ) const override
  {
    cout << "Critter Observer: A change occurred in the critter!\n";
    cout << "Critter Position: (" << critter->getPosition().row << ", " << critter->getPosition().col
         << ")\n";
    cout << "HP: " << ( critter->isDead() ? "Dead" : "Alive" ) << endl;
  }
};

#endif // CRITTER_OBSERVER_H
