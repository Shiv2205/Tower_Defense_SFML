#include "Critters.h"
#include "CrittersObserver.h"

using namespace std;

// Constructor
Critter::Critter( int rewards, int hitPoints, float strength, float speed, int level, Position startPos )
    : rewards( rewards ), hitPoints( hitPoints ), strength( strength ), speed( speed ), level( level ), position( startPos ),
      poisoned( false ), slowed( false ), poisonDuration( 0 ), slowDuration( 0 )
{
  this->curr_cell = nullptr;
  notify(); // Notify observers
}

// Move function (for testing)
void Critter::move()
{
  cout << "Critter moved from (" << position.row << ", " << position.col << ") to next position (stubbed)" << endl;
  notify(); // Notify observers
}

// Apply damage from towers
void Critter::takeDamage( int damage )
{
  hitPoints -= damage;
  cout << "Critter takes " << damage << " damage! HP: " << hitPoints << endl;
  notify(); // Notify observers

  if ( hitPoints <= 0 )
  {
    cout << "Critter defeated! Player earns " << rewards << " coins!" << endl;
  }
}

// Apply poison effect
void Critter::applyPoison( int duration )
{
  poisoned       = true;
  poisonDuration = duration;
  cout << "Critter is poisoned for " << duration << " turns!" << endl;
  notify();
}

// Apply slow effect
void Critter::applySlow( int duration )
{
  slowed       = true;
  slowDuration = duration;
  cout << "Critter is slowed for " << duration << " turns!" << endl;
  notify();
}
