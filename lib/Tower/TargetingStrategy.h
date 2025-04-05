#ifndef TARGETINGSTRATEGY_H
#define TARGETINGSTRATEGY_H

#include <vector>
#include "Tower.h"
#include "Critters/Critters.h"
#include "Map/Map.h"

class TargetingStrategy {
public:
    virtual Critter* selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) = 0;
    virtual ~TargetingStrategy() {}
};

class NearestToTowerStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) override;
};

class NearestToExitStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) override;
};

class StrongestCritterStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) override;
};

class WeakestCritterStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) override;
};

#endif
