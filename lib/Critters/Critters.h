#ifndef CRITTERS_H
#define CRITTERS_H

#include "Util/Util.h"
#include <iostream>
#include <vector>

using namespace std;
using std::vector;

// Forward declare observer to avoid circular dependency
class CritterObserver;

class Critter {
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

    vector<CritterObserver*> observers; // Stores observers

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

    // Observer methods
    void addObserver(CritterObserver* observer);
    void removeObserver(CritterObserver* observer);
    void notifyObservers();
};

#endif // CRITTERS_H
