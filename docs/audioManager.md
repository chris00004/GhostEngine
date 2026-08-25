needs:
    - sound class pool
    - play sound effect
    - set sound effect volume

    - play music track
    - set music track volume
    - fade in music track
    - fade out music track

enum class SoundID
    - PlayerJump
    - PlayerRoll
    - PlayerBrake
    - etc....

SoundProperties Struct
    - sf::SoundBuffer* buffer = nullptr;
    - std::string name;
    - float volume          = 100.0f;
    - float pitch           = 1.0f;
    - bool  isLooping        = false;
    - bool  is3D             = false;
    - bool  isDoppler         = false;
    - float dopplerFactor    = 1.0f;
    - float minDistance      = 1.0f;
    - float maxDistance      = 100.0f;
    - float attenuation      = 1.0f;

SoundContainer Class
    needs:
        - SoundProperties properties 
        - bool isActive = false;
        - bool isMoving = false;
        - Vec3* position = nullptr;

    allows for:
        playing basic 2d sound
        playing 3d sound at single position
        playing 3d sound at moving position
        toggling doppler effect
        setting doppler effect 

Audio Manager Class
    needs:
        - std::vector<SoundContainer> soundList
        - std::unordered_map<std::string, SoundID> fileNameToSoundIDMap
        - std::unordered_map<SoundID, sf::SoundBuffer> soundBufferMap
            when manager created -> check which paks loaded
                switch case for each pak to load buffer map
            soundBufferMap {
                {PlayerJump, pak.sound.find ( "playerJump.wav" ) }, -> maps PlayerJump to soundBuffer directly
            }
        - std::unordered_map<SoundID, SoundPropery> soundProperty2DMap
        - std::unordered_map<SoundID, SoundPropery> soundProperty3DMap


        - playSound2D( SoundID id )
            find !isActive sound in soundsList
                if found
                    sound.properties =  soundPropertyMap.find( id ) -> second
                    sound.


        - playSound3D( SoundID sound, Vec3 position )
        - playSound3DMoving( SoundID sound, Vec3& position, bool isDoppler )


maps of 2D and 3D sound identities, and one default 2D/3D