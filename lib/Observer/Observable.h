#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <vector>

class Observable
{
public:

  virtual void addObserver(const Observer* observer);

  virtual void removeObserver(const Observer* observer);

  virtual void notify(void);

private:

  std::vector<const Observer*> observers;
};

#endif // OBSERVABLE_H