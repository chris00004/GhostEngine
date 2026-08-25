#include "debugger.h"
#include "commonTypes.h"

//init defaults and unordered map
Debugger::Debugger( Input& input, PakData& pakData, GameData& gameData, const float& dt, const float& fps, 
                    InputManager& inputMgr ) 
                                                            : isActive ( false ),
                                                            debugState( DebugState::ENUM_START ),
                                                            input ( input ),
                                                            pakData ( pakData ),
                                                            selectedPak ( nullptr ),
                                                            isPakSwapped ( false ),
                                                            gameData ( gameData ),
                                                            dt ( dt ),
                                                            fps ( fps ),
                                                            inputMgr ( inputMgr )
                                                            {
    std::cout << "\nDebugMgr Constructed." << std::flush;
}


// INIT

void Debugger::init(){

    //index for traversing menus
    vecIndex = 0;

    //set up unordered map: debugState -> string
    debugStateNames = {
        { DebugState::ENUM_START, "Enum Start" },
        { DebugState::INPUT_TEST, "Input Test" },
        { DebugState::SOUND_TEST, "Sound Test" },
        { DebugState::GAMEDATA_VIEW, "Game Data View" },
        { DebugState::TEXTURES_VIEW, "Textures View" },
        { DebugState::STAGEDATA_VIEW, "Stage Data View" },
        { DebugState::DIALOGUES_VIEW, "Dialogues View" },
        { DebugState::ENUM_END, "Enum End" }
    };

    selectPakStruct ( pakData.global );

    //SF Circle & Vec2 -> setup position, radii, create shapes, set properties
    posJoystickDraw = { 180.0f, 180.0f };

    joystickEmbedRadius = 24.0f;
    joystickRadius = 3.0f;
    deadzoneRadius = input.deadzoneStick * joystickEmbedRadius;

    colorJoystickActive = sf::Color ( 180, 180, 180 );
    colorJoystickInactive = sf::Color ( 160, 30, 30 );

    circleJoystickEmbed.emplace( joystickEmbedRadius, 24 );
    circleDeadzone.emplace( joystickEmbedRadius, 24 );
    circleJoystick.emplace( joystickRadius, 8 );
    
    circleJoystickEmbed -> setFillColor ( sf::Color ( 60, 60, 60 ) );
    circleJoystickEmbed -> setOrigin ( { joystickEmbedRadius, joystickEmbedRadius } );
    circleJoystickEmbed -> setPosition ( posJoystickDraw );

    circleJoystick -> setFillColor ( sf::Color ( 255, 255, 255 ) );
    circleJoystick -> setOrigin ( { joystickRadius, joystickRadius } );
    circleJoystick -> setPosition ( posJoystickDraw );

    circleDeadzone -> setRadius ( deadzoneRadius );
    circleDeadzone -> setFillColor ( sf::Color ( 30, 30, 30 ) );
    circleDeadzone -> setOrigin ( { deadzoneRadius , deadzoneRadius } );
    circleDeadzone -> setPosition ( posJoystickDraw );


    //SF Font & Text -> load, color fill, scale
    sf::Font* tempFontPtr = findMapObject( selectedPak -> fonts, "test.otf" );
    if (tempFontPtr) {

        bodyText.emplace( *tempFontPtr, "...");
        fpsText.emplace( *tempFontPtr, "...");
        debugMenuText.emplace( *tempFontPtr, "...");
        popUpText.emplace( *tempFontPtr, "...");

        bodyText -> setFillColor( sf::Color ( 0, 255, 0 ) );
        bodyText -> setPosition( { 12.0f, 12.0f } );
        bodyText -> setScale( { 0.2f, 0.2f } );

        fpsText -> setFillColor( sf::Color ( 0, 255, 0 ) );
        fpsText -> setPosition( { 12.0f, 340.0f } );
        fpsText -> setScale( { 0.2f, 0.2f } );

        debugMenuText -> setFillColor( sf::Color ( 0, 255, 0 ) );
        debugMenuText -> setPosition( { 128.0f, 55.0f } );
        debugMenuText -> setScale( { 0.2f, 0.2f } );

        popUpText -> setFillColor( sf::Color ( 255, 0, 255 ) );
        popUpText -> setPosition( { 450.0f, 40.0f } );
        popUpText -> setScale( { 0.2f, 0.2f } );
    }
    else {
        
        std::cout << "tempFontPtr is Null" << "\n";
    }

    //safely get initial sound buffer
    sf::SoundBuffer* tempSoundPtr = findMapObject( selectedPak -> sounds, "test.wav" ); // soundsNames[ vecIndex ]
    if ( tempSoundPtr ) {
        
        debugSound.emplace( *tempSoundPtr );
    }
    else {
        
        std::cout << "tempSountPtr is Null" << "\n";
    }

    //safely get initial texture
    sf::Texture* tempTexturePtr = findMapObject ( selectedPak -> textures, "test.png" );
    if ( tempTexturePtr ) {

        debugSprite.emplace( *tempTexturePtr );
        debugSprite -> setPosition ( { 160.0f, 70.0f} );
        textureSize = sf::Vector2i( tempTexturePtr -> getSize() );
    }
    else {

        std::cout << "tempTexturePtr is Null" << "\n";
    }

    //keybind string
    keyBindString = "[ Enable/Disable ] \\    [ Accpet ] R-Shift    [ Next / Prev ] Arrows: Left / Right     [ Traverse Menu ] Arrows: Up / Down";
    keyBindString += "\n[ Pak Global ] P + 1    [ Pak Stage Common ]   P + 2    [ Pak Stage Current ]   P + 3";

    // Popup Text Timer
    timerPopUpText = { 1.5, 1.5 };

    //step out of init debug state
    setState ( DebugState::INPUT_TEST );
    std::cout << "\nDebugMgr Initialized." << std::flush;
}


