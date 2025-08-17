#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <vector>

#include "data/Wave.h"
#include "WaveGenerationManager.h"

class WaveManager
{
private:
    WaveGenerationManager generator;
    std::vector<Wave> allWaves;

public:
    WaveManager();
    ~WaveManager();

    const Wave *getNextUnstartedWave();
    void markWaveStarted(const Wave *wavePtr);
    bool hasUnstartedWave() const;
    void reset(int level);
};

#endif // WAVEMANAGER_H
