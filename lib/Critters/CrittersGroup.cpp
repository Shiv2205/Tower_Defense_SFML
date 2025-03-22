#include "CrittersGroup.h"
#include "Factory/CritterFactory.h"

// Constructor initializes the wave number and entry point
CritterGroup::CritterGroup( int wave_num, Position entry ) : wave_number( wave_num ), entry_point( entry )
{
  generateWave();
}

const std::vector<Critter*>& CritterGroup::getCritters( void ) const
{
  return this->critters;
}

int CritterGroup::getWaveNumber() const
{
  return this->wave_number;
}

const Position& CritterGroup::getEntryPoint() const
{
  return this->entry_point;
}

Path* CritterGroup::getEntryCell() const
{
  return this->entry_cell_ptr;
}

void CritterGroup::setEntryPoint( const Position& entry_point )
{
  this->entry_point = entry_point;
}

void CritterGroup::setEntryCell( Path* entry_cell_ptr )
{
  this->entry_cell_ptr = entry_cell_ptr;
}

// Generate a new wave of critters
void CritterGroup::generateWave()
{
  critters.clear();                             // Clear previous wave
  int            numCritters = wave_number * 2; // Increase number of critters per wave
  CritterFactory crit_factory;

  for ( int i = 0; i < numCritters; i++ )
  {
    critters.push_back( crit_factory.create( this->wave_number, this->entry_point ) );
  }
}

// Spawn next critter (remove it from list)
Critter* CritterGroup::spawnNextCritter()
{
  if ( ! critters.empty() )
  {
    Critter* nextCritter = critters.front(); // Get first critter
    critters.erase( critters.begin() );      // Remove from list
    return nextCritter;
  }
  return nullptr; // No more critters to spawn
}

// Check if all critters are gone
bool CritterGroup::isWaveOver() const
{
  return critters.empty();
}

CritterGroup::~CritterGroup()
{
  int num_critters = this->critters.size();

  for ( int i = 0; i < num_critters; i++ )
  {
    Critter* critter_ptr = this->critters.at( i );

    if ( nullptr != critter_ptr )
    {
      delete critter_ptr;
    }
  }
}
