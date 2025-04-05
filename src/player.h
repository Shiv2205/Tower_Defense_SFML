#pragma once

#include <vector>
#include "Tower/Tower.h"

class Player {
private:
    int currency;
    std::vector<Tower*> towers;

public:
    // Constructor
    Player(int startingCurrency = 1000);

    // Currency methods
    int getCurrency() const;
    void addCurrency(int amount);
    bool spendCurrency(int amount);
    bool spendCurrency(Tower* tower); // Spend based on tower cost
    bool canAfford(int cost) const;
    bool canAfford(Tower* tower) const;

    // Tower management
    void addTower(Tower* tower);
    void removeTower(Tower* tower);
    const std::vector<Tower*>& getTowers() const;

    // Utility
    void displayStats() const;
};
