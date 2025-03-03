#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>

// Forward declaration
class Observer;

class Observable
{
public:
  virtual void addObserver( const Observer* observer );

  virtual void removeObserver( const Observer* observer );

  virtual void notify( void );

private:
  std::vector<const Observer*> observers;
};

#endif // OBSERVABLE_H