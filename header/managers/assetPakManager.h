//ASSETS PAK READER

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <sstream>
#include <iostream>

#include "assetDataTypes.h"
#include "audioManager.h"

// PAK format:
// [4 bytes] file count
// per file:
//   [4 bytes] name length
//   [N bytes] name (used as the lookup key e.g. "assets/tile.png")
//   [8 bytes] data length
//   [N bytes] raw data

class AssetPakManager {

public:
    AssetPakManager();

    //holds byte info for an asset
    struct Entry {
        std::vector < char > data;
    };

    void init( AudioManager& auidoMgrRef );

    //reads pak into RAM
    void load( const std::string& pakPath );

    //build SFML & string objs
    void buildObjects( Pak& pak );

    sf::Texture&     getTexture( const std::string& name );
    sf::SoundBuffer& getSound  ( const std::string& name );
    sf::Font&        getFont   ( const std::string& name );

    //get asset by name, throws error if not found
    const Entry& get( const std::string& name ) const;

    bool has( const std::string& name ) const;

private:
    std::unordered_map < std::string, Entry > entries;
    AudioManager* audioMgrPtr = nullptr;
};
