#pragma once

#include "commonTypes.h"

enum class InputDevice
{
    KEYBOARD,
    GAMEPAD
};

struct InputState
{
    bool held = false;
    bool pressed = false;
    bool released = false;
    bool prevHeld = false;
    bool bufferActive = false;
    Timer alarmBuffer = { 0.2f, 0.2f };
};

struct Input
{
    InputState actionA;
    InputState actionB;
    InputState actionX;
    InputState actionY;
    InputState actionRB;
    InputState actionLB;
    InputState actionRT;
    InputState actionLT;
    InputState dirPadLeft;
    InputState dirPadUp;
    InputState dirPadRight;
    InputState dirPadDown;
    InputState actionStart;
    InputState actionSelect;
    InputDevice device = InputDevice::KEYBOARD;
    bool isJoystickUsed = false;
    bool isMoving = false;
    float deadzoneStick = 0.4f;
    float deadzoneTrigger = 0.2f;
    float direction = 0.0f;
    float joystickAxisX;
    float joystickAxisY;
};

struct InputMap
{
    bool actionA = false;
    bool actionB = false;
    bool actionX = false;
    bool actionY = false;
    bool actionRB = false;
    bool actionLB = false;
    bool actionRT = false;
    bool actionLT = false;
    bool dirPadLeft = false;
    bool dirPadUp = false;
    bool dirPadRight = false;
    bool dirPadDown = false;
    bool actionStart = false;
    bool actionSelect = false;
};
