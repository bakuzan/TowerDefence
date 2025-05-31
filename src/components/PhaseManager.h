#ifndef PHASEMANAGER_H
#define PHASEMANAGER_H

#include <memory>

#include "constants/Phase.h"
#include "components/PhaseController.h"

class PhaseManager
{
private:
    Phase currentPhase;

public:
    PhaseManager();
    ~PhaseManager();

    Phase getCurrentPhase();
    bool isPlacementPhase();
    bool isAssaultPhase();
    bool isResultsPhase();

    void advanceToNextPhase();
    std::unique_ptr<PhaseController> createController();
};

#endif // PHASEMANAGER_H
