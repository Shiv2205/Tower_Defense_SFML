#ifndef TOWER_H
#define TOWER_H

#include "Util/Util.h"
#include "Critters/Critters.h"
#include "Observer/Observable.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;

// Forward declare the Observer class
class TowerObserver;
class Critter;

class Tower: public Observable{
private:
    string name;
    int level;
    int cost;
    int refundValue;
    double range;
    double power;
    double fireRate;

public:
    // Constructor
    Tower(string name, int level, int cost, double range, double fireRate, double power);

    // Setters (Now notify observers)
    void setName(const string& n) { name = n; notify(); }
    void setLevel(int lvl) { level = lvl; notify(); }
    void setCost(int c) { cost = c; notify(); }
    void setRefundValue(int rv) { refundValue = rv; notify(); }
    void setRange(double r) { range = r; notify(); }
    void setPower(double p) { power = p; notify(); }
    void setFireRate(double fr) { fireRate = fr; notify(); }

    // Getters
    string getName() const { return name; }
    int getLevel() const { return level; }
    int getCost() const { return cost; }
    int getRefundValue() const { return refundValue; }
    double getRange() const { return range; }
    double getPower() const { return power; }
    double getFireRate() const { return fireRate; }

    // Methods
    virtual void attack() const = 0;
    void upgrade();
    void sell();
    void display() const;
    virtual void attack(vector<Critter> &critters);

    // Destructor
    virtual ~Tower() {}
};

#endif // TOWER_H
