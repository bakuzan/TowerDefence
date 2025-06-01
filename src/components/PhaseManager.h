#ifndef PHASEMANAGER_H
#define PHASEMANAGER_H

#include <memory>

#include "constants/Phase.h"

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
};

#endif // PHASEMANAGER_H
