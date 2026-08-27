#pragma once

#include "SFML/Window.hpp"

#include <windows.h>
#include "Xinput.h"
#include "inputTypes.h"

#include <string>
#include <unordered_map>

class InputManager{
    public:
        InputManager( Input& input, const float& dt );
        void init();
        void update();
        const std::string getInputName( InputState* key );
        const float getInputDir();
        

    private:

        bool isActive;

        //to be passed in by game manager
        const float& dt;
        Input& input;

        //key and gamepad maps
        InputMap mapKb;
        InputMap mapGp;

        //unorderd map, maps a name string to its input state
        std::unordered_map< InputState*, std::string > inputNames;

        //XInput
        XINPUT_STATE xInputState{};
        bool xInputConnected = false;

        //functions
        void updateInputState( InputState& inputState, bool isDownNow );
        void resetInputBuffer( InputState& inputState );
        void calculateInputDir( Input& input );

        void updateGamepadInputMap();
        void updateKeyboardInputMap();
        void processInputs();
};