#include <random>
#include <utility>

#include "WaveGenerationManager.h"
#include "constants/GenerationPattern.h"

WaveGenerationManager::WaveGenerationManager(unsigned int seedBase)
    : _seedBase(seedBase)
{
    // Constructor
}

WaveGenerationManager::~WaveGenerationManager()
{
    // Destructor
}

// Publics

std::vector<Wave> WaveGenerationManager::generateWavesForLevel(int level) const
{
    std::vector<Wave> waves;

    float budget = static_cast<float>(levelToBudget(level));
    int waveCount = 6 + randi(0, 3); // 6–9 waves

    for (int i = 0; i < waveCount && budget >= 1.0f; ++i)
    {
        waves.push_back(makePatternedWave(level, budget));
    }

    return waves;
}

// Privates

// --- Config helpers ---
int WaveGenerationManager::levelToBudget(int level) const
{
    double budget = 50.0;

    for (int i = 1; i < level; ++i)
    {
        budget *= 1.5;
    }

    return static_cast<int>(budget + 0.5);
}

std::vector<TypeWeight> WaveGenerationManager::levelWeights(int level) const
{
    if (level <= 1)
    {
        return {
            {EnemyType::BASIC, 1.0f},
            {EnemyType::FAST, 0.5f},
            {EnemyType::TANK, 0.2f},
        };
    }

    if (level == 2)
    {
        return {
            {EnemyType::BASIC, 0.9f},
            {EnemyType::FAST, 0.9f},
            {EnemyType::TANK, 0.35f},
        };
    }

    return {
        {EnemyType::BASIC, 0.8f},
        {EnemyType::FAST, 1.1f},
        {EnemyType::TANK, 0.5f},
    };
}

const EnemyArchetype &WaveGenerationManager::getArchetype(EnemyType type) const
{
    static EnemyArchetype B{EnemyType::BASIC, 1.0f, EnemyStats::create(100, 10, 100.0f, 50), 0.6f, 1.0f};
    static EnemyArchetype F{EnemyType::FAST, 0.8f, EnemyStats::create(60, 8, 160.0f, 40), 0.3f, 0.5f};
    static EnemyArchetype T{EnemyType::TANK, 3.0f, EnemyStats::create(300, 20, 60.0f, 150), 1.2f, 1.6f};

    switch (type)
    {
    case EnemyType::FAST:
        return F;
    case EnemyType::TANK:
        return T;
    default:
        return B;
    }
}

// --- RNG helpers ---
float WaveGenerationManager::randf(float a, float b) const
{
    thread_local std::mt19937 rng(_seedBase);
    std::uniform_real_distribution<float> d(a, b);
    return d(rng);
}

int WaveGenerationManager::randi(int a, int b) const
{
    thread_local std::mt19937 rng(_seedBase);
    std::uniform_int_distribution<int> d(a, b);
    return d(rng);
}

// --- Utility ---
EnemyType WaveGenerationManager::pickType(const std::vector<TypeWeight> &weights) const
{
    float sum = 0.0f;
    for (auto &tw : weights)
    {
        sum += tw.w;
    }

    std::uniform_real_distribution<float> d(0.0f, sum);
    thread_local std::mt19937 rng(_seedBase);
    float x = d(rng);

    for (auto &tw : weights)
    {
        if ((x -= tw.w) <= 0.0f)
        {
            return tw.type;
        }
    }

    return weights.back().type;
}

SpawnGroup WaveGenerationManager::makeGroup(EnemyType t, int count, float interval, float delay) const
{
    const auto &a = getArchetype(t);
    return SpawnGroup::create(
        t, count, interval, delay,
        a.stats);
}

// --- Wave pattern generator ---
Wave WaveGenerationManager::makePatternedWave(int level, float &budget) const
{
    std::vector<SpawnGroup> groups;
    auto weights = levelWeights(level);
    float localDelay = 0.f;

    GenerationPattern p = static_cast<GenerationPattern>(randi(0, 3));

    auto add = [&](EnemyType t, int desired, float iMin, float iMax, float extraDelay = 0.f)
    {
        const auto &a = getArchetype(t);
        int maxByBudget = static_cast<int>(budget / a.cost);
        int c = std::min(desired, std::max(0, maxByBudget));
        if (c <= 0)
        {
            return;
        }

        groups.push_back(makeGroup(t, c, randf(iMin, iMax), localDelay + extraDelay));
        budget -= c * a.cost;
    };

    switch (p)
    {
    case GenerationPattern::Trickle:
        add(EnemyType::BASIC, randi(6, 12), 0.6f, 1.0f);
        localDelay += randf(1.0f, 2.0f);
        add(EnemyType::FAST, randi(3, 6), 0.3f, 0.5f);
        break;
    case GenerationPattern::Burst:
        add(EnemyType::FAST, randi(6, 10), 0.25f, 0.45f);
        localDelay += randf(0.8f, 1.6f);
        add(EnemyType::BASIC, randi(4, 8), 0.5f, 0.8f);
        break;
    case GenerationPattern::Pulse:
        add(EnemyType::TANK, randi(1, 2), 1.2f, 1.6f);
        localDelay += randf(1.2f, 2.0f);
        add(EnemyType::FAST, randi(4, 7), 0.3f, 0.5f);
        break;
    case GenerationPattern::Mixed:
        for (int i = 0; i < 3; ++i)
        {
            EnemyType t = pickType(weights);
            const auto &a = getArchetype(t);
            int cnt = (t == EnemyType::TANK) ? randi(1, 2) : randi(3, 7);
            float delay = localDelay + (i == 0 ? 0.f : randf(0.6f, 1.6f));
            add(t, cnt, a.intervalMin, a.intervalMax, delay);
        }
        break;
    }

    return Wave::create(std::move(groups));
}