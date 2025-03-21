#ifndef CRITTERGROUP_H
#define CRITTERGROUP_H

#include "Critters.h" // Include your Critter class
#include <vector>

class CritterGroup
{
public:
  // Constructor
  CritterGroup( int waveNum, Position entry );

  const std::vector<Critter*>& getCritters( void ) const;

  int getWaveNumber() const;

  const Position& getEntryPoint() const;

  // Generate a wave of critters
  void generateWave();

  // Spawn next critter (returns nullptr if no critters left)
  Critter* spawnNextCritter();

  // Check if wave is finished
  bool isWaveOver() const;

  // Destructor
  virtual ~CritterGroup();

private:
  std::vector<Critter*> critters;   // List of critters in the current wave
  int                   waveNumber; // Current wave number
  Position              entryPoint; // The position where critters spawn
};

#endif // CRITTERGROUP_H
