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

#include "gameManager.h"
#include "inputTypes.h"


//RUN W/ [F5] FOR JSONS TO APPLY!!!

int main()
{
    /* SFML */
    sf::VideoMode internalResolution ( { 640, 360 } );
    sf::VideoMode hdResolution ( { 1920, 1080 } );
    sf::RenderWindow window( hdResolution, "PROJECT SPARR-0", sf::State::Windowed ); //sf::VideoMode::getDesktopMode()

    sf::View view( sf::FloatRect( {0.f, 0.f}, {640.0f, 360.0f} ) );
    window.setView(view);
    //window.setVerticalSyncEnabled( true );

    std::cout << "Window Created." << std::flush;
    GameManager gameManager;
    std::cout << "\nGameMgr Created." << std::flush;

    
    //PROGRAM IS RUNNING
    while ( window.isOpen() )
    {
        //EVENTS
        while ( const std::optional event = window.pollEvent() )
        {
            
            if ( event -> is <sf::Event::Closed>() )
                window.close();
        }

        gameManager.update();
        
        //DRAWING
        window.clear(sf::Color(0, 0, 0));

        gameManager.draw( window );

        window.display();
    }

    return 0;
}