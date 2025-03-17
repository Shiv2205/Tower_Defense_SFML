#ifndef CRITTERS_H
#define CRITTERS_H

#include "Observer/Observable.h"
#include "Util/Util.h"
#include <iostream>

using namespace std;

// Forward declare observer to avoid circular dependency
class CritterObserver;

class Critter: public Observable {
private:
    int rewards;
    int hitPoints;
    int strength;
    int speed;
    int level;
    Position position;

    bool poisoned;
    bool slowed;
    int poisonDuration;
    int slowDuration;

public:
    Critter(int rewards, int hitPoints, int strength, int speed, int level, Position startPos);

    void move();
    void takeDamage(int damage);
    void applyPoison(int duration);
    void applySlow(int duration);

    bool isDead() const;
    Position getPosition() const;
    int getStrength() const;
    int getRewards() const;

};

#endif // CRITTERS_H
