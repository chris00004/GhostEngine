#pragma once

#include "audioTypes.h"
#include "displayTypes.h"
#include "stageTypes.h"
#include "gameObject.h"

#include <string>
#include <vector>

struct Settings
{
    Display display;
    Volume volume;
    float gamepadDeadzone = 0.4f;
};

struct GameData
{
    std::vector< StageData > stages;
    Settings settings;
    int totalHFuel = 0;
    bool firstLaunch = true;
};


