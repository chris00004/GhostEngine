#pragma once

#include "audioTypes.h"
#include "commonTypes.h"
#include "assetDataTypes.h"
#include <iostream>

class SoundContainer{
    public:
        SoundContainer ();
        void init ( const sf::SoundBuffer* tempBufferPtr, int containerId );
        void update ();

        void playSound ();

        //setters
        void setBuffer ( const sf::SoundBuffer* bufferPtr );
        void setProperties ( const SoundProperties* propertiesPtr );
        void setAudio3D ( bool is3D );
        void setLooping ( bool isTrue );

        //getters
        const bool getIsReady();
        const std::string getName();
        
    private:

        int containerId;
        bool isReady;
        bool is3D;
        bool isMoving;
        bool isLooping;
        bool isDoppler;

        Vec3* position;
        Vec3* speed;

        std::string name;
        std::optional < sf::Sound > sound;
};