// UPDATE

void Debugger::update(){
    
    // Keyboard debug input 
    updateDebugInputState( inputActivate, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Backslash ) );

    // Enable/disable debugger
    if ( inputActivate.pressed ) {
        
        isActive = !isActive;
    }

    // SAFETY GUARD: IS DEBUGGER ACTIVE
    if ( !isActive ) {
        
        return;
    }

    // Update Debugger Inputs
    updateDebugInput();

    //update debugState forward if next state + 1 isnt end enum
    if ( inputNextState.pressed ) { 
        
        setState ( ( DebugState )( enumToInt( debugState ) + 1 ) ); 
    }

    else if ( inputPrevState.pressed ) { 
        setState ( ( DebugState )( enumToInt( debugState ) - 1 ) ); 
    }

    // SAFETY GUARD: IS PAK LOADED
    if ( !isPakLoaded ) { 

        return; 
    }

    // Check for pak just swapped to display popup
    if ( isPakSwapped ) {

        timerUpdate ( timerPopUpText, dt );
        if ( timerIsDone ( timerPopUpText ) ) {
            
            isPakSwapped = false;
        }
    }

    switch(debugState) {
        
        case DebugState::ENUM_START: { 
            
            setState( ( DebugState ) ( enumToInt( DebugState::ENUM_END ) - 1 ) );  
        break; }
        
        case DebugState::INPUT_TEST: {

            if ( input.isJoystickUsed && circleJoystick -> getFillColor() != colorJoystickActive  ) 
                circleJoystick  -> setFillColor ( colorJoystickActive );

            else if ( !input.isJoystickUsed && circleJoystick -> getFillColor() != colorJoystickInactive ) 
                circleJoystick -> setFillColor ( colorJoystickInactive );

            circleJoystick -> setPosition ( { posJoystickDraw.x + input.joystickAxisX * 24.0f
                                        , posJoystickDraw.y - input.joystickAxisY * 24.0f } );

            //build input string every frame
            buildString ();
        break; }

        case DebugState::SOUND_TEST: {

            // SAFETY GUARD: IS VECTOR NOT EMPTY
            if ( soundsNames.empty() ) { break; }
            
            allowVectorControls( soundsNames.size() - 1 );

            sf::SoundBuffer* tempSoundPtr = findMapObject ( selectedPak -> sounds, soundsNames [ vecIndex ] );

            if (tempSoundPtr) {

                if ( inputDown.pressed || inputUp.pressed || isStateChanged ) {

                    debugSound -> setBuffer ( *tempSoundPtr );  

                    //rebuild sound string on new sound selected
                    buildString ();
                } 
                else if ( inputAccept.pressed ) {
                    
                    debugSound -> play();
                }
            }
        break; }

        case DebugState::GAMEDATA_VIEW: { break; }

        case DebugState::TEXTURES_VIEW: {

            // SAFETY GUARD: IS VECTOR NOT EMPTY
            if ( texturesNames.empty() ) break;
            
            allowVectorControls( texturesNames.size() - 1 );

            if ( inputDown.pressed || inputUp.pressed || isStateChanged ) {

                sf::Texture* tempTexturePtr = findMapObject ( selectedPak -> textures, texturesNames [ vecIndex ] );
                if (tempTexturePtr) {

                    //get texture size
                    textureSize = sf::Vector2i( tempTexturePtr -> getSize() );

                    //set sprite to texture
                    debugSprite -> setTexture ( *tempTexturePtr );

                    //resize sprites tex rect to texture size
                    debugSprite -> setTextureRect( sf::IntRect( { 0, 0 }, textureSize ) );

                    //rebuild texture string on new texture selected
                    buildString ();
                }
            }                        
        break; }

        case DebugState::STAGEDATA_VIEW: {

            // SAFETY GUARD: IS VECTOR NOT EMPTY
            if ( gameData.stages.empty() ) break;
            
            //enable menu controls
            allowVectorControls( gameData.stages.size() - 1 );

            if ( inputDown.pressed || inputUp.pressed || isStateChanged ) {

                //rebuild stage data string on new stage selected
                buildString ();
            }
        break; }

        case DebugState::DIALOGUES_VIEW: {

            // SAFETY GUARD: IS VECTOR NOT EMPTY
            if ( dialoguesNames.empty() ) break;
         
            //enable menu controls
            allowVectorControls( dialoguesNames.size() - 1 );

            //get current dialogue entry
            if ( inputDown.pressed || inputUp.pressed || isStateChanged ) {

                std::vector< std::string >* tempStringVecPtr = findMapObject ( selectedPak -> dialogues, dialoguesNames [ vecIndex ] );
                if (tempStringVecPtr) {

                    dialogueEntry = *tempStringVecPtr;

                    //rebuild dialogue string on new dialogue selected
                    buildString ();
                }
            }   
            
        break; }

        case DebugState::ENUM_END: { 
            
            setState( ( DebugState ) ( enumToInt( DebugState::ENUM_START ) + 1 ) ); 
        break; }
    }

    fpsText -> setString ( std::to_string( fps ) );

    if ( isStateChanged ) {
        
        isStateChanged = false;
    }

    //switch selected pak struct, after state changes check so string rebuild triggers
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::P ) ) {

        if ( inputNum1.pressed ) { 

            selectPakStruct( pakData.global );
            isPakSwapped = true;
            timerReset ( timerPopUpText );
            popUpText -> setString( "NOTICE -> Loaded Pak : GLOBAL" );
        }

        else if ( inputNum2.pressed ) { 

            selectPakStruct( pakData.stageCommon );
            isPakSwapped = true;
            timerReset ( timerPopUpText );
            popUpText -> setString( "NOTICE -> Loaded Pak : STAGE COMMON" );
        }

        else if ( inputNum3.pressed ) { 

            selectPakStruct( pakData.stageCurrent );
            isPakSwapped = true;
            timerReset ( timerPopUpText );
            popUpText -> setString( "NOTICE -> Loaded Pak : STAGE CURRENT" );
        }
    }
}



