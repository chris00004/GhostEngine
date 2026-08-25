#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "debugger.h"
#include "inputManager.h"
#include "assetPakManager.h"
#include "renderManager.h"

#include "inputTypes.h"
#include "gameDataTypes.h"

#include "menuTypes.h"
#include "assetDataTypes.h"
#include "gameObject.h"


class GameManager{
    public:
        GameManager();
        void update();
        void draw( sf::RenderWindow& window );
        std::vector < GameObject* > getGameObjects() const;
        void loadMeshMap();

        enum class GameState{
            INIT,
            GAMELOOP,
            PAK_LOAD,
            CLEANUP
        };

    private: 

        GameState gameState;
        sf::VideoMode windowResolution;
        std::string windowTitle;

        //manager data structs
        PakData pakData;
        GameData gameData;
        Input input;
        MenuItem currentMenu;

        // First: create all sub managers 
        InputManager inputMgr;
        AudioManager audioMgr;

        // Second: create PAK manager ( needs pointers to sub managers )
        AssetPakManager pakMgr;

        // Third: create debugger
        Debugger debugMgr;
        
        std::chrono::steady_clock::time_point lastTime;
        float fps;
        float dt;

        bool paksLoaded = false;

        std::vector < GameObject* > gameObjects;

        //debug
        Timer debugDrawTimer = { 0.075f, 0.075f };
        std::optional<sf::Text> fpsText;

        sf::RectangleShape rect0;

        sf::CircleShape dot0;
        sf::CircleShape dot1;

        StageData s1;
        StageData s2;
        StageData s3;
};