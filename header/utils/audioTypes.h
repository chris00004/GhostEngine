#pragma once

#include "SFML/Audio.hpp"

struct Volume { float master = 100.0f; float music = 100.f; float sfx = 100.0f; };

enum class AudioType
{
    TYPE_2D,
    TYPE_3D
};

enum class SoundID
{
    TEST,
    PLAYER_JUMP,
    PLAYER_FOOTSTEP,
    PLAYER_ROLL
};

struct SoundProperties{
    std::string name = "null sound";
    float volume          = 100.0f;
    float pitch           = 1.0f;
    float dopplerFactor    = 1.0f;
    float minDistance      = 25.0f;
    float maxDistance      = 100.0f;
    float attenuation      = 1.0f;
};
