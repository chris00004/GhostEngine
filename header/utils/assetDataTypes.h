#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//enum class PakSlot { Global, StageCommon, StageCurrent };

// holds all data for a specific section of game, EX: global, stage common, stage current
struct Pak{
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, std::vector<char>> rawFontBuffers;
    std::unordered_map<std::string, std::vector<std::string>> dialogues;
};

// holds all pak structs
struct PakData
{
    Pak global;
    Pak stageCommon;
    Pak stageCurrent;
};