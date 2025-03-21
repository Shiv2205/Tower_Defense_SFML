#include "TargetingStrategy.h"
#include <limits>
#include <cmath>

Critter* NearestToTowerStrategy::selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) {
    Critter* nearest = nullptr;
    int minDistance = std::numeric_limits<int>::max();
    Position towerPos = tower.getPosition();

    for (Critter* critter : critters) {
        if (critter->isDead()) continue;
        Position critterPos = critter->getPosition();
        int dx = std::abs(static_cast<int>(critterPos.row) - static_cast<int>(towerPos.row));
        int dy = std::abs(static_cast<int>(critterPos.col) - static_cast<int>(towerPos.col));
        int distance = dx + dy;
        if (distance < minDistance && distance <= tower.getRange()) {
            minDistance = distance;
            nearest = critter;
        }
    }
    return nearest;
}

Critter* NearestToExitStrategy::selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) {
    Critter* nearest = nullptr;
    int minDistance = std::numeric_limits<int>::max();
    Position exitPos = map.getExit();

    for (Critter* critter : critters) {
        if (critter->isDead()) continue;
        Position critterPos = critter->getPosition();
        int dx = std::abs(static_cast<int>(critterPos.row) - static_cast<int>(exitPos.row));
        int dy = std::abs(static_cast<int>(critterPos.col) - static_cast<int>(exitPos.col));
        int distance = dx + dy;
        if (distance < minDistance) {
            minDistance = distance;
            nearest = critter;
        }
    }
    return nearest;
}

Critter* StrongestCritterStrategy::selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) {
    Critter* strongest = nullptr;
    int maxStrength = -1;

    for (Critter* critter : critters) {
        if (critter->isDead()) continue;
        int strength = critter->getStrength();
        if (strength > maxStrength) {
            maxStrength = strength;
            strongest = critter;
        }
    }
    return strongest;
}

Critter* WeakestCritterStrategy::selectTarget(const Tower& tower, std::vector<Critter*>& critters, const Map& map) {
    Critter* weakest = nullptr;
    int minHP = std::numeric_limits<int>::max();

    for (Critter* critter : critters) {
        if (critter->isDead()) continue;
        int hp = critter->getHitPoints(); // Requires getHitPoints() in Critter
        if (hp < minHP) {
            minHP = hp;
            weakest = critter;
        }
    }
    return weakest;
}
