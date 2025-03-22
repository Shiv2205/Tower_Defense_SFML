#ifndef CRITTERGROUP_H
#define CRITTERGROUP_H

#include "Critters.h" // Include your Critter class
#include <vector>

// Forward declaration
class Path;

class CritterGroup
{
public:
  // Constructor
  CritterGroup( int wave_num, Position entry );

  const std::vector<Critter*>& getCritters( void ) const;
  int                          getWaveNumber( void ) const;
  const Position&              getEntryPoint( void ) const;
  Path*                        getEntryCell( void ) const;

  void setEntryPoint( const Position& entry_point );
  void setEntryCell( Path* entry_cell_ptr );

  // Generate a wave of critters
  void generateWave( void );

  // Spawn next critter (returns nullptr if no critters left)
  Critter* spawnNextCritter( void );

  // Check if wave is finished
  bool isWaveOver( void ) const;

  // Destructor
  virtual ~CritterGroup( void );

private:
  std::vector<Critter*> critters;       // List of critters in the current wave
  int                   wave_number;    // Current wave number
  Position              entry_point;    // The position where critters spawn
  Path*                 entry_cell_ptr; // Pointer to entry Path cell
};

#endif // CRITTERGROUP_H
