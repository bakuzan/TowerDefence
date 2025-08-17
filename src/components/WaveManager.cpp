#include <algorithm>

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

const Wave *WaveManager::getNextUnstartedWave()
{
    for (auto &wave : allWaves)
    {
        if (!wave.hasRun)
        {
            return &wave;
        }
    }

    return nullptr;
}

void WaveManager::markWaveStarted(const Wave *wavePtr)
{
    for (auto &wave : allWaves)
    {
        if (&wave == wavePtr)
        {
            wave.hasRun = true;
            break;
        }
    }
}

bool WaveManager::hasUnstartedWave() const
{
    return std::any_of(allWaves.begin(), allWaves.end(),
                       [](const Wave &w)
                       { return !w.hasRun; });
}

void WaveManager::reset(int level)
{
    allWaves = generator.generateWavesForLevel(level);
}