// DRAW 

void Debugger::draw( sf::RenderWindow& window ) {
    
    if ( !isActive ) return;

    window.draw( *bodyText );
    window.draw( *fpsText );

    if ( isPakSwapped ) {
        window.draw( *popUpText );
    }

    switch(debugState) {

        case DebugState::ENUM_START:
        break;

        case DebugState::INPUT_TEST:

            window.draw ( *circleJoystickEmbed );
            window.draw ( *circleDeadzone );
            window.draw ( *circleJoystick );
        break;

        case DebugState::SOUND_TEST:
        break;

        case DebugState::TEXTURES_VIEW:

            window.draw ( *debugMenuText );
            window.draw ( *debugSprite );
        break;

        case DebugState::GAMEDATA_VIEW:
        break;

        case DebugState::STAGEDATA_VIEW:

            window.draw ( *debugMenuText );
        break;

        case DebugState::DIALOGUES_VIEW:

            window.draw ( *debugMenuText );
        break;

        case DebugState::ENUM_END:
        break;
    }
    
}


// UPDATE INPUT STATE

void Debugger::updateDebugInputState( InputState& inputState, bool isDownNow )
{
    //store last frame
    inputState.prevHeld = inputState.held;   

    //if input down -> held is true
    inputState.held = isDownNow;

    //if input down and was up last frame -> pressed is true
    inputState.pressed  = inputState.held && !inputState.prevHeld;

    //if input up and was down last frame -> released is true
    inputState.released = !inputState.held && inputState.prevHeld;
}

// UPDATE ALL DEBUG MENU INPUTS

