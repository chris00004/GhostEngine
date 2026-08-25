#pragma once

#include<string>
#include<vector>

#include "gameObject.h"

enum class StageRank {
    HYPER_S = 0,
    S = 1,
    A = 2,
    B = 3,
    C = 4,
    D = 5
};

enum class StageID {
    EMPTY = -1,
    INITIALIZATION = 0,
    DIGITAL_STRETCH = 1,
    METROPOLIS = 2,
    HYPER_PLANT = 3,
    TROPICAL_RIG = 4
};

struct StageData
{
    StageID id = StageID::EMPTY;
    std::string name = "Null Stage";
    bool unlocked = false;
    StageRank rank = StageRank::D;
    float rankTimeRequirements[6] = { 999.99f, 999.99f, 999.99f, 999.99f, 999.99f, 999.99f };
    float bestTime = 999.99f;
    int checkPointCount = 0;
    std::vector<float> bestCheckPointTimes;
    std::vector<GameObject> stageObjects;
};

// std::unordered_map< StageRank, std::string > stageRankNames = {
//     {StageRank::HYPER_S,   "HYPER-S"},
//     {StageRank::S,   "S"},
//     {StageRank::A,   "A"},
//     {StageRank::B,   "B"},
//     {StageRank::C,   "C"},
//     {StageRank::D,   "D"}
// };

// std::unordered_map< StageID, std::string > stageIDNames = {
//     {StageID::EMPTY,   "Null Stage"},
//     {StageID::INITIALIZATION,   "Initialization"},
//     {StageID::DIGITAL_STRETCH,   "Digital Stretch"},
//     {StageID::METROPOLIS,   "Metropolis"},
//     {StageID::HYPER_PLANT,   "Hyper Plant"},
//     {StageID::TROPICAL_RIG,   "Tropical Rig"}
// };