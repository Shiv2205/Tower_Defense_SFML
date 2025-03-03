#ifndef OBSERVER_H
#define OBSERVER_H

#include "Observable.h"

class Observer
{
public:
  virtual void update( Observable* subject ) const = 0;

};

#endif // OBSERVER_H