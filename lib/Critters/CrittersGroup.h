#ifndef CRITTERGROUP_H
#define CRITTERGROUP_H

#include <vector>
#include "Critters.h"  // Include your Critter class

class CritterGroup {
private:
    std::vector<Critter> critters; // List of critters in the current wave
    int waveNumber;  // Current wave number
    Position entryPoint; // The position where critters spawn

public:
    // Constructor
    CritterGroup(int waveNum, Position entry);

    // Generate a wave of critters
    void generateWave();

    // Spawn next critter (returns nullptr if no critters left)
    Critter* spawnNextCritter();

    // Check if wave is finished
    bool isWaveOver() const;
};

#endif // CRITTERGROUP_H
