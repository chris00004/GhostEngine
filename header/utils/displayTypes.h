#pragma once

#include<string>

enum DisplayType{
    WINDOWED,
    FULLSCREEN_BORDERLESS,
    FULLSCREEN_EXCLUSIVE
};

struct Display
{
    float x = 640;
    float y = 360;
    const std::string windowTitle = "PROJECT SPARR-0";
    int scale = 1;
    DisplayType type = DisplayType::WINDOWED;
    bool showFps = true;
};
