#include "player.h"
#include "Tower.h"
#include <iostream>
#include <algorithm>

// Constructor
Player::Player(int startingCurrency)
    : currency(startingCurrency) {}

// Get current currency
int Player::getCurrency() const {
    return currency;
}

// Add currency
void Player::addCurrency(int amount) {
    currency += amount;
}

// Spend a specific amount of currency
bool Player::spendCurrency(int amount) {
    if (amount > currency) return false;
    currency -= amount;
    return true;
}

// Spend currency based on a tower's cost
bool Player::spendCurrency(Tower* tower) {
    return spendCurrency(tower->getCost());
}

// Check if player can afford a specific cost
bool Player::canAfford(int cost) const {
    return currency >= cost;
}

// Check if player can afford a tower
bool Player::canAfford(Tower* tower) const {
    return canAfford(tower->getCost());
}

// Add a tower to player's collection
void Player::addTower(Tower* tower) {
    towers.push_back(tower);
}

// Remove a tower and delete it
void Player::removeTower(Tower* tower) {
    towers.erase(std::remove(towers.begin(), towers.end(), tower), towers.end());
    delete tower;
}

// Get all owned towers
const std::vector<Tower*>& Player::getTowers() const {
    return towers;
}

// Display player info
void Player::displayStats() const {
    std::cout << "Player Currency: " << currency << std::endl;
    std::cout << "Owned Towers: " << towers.size() << std::endl;
}
