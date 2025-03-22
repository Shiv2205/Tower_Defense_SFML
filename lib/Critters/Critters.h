#ifndef CRITTERS_H
#define CRITTERS_H

#include "Observer/Observable.h"
#include "Util/Util.h"
#include <iostream>

using namespace std;

// Forward declare observer to avoid circular dependency
class CritterObserver;
class Path;

class Critter : public Observable
{
private:
  int      rewards;
  int      hitPoints;
  float    strength;
  float    speed;
  int      level;
  Position position;
  Path*    curr_cell;

  bool poisoned;
  bool slowed;
  int  poisonDuration;
  int  slowDuration;

public:
  Critter( int rewards, int hitPoints, float strength, float speed, int level, Position startPos );

  void move();
  void takeDamage( int damage );
  void applyPoison( int duration );
  void applySlow( int duration );

  bool     isDead() const;
  Position getPosition() const;
  float    getStrength() const;
  float    getSpeed() const;
  int      getRewards() const;
  Path*    getCurrCell() const;

  void setPosition( const Position& position );
  void setCurrCell( Path* curr_cell );
};

#endif // CRITTERS_H
