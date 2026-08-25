
#include "inputManager.h"
#include <iostream>

InputManager::InputManager( Input& input, const float& dt ) : dt( dt ),
                                                        input( input ),
                                                        isActive ( false )
                                                        {
    
    inputNames = {
        { &input.dirPadLeft, "Left" },
        { &input.dirPadUp, "Up" },
        { &input.dirPadRight, "Right" },
        { &input.dirPadDown, "Down" },
        { &input.actionA, "Action A" },
        { &input.actionB, "Action B" },
        { &input.actionX, "Action X" },
        { &input.actionY, "Action Y" },
        { &input.actionLB, "Action LB" },
        { &input.actionRB, "Action RB" },
        { &input.actionLT, "Action LT" },
        { &input.actionRT, "Action RT" },
        { &input.actionStart, "Start" },
        { &input.actionSelect, "Select" }
    };
    std::cout << "\nInputMgr Construct." << std::flush;
}

void InputManager::init() {

    isActive = true;
}

void InputManager::update() {
    
    if ( !isActive ) return;

    //get xinput state
    xInputConnected = XInputGetState( 0, &xInputState ) == ERROR_SUCCESS;
    
    //read gamepad input if connected
    if ( !xInputConnected ) {
        
        mapGp = {};
    }
    else {

        //read inputs into mapGamepad
        mapGp.actionA = ( xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A );
        mapGp.actionB = ( xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_B );
        mapGp.actionX = ( xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_X );
        mapGp.actionY = ( xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y );

        mapGp.actionLB = ( xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER );
        mapGp.actionRB = ( xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER );

        //do threshold check
        float ltThreshold  = xInputState.Gamepad.bLeftTrigger / 255.0f;
        float rtThreshold = xInputState.Gamepad.bRightTrigger / 255.0f;

        mapGp.actionLT = (ltThreshold > input.deadzoneTrigger);
        mapGp.actionRT = (rtThreshold > input.deadzoneTrigger);

        mapGp.dirPadLeft = (xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
        mapGp.dirPadUp = (xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
        mapGp.dirPadRight = (xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
        mapGp.dirPadDown = (xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);

        mapGp.actionStart = (xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
        mapGp.actionSelect = (xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
    }

    //read inputs into mapKeyboard
    mapKb.actionA = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    mapKb.actionB = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L);
    mapKb.actionX = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J);
    mapKb.actionY = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I);

    mapKb.actionLB = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    mapKb.actionRB = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    mapKb.actionLT = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    mapKb.actionRT = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
    
    mapKb.dirPadLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    mapKb.dirPadUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    mapKb.dirPadRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    mapKb.dirPadDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

    mapKb.actionStart = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    mapKb.actionSelect = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab);

    //get gamepad left stick x,y axis (-1.0, 1.0)
    input.joystickAxisX = xInputState.Gamepad.sThumbLX / 32767.0f; //normalize axis val
    input.joystickAxisY = xInputState.Gamepad.sThumbLY / 32767.0f; //normalize axis val

    //check if left stick passes deadzone -> is being used
    input.isJoystickUsed = std::abs(input.joystickAxisX) > input.deadzoneStick || 
                            std::abs(input.joystickAxisY) > input.deadzoneStick;

    //update input states
    //face buttons
    updateInputState( input.actionA, mapGp.actionA || mapKb.actionA);
    updateInputState( input.actionB, mapGp.actionB || mapKb.actionB);
    updateInputState( input.actionX, mapGp.actionX || mapKb.actionX);
    updateInputState( input.actionY, mapGp.actionY || mapKb.actionY);

    //bumpers + triggers
    updateInputState( input.actionLB, mapGp.actionLB || mapKb.actionLB);
    updateInputState( input.actionRB, mapGp.actionRB || mapKb.actionRB);
    updateInputState( input.actionLT, mapGp.actionLT || mapKb.actionLT);
    updateInputState( input.actionRT, mapGp.actionRT || mapKb.actionRT);

    //dpad
    updateInputState( input.dirPadLeft, mapGp.dirPadLeft || mapKb.dirPadLeft);
    updateInputState( input.dirPadUp, mapGp.dirPadUp || mapKb.dirPadUp);
    updateInputState( input.dirPadRight, mapGp.dirPadRight || mapKb.dirPadRight);
    updateInputState( input.dirPadDown, mapGp.dirPadDown || mapKb.dirPadDown);

    //start + select
    updateInputState( input.actionStart, mapGp.actionStart || mapKb.actionStart);
    updateInputState( input.actionSelect, mapGp.actionSelect || mapKb.actionSelect);

    //calulate input dir
    calculateInputDir( input );
}

void InputManager::resetInputBuffer( InputState& inputState ) {

    inputState.alarmBuffer.current = inputState.alarmBuffer.base;
    inputState.bufferActive = false;
}

void InputManager::updateInputState( InputState& inputState, bool isDownNow ) {

    //store last frame
    inputState.prevHeld = inputState.held;   

    //if input down -> held is true
    inputState.held = isDownNow;

    //if input down and was up last frame -> pressed is true
    inputState.pressed = inputState.held && !inputState.prevHeld;

    //if input up and was down last frame -> released is true
    inputState.released = !inputState.held && inputState.prevHeld;

    //input buffer trigger
    if ( inputState.pressed ) {

        inputState.alarmBuffer.current = inputState.alarmBuffer.base;
        inputState.bufferActive = true;
    }

    //input buffer update
    if ( inputState.bufferActive ) {

        inputState.alarmBuffer.current -= dt;
        if ( inputState.alarmBuffer.current <= 0 ) {
            
            inputState.alarmBuffer.current = 0.0f;
            inputState.bufferActive = false;
        }
    }
}

void InputManager::calculateInputDir( Input& input ) {

    //movement left stick
    if ( input.isJoystickUsed ) { 
        
        input.direction = std::atan2( input.joystickAxisY, input.joystickAxisX );
    }

    //movement keyboard / dpad
    else {
        
        int dirInputX = ( input.dirPadRight.held ) - ( input.dirPadLeft.held );
        int dirInputY = ( input.dirPadDown.held ) - ( input.dirPadUp.held );

        //calculate direction of input 
        if (dirInputX != 0 || dirInputY != 0) 
            input.direction = std::atan2( dirInputY, dirInputX );
    }
}

const std::string InputManager::getInputName( InputState* key ) { 
    auto name = inputNames.find(key);
    if (name != inputNames.end()) return name -> second;
    return "Null Input";
}

