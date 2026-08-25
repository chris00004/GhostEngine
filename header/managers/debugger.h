#pragma once

#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "inputTypes.h"
#include "gameDataTypes.h"
#include "commonTypes.h"

#include "inputManager.h"
#include "assetDataTypes.h"

class Debugger
{
public:
    Debugger( Input& input, PakData& pakData, GameData& gameData, 
                const float& dt, const float& fps, InputManager& inputMgr );
    void init();
    void update();
    void draw( sf::RenderWindow& window );

private:
    enum class DebugState{
        ENUM_START,
        INPUT_TEST,
        SOUND_TEST,
        GAMEDATA_VIEW,
        TEXTURES_VIEW,
        STAGEDATA_VIEW,
        DIALOGUES_VIEW,
        ENUM_END
    };

    enum class SelectedPak{
        PakGlobal,
        PakStageCommon,
        PakCurrentStage
    };

    DebugState debugState;
    bool isStateChanged = false;

    bool isActive;
    bool isPakLoaded;
    int vecIndex;
    int stageRanksCount;

    sf::Vector2i textureSize;
    
    std::unordered_map< DebugState, std::string > debugStateNames;

    const float& dt;
    const float& fps;

    Input& input;
    GameData& gameData;
    PakData& pakData;
    InputManager& inputMgr;

    bool isPakSwapped;
    Pak* selectedPak;
    
    std::optional <sf::Text> bodyText;
    std::optional <sf::Text> fpsText;
    std::optional <sf::Text> debugMenuText;
    std::optional <sf::Text> popUpText;

    Timer timerPopUpText;

    std::optional <sf::Sprite> debugSprite;
    std::optional <sf::Sound> debugSound;

    std::vector<std::string> dialogueEntry;

    // INPUT_TEST related
    float joystickEmbedRadius;
    float joystickRadius;
    float deadzoneRadius;

    sf::Color colorJoystickActive;
    sf::Color colorJoystickInactive;

    sf::Vector2f posJoystickDraw;
    std::optional <sf::CircleShape> circleJoystickEmbed;
    std::optional <sf::CircleShape> circleJoystick;
    std::optional <sf::CircleShape> circleDeadzone;

    std::vector< std::string > texturesNames;
    std::vector< std::string > soundsNames;
    std::vector< std::string > fontsNames;
    std::vector< std::string > dialoguesNames;

    std::string keyBindString = "";
    std::string bodyString = "";
    std::string debugMenuString = "";

    //keyboard nav
    InputState inputActivate;
    InputState inputNextState;
    InputState inputPrevState;
    InputState inputAccept;
    InputState inputBack;
    InputState inputUp;
    InputState inputDown;
    InputState inputNum1;
    InputState inputNum2;
    InputState inputNum3;

    void updateDebugInputState( InputState& inputState, bool isDownNow );
    std::string createInputString( InputState& inputState );
    void allowVectorControls( int endVal );
    void setState( DebugState debugState );

    void buildString();
    void selectPakStruct( Pak& pak ); 
    void updateDebugInput();
    
};