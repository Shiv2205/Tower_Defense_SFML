#ifndef CRITTER_FACTORY_H
#define CRITTER_FACTORY_H

#include "Util/Util.h"

//Forward declaration
class Critter;

class CritterFactory
{
public:
  Critter* create(int wave_number, const Position& entry);
};

#endif // CRITTER_FACTORY_H