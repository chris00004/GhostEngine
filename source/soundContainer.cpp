#include "soundContainer.h"

SoundContainer::SoundContainer() : isReady ( false ),
                                    is3D ( false ),
                                    isMoving ( false ),
                                    isLooping ( false ),
                                    isDoppler ( false ),
                                    position ( nullptr ),
                                    speed ( nullptr ),
                                    name ( "Null Sound" )
{}

void SoundContainer::init( const sf::SoundBuffer* tempBufferPtr, int containerId )
{
    if ( tempBufferPtr )
    {
        sound.emplace( *tempBufferPtr );
        this -> containerId = containerId;

        std::cout << "Sound Container [ " << containerId << " ] initialized.\n";
    }
    else std::cout << "Sound Container [ " << containerId << " ] is null.\n";
}

void SoundContainer::update()
{
    if ( sound -> getStatus() == sf::Sound::Status::Stopped && !isReady ){
        isReady = true;
        std::cout << "Sound Container [ " << containerId << " ] sound status = stopped. is ready = " << isReady << "\n";
    }
}

void SoundContainer::setBuffer ( const sf::SoundBuffer* bufferPtr ){
    sound -> setBuffer( *bufferPtr );
}

void SoundContainer::setProperties ( const SoundProperties* propertiesPtr )
{
    name = propertiesPtr -> name;
    sound -> setVolume( propertiesPtr -> volume );
    sound -> setPitch( propertiesPtr -> pitch );
    sound -> setDopplerFactor( propertiesPtr -> dopplerFactor );
    sound -> setMinDistance( propertiesPtr -> minDistance );
    sound -> setMaxDistance( propertiesPtr -> maxDistance );
    sound -> setAttenuation( propertiesPtr -> attenuation );
}

void SoundContainer::setLooping ( bool isTrue ){
    if ( sound ){
        if ( sound -> isLooping() != isTrue ){

            isLooping = isTrue;
            sound -> setLooping ( isLooping );
        }
    }
}

void SoundContainer::setAudio3D( bool isTrue ){
    if ( sound ){
        if ( sound -> isSpatializationEnabled() != isTrue ){

            is3D = isTrue;
            sound -> setSpatializationEnabled ( is3D );
        }
    }
}

void SoundContainer::playSound(){
    if ( isReady ) {
        sound -> play();
        isReady = false;
        std::cout << "Sound Container [ " << containerId << " ] sound status = playing. is ready = " << isReady << "\n";
    }
    //else std::cout << "Sound Container [ " << containerId << " ] is ready = " << isReady << "\n";
}

const bool SoundContainer::getIsReady() { return isReady; } 

const std::string SoundContainer::getName() { return name; }