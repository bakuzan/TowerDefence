#ifndef WAVEGENERATIONMANAGER_H
#define WAVEGENERATIONMANAGER_H

#include <vector>

#include "data/EnemyArchetype.h"
#include "data/TypeWeight.h"
#include "data/Wave.h"

class WaveGenerationManager
{
private:
    mutable unsigned int _seedBase;

private:
    int levelToBudget(int level) const;
    std::vector<TypeWeight> levelWeights(int level) const;
    const EnemyArchetype &getArchetype(EnemyType type) const;

    float randf(float a, float b) const;
    int randi(int a, int b) const;

    EnemyType pickType(const std::vector<TypeWeight> &weights) const;
    SpawnGroup makeGroup(EnemyType t, int count, float interval, float delay) const;
    Wave makePatternedWave(int level, float &budget) const;

public:
    WaveGenerationManager(unsigned int seedBase = 1337u);
    ~WaveGenerationManager();

    std::vector<Wave> generateWavesForLevel(int level) const;
};

#endif // WAVEGENERATIONMANAGER_H
