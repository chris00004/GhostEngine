#include "gameManager.h"

GameManager::GameManager() :gameState ( GameState::INIT ),
                            lastTime ( std::chrono::high_resolution_clock::now() ),
                            audioMgr( pakData, dt, input ),
                            inputMgr( input, dt ),
                            debugMgr ( input, pakData, gameData, dt, fps, inputMgr )
                            {
    //by this point: managers initialized, gameState set to INIT,
}

void GameManager::update()
{

    // DELTA TIME
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = now - lastTime;
    lastTime = now;
    dt = delta.count(); 
    fps = 1.0f / dt;

    switch ( gameState )
    {
        case GameState::INIT:{

            std::cout << "\nGameMgr INIT begin." << std::flush;

            gameData.stages.push_back ( s1 );
            gameData.stages.push_back ( s2 );
            gameData.stages.push_back ( s3 );


            //load game assets paks
            //pakMgr.init( x, y, z, etc... );
            pakMgr.load( "global-test.pak" );
            pakMgr.buildObjects( pakData.global );

            pakMgr.load( "stage-common-test.pak" );
            pakMgr.buildObjects( pakData.stageCommon );
            
            pakMgr.load( "stage-0-test.pak" );
            pakMgr.buildObjects( pakData.stageCurrent );

            // pakMgr.load( "poop.fart" );
            // pakMgr.buildObjects( pakData.stageCurrent );

            inputMgr.init();
            audioMgr.init();

            //init debugger
            debugMgr.init();

            //verify music files


            //load gameData file and overwrite


            //local things
            sf::Font* tempFontPtr = findMapObject( pakData.global.fonts, "test.otf" );
            if (tempFontPtr) 
            {
                fpsText.emplace ( *tempFontPtr, "..." );
                fpsText -> setPosition ( { 580.0f, 20.0f } );
                fpsText -> setScale ( { 0.2f, 0.2f } );
            }

            //move into gameloop
            gameState = GameState::GAMELOOP;

        break;}

        case GameState::GAMELOOP:{

            //run all objs update loop
            inputMgr.update();
            audioMgr.update();
            debugMgr.update();

            //debug fps text
            debugDrawTimer.current -= dt;
            if ( debugDrawTimer.current < 0.0f ){
                fpsText -> setString ( std::to_string( fps ) );
                debugDrawTimer.current = debugDrawTimer.base;
            }
        break;}

        case GameState::CLEANUP:{
            //garbage collection
        break;}
    }
}

void GameManager::draw( sf::RenderWindow& window ){
    debugMgr.draw ( window );
    window.draw ( *fpsText );
}