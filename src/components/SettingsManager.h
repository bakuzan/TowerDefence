#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <string>

#include "constants/EnvironmentType.h"

class SettingsManager
{
private:
    std::string filename = "settings.txt";

    // Data
    EnvironmentType environmentType = EnvironmentType::SPRING;

private:
    SettingsManager() = default;
    ~SettingsManager() = default;

    void load();

public:
    static SettingsManager &getInstance()
    {
        static SettingsManager instance;
        instance.load();
        return instance;
    }

    void save();
    void reset();

    // Accessors and mutators
    EnvironmentType getEnvironmentType() const;
    void setEnvironmentType(EnvironmentType environmentType);
};

#endif // SETTINGSMANAGER_H
