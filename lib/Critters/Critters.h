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
  
  /**
   * @brief Check if the Critter is dead
   *
   * @return true
   * @return false
   */
  bool isDead() const { return this->hitPoints <= 0; }

  /**
   * @brief Get the Position object
   *
   * @return Position
   */
  Position getPosition() const { return this->position; }

  /**
   * @brief Get the Strength object
   *
   * @return float
   */
  float getStrength() const { return this->strength; }

  /**
   * @brief Get the Speed object
   *
   * @return float
   */
  float getSpeed() const { return this->speed; }

  /**
   * @brief Get the Rewards object
   *
   * @return int
   */
  int getRewards() const { return this->rewards; }
  
  int getHitPoints() const { return this->hitPoints; }

  /**
   * @brief Get the Curr Cell object
   *
   * @return Path*
   */
  Path* getCurrCell() const { return this->curr_cell; }

  /**
   * @brief Set the Position object
   * 
   * @param position 
   */
  void setPosition( const Position& position ) { this->position = position; }
  
  /**
   * @brief Set the Curr Cell object
   * 
   * @param curr_cell 
   */
  void setCurrCell( Path* curr_cell ) { this->curr_cell = curr_cell; }
};

#endif // CRITTERS_H
