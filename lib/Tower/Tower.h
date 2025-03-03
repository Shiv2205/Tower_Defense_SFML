#ifndef TOWER_H
#define TOWER_H

#include "Util/Util.h"
#include "Critters/Critters.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;

// Forward declare the Observer class
class TowerObserver;
class Critter;

class Tower {
private:
    string name;
    int level;
    int cost;
    int refundValue;
    double range;
    double power;
    double fireRate;

    vector<TowerObserver*> observers; // ✅ List of observers

protected:
    void notifyObservers(); // ✅ Notify all observers when values change

public:
    // Constructor
    Tower(string name, int level, int cost, double range, double fireRate, double power);

    // Observer Methods
    void addObserver(TowerObserver* observer);
    void removeObserver(TowerObserver* observer);

    // Setters (Now notify observers)
    void setName(const string& n) { name = n; notifyObservers(); }
    void setLevel(int lvl) { level = lvl; notifyObservers(); }
    void setCost(int c) { cost = c; notifyObservers(); }
    void setRefundValue(int rv) { refundValue = rv; notifyObservers(); }
    void setRange(double r) { range = r; notifyObservers(); }
    void setPower(double p) { power = p; notifyObservers(); }
    void setFireRate(double fr) { fireRate = fr; notifyObservers(); }

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
