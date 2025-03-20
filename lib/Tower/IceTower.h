// IceTower.h
#ifndef ICETOWER_H
#define ICETOWER_H

#include "Tower.h"

class IceTower : public Tower
{
public:
  // Constructor
  IceTower();

  // Attack method
  void attack() const override;

  void attack( vector<Critter>& critters );
};

#endif
