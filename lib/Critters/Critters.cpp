#include "Critters.h"
#include "CrittersObserver.h" 

using namespace std;

// Constructor
Critter::Critter(int rewards, int hitPoints, int strength, int speed, int level, Position startPos)
    : rewards(rewards), hitPoints(hitPoints), strength(strength), speed(speed), level(level), position(startPos),
      poisoned(false), slowed(false), poisonDuration(0), slowDuration(0) {
    notifyObservers();  // Notify observers when a new critter is created
}

// Add an observer
void Critter::addObserver(CritterObserver* observer) {
    observers.push_back(observer);
}

// Remove an observer
void Critter::removeObserver(CritterObserver* observer) {
  //observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

// Notify all observers of a change
void Critter::notifyObservers() {
    for (CritterObserver* observer : observers) {
        observer->update();
    }
}

// Move function (for testing)
void Critter::move() {
    cout << "Critter moved from (" << position.row << ", " << position.col << ") to next position (stubbed)" << endl;
    notifyObservers();  // Notify observers
}

// Apply damage from towers
void Critter::takeDamage(int damage) {
    hitPoints -= damage;
    cout << "Critter takes " << damage << " damage! HP: " << hitPoints << endl;
    notifyObservers();  // Notify observers

    if (hitPoints <= 0) {
        cout << "Critter defeated! Player earns " << rewards << " coins!" << endl;
    }
}

// Apply poison effect
void Critter::applyPoison(int duration) {
    poisoned = true;
    poisonDuration = duration;
    cout << "Critter is poisoned for " << duration << " turns!" << endl;
    notifyObservers();
}

// Apply slow effect
void Critter::applySlow(int duration) {
    slowed = true;
    slowDuration = duration;
    cout << "Critter is slowed for " << duration << " turns!" << endl;
    notifyObservers();
}

// Check if the critter is dead
bool Critter::isDead() const {
    return hitPoints <= 0;
}

// Get current position
Position Critter::getPosition() const {
    return position;
}

// Get critter's strength (how many coins it steals if it reaches exit)
int Critter::getStrength() const {
    return strength;
}

// Get reward amount when critter is killed
int Critter::getRewards() const {
    return rewards;
}
