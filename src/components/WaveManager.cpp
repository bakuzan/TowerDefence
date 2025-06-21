#include "WaveManager.h"

WaveManager::WaveManager()
{
    // Constructor
}

WaveManager::~WaveManager()
{
    // Destructor
}

// Publics

bool WaveManager::hasNextWave() const
{
    return currentWaveIndex < allWaves.size();
}

const Wave &WaveManager::getCurrentWave() const
{
    return allWaves.at(currentWaveIndex);
}

void WaveManager::advanceToNextWave()
{
    ++currentWaveIndex;
}