void Debugger::updateDebugInput() {

    updateDebugInputState( inputAccept, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::RShift ) );
    updateDebugInputState( inputBack, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::RControl ) );
    updateDebugInputState( inputNextState, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Right ) );
    updateDebugInputState( inputPrevState, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Left ) );
    updateDebugInputState( inputUp, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Up ) );
    updateDebugInputState( inputDown, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Down ) );
    updateDebugInputState( inputNum1, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num1 ) );
    updateDebugInputState( inputNum2, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num2 ) );
    updateDebugInputState( inputNum3, sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num3 ) );
}

// CREATE INPUT STRING

std::string Debugger::createInputString ( InputState& inputState )
{
    return "\n[ "+ inputMgr.getInputName( &inputState ) + " ]"
            + " Held:" + std::to_string(inputState.held)
            + ", Pressed:" + std::to_string(inputState.pressed)
            + ", Released:" + std::to_string(inputState.released)
            + ", Buffer_Active:" + std::to_string(inputState.bufferActive);
}

// ENABLE MENU CONTROLS

void Debugger::allowVectorControls( int endVal )
{
    //increment / decrement
    if (inputDown.pressed) vecIndex ++;
    if (inputUp.pressed) vecIndex --;

    //loop menu
    if ( vecIndex < 0 ) vecIndex = endVal;
    if ( vecIndex > endVal ) vecIndex = 0;
}

// SELECT PAK STRUCT

void Debugger::selectPakStruct( Pak& pak )
{
    isPakLoaded = false;

    std::cout << "\nSelecting new pak." << std::flush;
    selectedPak = &pak;
    std::cout << "\nNew pak selected" << std::flush;

    std::cout << "\nClearing all names vectors" << std::flush;
    //claer all vectors
    texturesNames.clear();
    soundsNames.clear();
    fontsNames.clear();
    dialoguesNames.clear();
    std::cout << "\nName vectors cleared." << std::flush;

    std::cout << "\nLoad pak data names into names vectors." << std::flush;
    //load all pakData names into vectors
    if ( !pak.textures.empty() ) for ( const auto& pair : pak.textures ) { texturesNames.push_back( pair.first ); }
        else std::cout << "\npak.textures empty." << std::flush;
        
    if ( !pak.sounds.empty() ) for ( const auto& pair : pak.sounds ) { soundsNames.push_back( pair.first ); }
        else std::cout << "\npak.sounds empty." << std::flush;

    if ( !pak.fonts.empty() ) for ( const auto& pair : pak.fonts ) { fontsNames.push_back( pair.first ); }
        else std::cout << "\npak.fonts empty." << std::flush;

    if ( !pak.dialogues.empty() ) for ( const auto& pair : pak.dialogues ) { dialoguesNames.push_back( pair.first ); }
        else std::cout << "\npak.dialogues empty." << std::flush;

    std::cout << "\nPak data names loaded into names vectors" << std::flush;

    std::cout << "\nCompleting pak loading." << std::flush;
    isPakLoaded = true;
    std::cout << "\nPak loading complete." << std::flush;
    isStateChanged = true;
}

    
// SET STATE

void Debugger::setState( DebugState debugState )
{
    this -> debugState = debugState;
    vecIndex = 0;
    isStateChanged = true;
    buildString ();
}


// BUILD STRING

