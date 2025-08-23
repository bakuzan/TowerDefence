#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <string>

#include "constants/Difficulty.h"
#include "constants/EnvironmentType.h"

class SettingsManager
{
private:
    std::string filename = "settings.txt";

    // Data
    Difficulty difficulty = Difficulty::EASY;
    EnvironmentType environmentType = EnvironmentType::SPRING;

private:
    SettingsManager();
    ~SettingsManager() = default;

    void load();

public:
    static SettingsManager &getInstance()
    {
        static SettingsManager instance;
        return instance;
    }

    void save();
    void reset();

    // Accessors and mutators
    EnvironmentType getEnvironmentType() const;
    void setEnvironmentType(EnvironmentType environmentType);

    Difficulty getDifficulty() const;
    void setDifficulty(Difficulty difficulty);
};

#endif // SETTINGSMANAGER_H
