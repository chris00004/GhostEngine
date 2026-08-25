#include "audioManager.h"

AudioManager::AudioManager( const PakData& pakData, const float& dt, const Input& input ) : dt ( dt ),
                                                                                            pakData ( pakData ),
                                                                                            input ( input )
{ }

void AudioManager::init()
{ 
    //[ string -> soundId ] definitions
    stringToSoundIDMap.insert ( { "test.wav", SoundID::TEST } );

    //[ soundId -> property ] definitions
    SoundProperties testSoundProperties; 
    testSoundProperties.name = "Test Sound";

    soundIdToPropertiesMap.insert ( { SoundID::TEST, testSoundProperties } );

    //load sound buffer ptrs
    loadSoundData( pakData.global );

    //by this point: 
    //  all sound name strings mapped to sound Ids
    //  all sound Ids mapped to sound properties

    //ensure up vector is -z upward
    sf::Listener::setUpVector( { 0, 0, -1 } );

    //top down camera, fixed direction
    sf::Listener::setDirection( { 0, 1, 0 } );

    const sf::SoundBuffer* tempBufferPtr = findMapObject ( pakData.global.sounds, "test.wav" );
    if ( !tempBufferPtr ) std::cout << "AudioMgr: tempBufferPtr is null\n";

    poolSize = soundArray.size();

    for ( int i = 0; i < poolSize; i++ )
    {
        SoundContainer& soundContainer = soundArray[ i ]; 
        soundContainer.init( tempBufferPtr, i );
    }

    std::cout << "AudioMgr initialized.\n";
}

SoundContainer* AudioManager::setupAndRetriveNewSound ( SoundID soundId ){
    /*
        1. find available sound
        2. set new buffer
        3. set new properties
    */

    for ( int i = 0; i < poolSize; i++ )
    {
        SoundContainer* soundContainerPtr = &soundArray[ i ]; 
        if ( !soundContainerPtr ) return nullptr;

        if ( soundContainerPtr -> getIsReady() ){

            const sf::SoundBuffer* newBufferPtr = *findMapObject ( soundIdToBufferPtrMap, soundId );

            if ( newBufferPtr ) soundContainerPtr -> setBuffer ( newBufferPtr );
            else {
                std::cout << "No buffer mapped to this SoundID in soundIdToBufferPtrMap.\n";
                return nullptr;
            }

            const SoundProperties* newPropertiesPtr = findMapObject ( soundIdToPropertiesMap, soundId );
            if ( newPropertiesPtr ) soundContainerPtr -> setProperties ( newPropertiesPtr );
            else {
                std::cout << "No sound properties mapped to this SoundID in soundIdToPropertiesMap.\n";
                return nullptr;
            }

            //if valid ptr & successfully applied buffer & properties return ptr
            return soundContainerPtr;
        }
    }
    return nullptr;
}

void AudioManager::playSound2D( SoundID soundId, bool isLooping ){

    SoundContainer* soundContainerPtr = setupAndRetriveNewSound ( soundId );
    if ( !soundContainerPtr ) return;

    soundContainerPtr -> setAudio3D ( false );
    soundContainerPtr -> setLooping ( isLooping );
    soundContainerPtr -> playSound ();
}

void AudioManager::update(){

    //sf::Listener::setPosition({x, y, z});
    //sf::Listener::setDirection({dx, dy, dz});

    for ( int i = 0; i < poolSize; i++ )
    {
        soundArray[ i ].update();
    }

    if ( input.actionA.pressed ) playSound2D( SoundID::TEST, false );
}

void AudioManager::loadSoundData ( const Pak& pak )
{
    //loop thru pak's sounds map
    for ( const auto &pair : pak.sounds )
    {
        //grab name and pointer to buffer
        const std::string name = pair.first;
        const sf::SoundBuffer* bufferPtr = &pair.second;

        //use name to get soundID
        SoundID* soundIDPtr = findMapObject ( stringToSoundIDMap, name );

        //safety check on soundID ptr
        if ( !soundIDPtr ){
            std::cout << "\"" << name << "\"" << " does not point to a valid soundID. Skipping entry.\n";
            continue;
        }

        //use ID as key mapping to sound buffer
        soundIdToBufferPtrMap.insert ( { *soundIDPtr, bufferPtr } );
        std::cout << "\"" << name << "\"" << " succesfully mapped to a valid soundID.\n";
    }
}

void AudioManager::removeSoundData ( const Pak& pak )
{
    //loop thru pak's sounds map
    for ( const auto &pair : pak.sounds )
    {
        std::string name = pair.first;

        //use name to get soundID
        SoundID* soundIDPtr = findMapObject ( stringToSoundIDMap, name );

        //safety check on soundID ptr
        if ( !soundIDPtr ){
            std::cout << "\"" << name << "\"" << " does not point to a valid soundID. Skipping entry.\n";
            continue;
        }

        //remove buffer ptrs map
        soundIdToBufferPtrMap.erase ( *soundIDPtr );
    }
}