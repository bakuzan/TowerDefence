#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <vector>

#include "data/Wave.h"

class WaveManager
{
private:
    std::vector<Wave> allWaves;

public:
    WaveManager();
    ~WaveManager();

    const Wave *getNextUnstartedWave();
    void markWaveStarted(const Wave *wavePtr);
    bool hasUnstartedWave() const;
    void reset();
};

#endif // WAVEMANAGER_H
