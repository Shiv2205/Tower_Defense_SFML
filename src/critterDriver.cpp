#include "critterDriver.h"

void critterDemo( void )
{
  Position startPos = { 0, 0 };

  // Create a critter
  Critter critter1( 10, 30, 5, 2, 1, startPos );

  // Attach an observer to critter
  CritterObserver observer( &critter1 );

  std::cout << "\n--- Testing Critter Observer ---\n";

  // Move the critter
  std::cout << "\nMoving the critter...\n";
  critter1.move();

  // Apply damage
  std::cout << "\nApplying 10 damage...\n";
  critter1.takeDamage( 10 );

  // Apply poison effect
  std::cout << "\nApplying poison for 3 turns...\n";
  critter1.applyPoison( 3 );

  // Apply slow effect
  std::cout << "\nApplying slow effect for 2 turns...\n";
  critter1.applySlow( 2 );
}