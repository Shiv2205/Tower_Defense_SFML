#include "CrittersGroup.h"

// Constructor initializes the wave number and entry point
CritterGroup::CritterGroup(int waveNum, Position entry)
    : waveNumber(waveNum), entryPoint(entry) {
    generateWave();
}

// Generate a new wave of critters
void CritterGroup::generateWave() {
    critters.clear(); // Clear previous wave

    int numCritters = waveNumber * 2;  // Increase number of critters per wave
    int baseHP = 10 + (waveNumber * 5); // Increase HP per wave
    int baseSpeed = 1 + (waveNumber / 5); // Speed increases slowly
    int baseStrength = 2 + (waveNumber / 2); // Higher waves steal more coins

    for (int i = 0; i < numCritters; i++) {
        critters.push_back(Critter(10, baseHP, baseStrength, baseSpeed, waveNumber, entryPoint));
    }
}

// Spawn next critter (remove it from list)
Critter* CritterGroup::spawnNextCritter() {
    if (!critters.empty()) {
        Critter* nextCritter = &critters.front(); // Get first critter
        critters.erase(critters.begin()); // Remove from list
        return nextCritter;
    }
    return nullptr; // No more critters to spawn
}

// Check if all critters are gone
bool CritterGroup::isWaveOver() const {
    return critters.empty();
}
