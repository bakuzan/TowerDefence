#include <algorithm>

#include "WaveManager.h"

WaveManager::WaveManager()
{
    int health = 100;
    float speed = 100;
    int points = 50;
    // TODO
    // Need to add more waves and probably make them dynamic so they can be
    // calculated based on level
    allWaves = {
        Wave::create({
            SpawnGroup::create(EnemyType::BASIC, 8, 1.0f, 0.0f, EnemyStats::create(health, speed, points)),
            SpawnGroup::create(EnemyType::BASIC, 6, 0.5f, 0.0f, EnemyStats::create(health, speed, points)),
            SpawnGroup::create(EnemyType::BASIC, 4, 0.25f, 0.0f, EnemyStats::create(health, speed, points)),
        }),
    };
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

void WaveManager::reset()
{
    for (auto &wave : allWaves)
    {
        wave.hasRun = false;
    }
}