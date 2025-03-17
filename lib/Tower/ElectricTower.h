// ElectricTower.h
#ifndef ELECTRICTOWER_H
#define ELECTRICTOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class ElectricTower : public Tower
{
public:
  // Constructor
  ElectricTower();

  // Attack Method
  void attack() const override;
};

#endif
