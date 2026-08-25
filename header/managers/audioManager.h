#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include "assetDataTypes.h"
#include "audioTypes.h"
#include "soundContainer.h"
#include "inputTypes.h"

class AudioManager
{
public:
    AudioManager( const PakData& pakData, const float& dt, const Input& input );
    void init();
    void update();

    SoundContainer* setupAndRetriveNewSound ( SoundID soundId );
    
    void loadSoundData ( const Pak& pak );
    void removeSoundData ( const Pak& pak );

    void playSound2D( SoundID id, bool isLooping );
    void playSound3D( SoundID id, Vec3* position, bool isLooping );
    void playSound3DMoving( SoundID id, Vec3* position, Vec3* speed, bool isLooping, bool isDoppler );

    


private:

    //Camera& camera;
    const PakData& pakData;
    const float& dt;
    const Input& input;

    bool isActive;
    int poolSize;
    
    //pre-fill
    std::unordered_map< std::string, SoundID > stringToSoundIDMap;
    std::unordered_map< SoundID, SoundProperties > soundIdToPropertiesMap;

    //fill on load sound data
    std::unordered_map< SoundID, const sf::SoundBuffer* > soundIdToBufferPtrMap;

    std::array< SoundContainer, 32 > soundArray;
};