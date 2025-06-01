#include "PhaseManager.h"

PhaseManager::PhaseManager()
    : currentPhase(Phase::PLACEMENT)
{
    // Constructor
}

PhaseManager::~PhaseManager()
{
    // Destructor
}

// Publics

Phase PhaseManager::getCurrentPhase()
{
    return currentPhase;
}

bool PhaseManager::isPlacementPhase()
{
    return currentPhase == Phase::PLACEMENT;
}

bool PhaseManager::isAssaultPhase()
{
    return currentPhase == Phase::COMBAT;
}

bool PhaseManager::isResultsPhase()
{
    return currentPhase == Phase::RESULTS;
}

void PhaseManager::advanceToNextPhase()
{
    currentPhase = static_cast<Phase>((static_cast<int>(currentPhase) + 1) % static_cast<int>(Phase::COUNT));
}
