#include "CritterFactory.h"
#include "Critters/Critters.h"

Critter* CritterFactory::create( int wave_number, const Position& entry )
{
  int   wave_level    = wave_number;
  int   base_reward   = 10 * wave_number;
  int   base_HP       = 10 + ( wave_number * 5 );      // Increase HP per wave
  float base_speed    = 1.0f + ( wave_number / 5.0f ); // Speed increases slowly
  float base_strength = 2.0f + ( wave_number / 2.0f ); // Higher waves steal more coins

  return new Critter( base_reward, base_HP, base_strength, base_speed, wave_level, entry );
}