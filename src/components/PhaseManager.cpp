#include "PhaseManager.h"

#include "components/PlacementPhaseController.h"
#include "components/CombatPhaseController.h"
#include "components/ResultsPhaseController.h"

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

std::unique_ptr<PhaseController> PhaseManager::createController()
{
    switch (currentPhase)
    {
    case Phase::PLACEMENT:
        return std::make_unique<PlacementPhaseController>();
    case Phase::COMBAT:
        return std::make_unique<CombatPhaseController>();
    case Phase::RESULTS:
        return std::make_unique<ResultsPhaseController>();
    default:
        return nullptr; // Fallback if needed
    }
}