void Debugger::buildString()
{
    //setup body string 
    bodyString = keyBindString + "\n\n"
                + "Menu: " + debugStateNames.find( debugState ) -> second + "\n";

    switch( debugState )
    {
        case DebugState::INPUT_TEST: {

            bodyString += 
                createInputString( input.actionA )
                + createInputString( input.actionB )
                + createInputString( input.actionX )
                + createInputString( input.actionY )
                + createInputString( input.actionLB )
                + createInputString( input.actionRB )
                + createInputString( input.actionLT )
                + createInputString( input.actionRT )
                + createInputString( input.dirPadLeft )
                + createInputString( input.dirPadUp )
                + createInputString( input.dirPadRight )
                + createInputString( input.dirPadDown )
                + "\n\n\n Joystick Active: " + std::to_string( input.isJoystickUsed )
                + "\n[ Left-Stick ]\nX:" 
                    + std::to_string( input.joystickAxisX )
                    + "\nY:" + std::to_string( input.joystickAxisY )
                + "\nInputDirection: " + std::to_string( input.direction )
                ;
        break; }

        case DebugState::SOUND_TEST:{

            // SAFETY GUARD
            if ( soundsNames.empty() ) {

                bodyString += "\nNo Sounds Data.";
                break;
            }
            
            // build sound string
            for ( int i = 0; i < soundsNames.size(); i++ ) {

                //fill bodystring with filenames
                if ( i == vecIndex ) bodyString += "\n->" + soundsNames[i];
                else bodyString += "\n" + soundsNames[i];
            }

        break;}

        case DebugState::TEXTURES_VIEW:{

            // SAFETY GUARD
            if ( texturesNames.empty() ){
                bodyString += "\nNo Textures Data.";
                break;
            }

            // build texture string
            for ( int i = 0; i < texturesNames.size(); i++ ) {

                //fill bodystring with filenames
                if (i == vecIndex) bodyString += "\n->" + texturesNames[i];
                else bodyString += "\n" + texturesNames[i];
            }
            debugMenuString = "Texture Size: { " + std::to_string( textureSize.x ) + ", " + std::to_string( textureSize.y ) + " }";

        break;}

        case DebugState::GAMEDATA_VIEW: {
            bodyString += 
                "\n [firstLaunch] " + std::to_string( gameData.firstLaunch )
                + "\n [totalHFuel] " + std::to_string( gameData.totalHFuel)
                + "\n\n [resolutionX] " + std::to_string( gameData.settings.display.x )
                + "\n [resolutionY] " + std::to_string( gameData.settings.display.y )
                + "\n [windowTitle] " + gameData.settings.display.windowTitle
                + "\n\n [volumeMaster] " + std::to_string( gameData.settings.volume.master )
                + "\n [volumeMusic] " + std::to_string( gameData.settings.volume.music )
                + "\n [volumeSfx] " + std::to_string( gameData.settings.volume.sfx )
                ;
        break;}

        case DebugState::STAGEDATA_VIEW: {

            // SAFETY GUARD
            if ( gameData.stages.empty() ){
                bodyString += "\nNo Stage Data.";
                break;
            }

            //draw body list of stages
            for ( int i = 0; i < gameData.stages.size(); i++ ) {

                //fill bodystring with filenames
                if (i == vecIndex) bodyString += "\n -> " + gameData.stages[i].name;
                else bodyString += "\n" + gameData.stages[i].name;
            }

            //current stage
            StageData stage = gameData.stages[ vecIndex ];

            // stage data string fill out
            debugMenuString = 
                "[ Unlocked ]  " + std::to_string ( stage.unlocked )
                + "\n[ Best Time ]  " + std::to_string( stage.bestTime ) 
                + "\n[ Best Checkpoint Times ]  "; 
                
            //loop thru best checkpt times
            if ( stage.bestCheckPointTimes.empty() ) {

                for ( int i = 0; i < stage.bestCheckPointTimes.size(); i++ ) {

                    debugMenuString += "\n\t" + std::to_string( stage.bestCheckPointTimes[ i ] );
                }
            }
            else debugMenuString += "\n\tN/A";

            //highest rank
            debugMenuString += "\n[ Highest Rank ]  " + std::to_string( static_cast<int>( stage.rank ) )
                            + "\n[ Rank Time Requirements ]  ";

            // get count of all possible ranks
            stageRanksCount = sizeof ( stage.rankTimeRequirements )
                                / sizeof ( stage.rankTimeRequirements[0] );

            for ( int i = 0; i < stageRanksCount; i++ ) {

                debugMenuString += "\n\tRank " + std::to_string( i )
                                + " - " + std::to_string( stage.rankTimeRequirements[i] );
            }
            

        break;}

        case DebugState::DIALOGUES_VIEW:{

            // SAFETY GUARD
            if ( dialoguesNames.empty() ) {

                bodyString += "\nNo Dialogues Data.";
                break;
            }
            
            //draw body list of stages
            for ( int i = 0; i < dialoguesNames.size(); i++ ) {

                //fill bodystring with filenames
                if (i == vecIndex) bodyString += "\n -> " + dialoguesNames[i];
                else bodyString += "\n" + dialoguesNames[i];
            }

            //loop thru entry lines, add to string
            debugMenuString = "";
            for ( int i = 0; i < dialogueEntry.size(); i++ ) {

                debugMenuString += "\n" + std::to_string(i) + ". " + dialogueEntry[ i ];
            }

        break;}
    }

    if ( bodyText ) {
        
        bodyText -> setString( bodyString );
    }

    if ( debugMenuText ) {
        
        debugMenuText -> setString ( debugMenuString );
    }

    std::string* tempStateString = &debugStateNames.find( debugState ) -> second;

    if ( tempStateString ) {
        
        std::cout << "body string updated: " << *tempStateString << std::endl;
    }
}

