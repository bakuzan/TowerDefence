#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <vector>

#include "data/Wave.h"

class WaveManager
{
private:
    std::vector<Wave> allWaves;
    std::size_t currentWaveIndex = 0;

public:
    WaveManager();
    ~WaveManager();

    bool hasNextWave() const;
    const Wave &getCurrentWave() const;
    void advanceToNextWave();
};

#endif // WAVEMANAGER_H
