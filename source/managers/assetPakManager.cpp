#include "assetPakManager.h"
#include <filesystem>

AssetPakManager::AssetPakManager(){} //: pakData( pakData ){}

/* --- [ Overview ] ---------------------------------
    
    [ void load ] takes in a string path, if pak file -> load all byte data into entries unordered map

    [ void buildObjects ] takes in a pak struct -> writes the data in entries as C++ and SFML objects 
                        organized into the pak struct's unordered maps

    [ entries ] unordered map holding all currently loaded pak file byte data

 --------------------------------------------------*/


void AssetPakManager::init( AudioManager& audioMgrRef ) {
    audioMgrPtr = &audioMgrRef;
}

//loads and overwrites local entries unordered map with pak data from given path
void AssetPakManager::load( const std::string& pakPath ) {
    
    std::cout << "CWD: " << std::filesystem::current_path() << std::flush;
    std::cout << "Opening pak: " << pakPath << std::flush;
    std::ifstream in(pakPath, std::ios::binary);
    if (!in) {
        std::cout << " -> FAILED TO OPEN" << std::flush;
        throw std::runtime_error("Cannot open pak: " + pakPath);
    }
    std::cout << " -> opened OK" << std::flush;

    uint32_t count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::cout << "\ncount: " << count << std::flush;

    for (uint32_t i = 0; i < count; i++) {
        uint32_t nameLen = 0;
        in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        std::cout << "\n[" << i << "] nameLen: " << nameLen << std::flush;

        std::string name(nameLen, '\0');
        in.read(name.data(), nameLen);
        std::cout << " name: " << name << std::flush;

        uint64_t dataLen = 0;
        in.read(reinterpret_cast<char*>(&dataLen), sizeof(dataLen));
        std::cout << " dataLen: " << dataLen << std::flush;

        std::vector<char> data(dataLen);
        in.read(data.data(), dataLen);

        entries[name] = { std::move(data) };
        std::cout << " OK" << std::flush;
    }
    std::cout << "\nload() done." << std::flush;
}

// searches through entries unordered map, sorts based on filetype, and builds c++ & sfml objs into given pakData struct
void AssetPakManager::buildObjects( Pak& pak ) {

    // clear existing pakData unordered maps
    pak.textures.clear();
    pak.sounds.clear();
    pak.fonts.clear();
    pak.dialogues.clear();

    // helper for 
    auto endsWith = []( const std::string& str, const std::string& suffix ) {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    };

    //build & organize objects
    for ( const auto& [name, entry] : entries ) {
        const void* ptr = entry.data.data();
        size_t size = entry.data.size();
 
        //textures
        if ( endsWith( name, ".png" ) || endsWith( name, ".jpg" ) ) {
            sf::Texture tex( ptr, size );
            pak.textures[ name ] = std::move( tex );
            std::cout << "Added " << name << " to textures map." << std::endl;

        //sound buffers
        } else if ( endsWith( name, ".wav" ) || endsWith( name, ".ogg" ) ) {
            sf::SoundBuffer buf( ptr, size );
            pak.sounds[ name ] = std::move( buf );

            //use name to 
            std::cout << "Added " << name << " to sounds map." << std::endl;

        //fonts
        } else if ( endsWith( name, ".ttf" ) || endsWith( name, ".otf" ) ) {

            // copy byte data into paks raw font buffers 
            pak.rawFontBuffers[ name ] = entry.data;

            // use ptr to spot in pak data
            const void* ptr = pak.rawFontBuffers[ name ].data();
            size_t size = pak.rawFontBuffers[ name ].size();

            sf::Font font( ptr, size );
            font.setSmooth( false );
            pak.fonts[ name ] = std::move( font );
            std::cout << "Added " << name << " to fonts map." << std::endl;

        //dialogues
        } else if ( endsWith( name, ".txt" ) ) {
            std::vector<std::string> dialogueEntry;
            
            //wrap raw byte data in a string stream
            std::string rawText( entry.data.begin(), entry.data.end() );
            std::istringstream stream( rawText );
            
            std::string line;
            while ( std::getline( stream, line ) ) {

                // strip carriage returns for windows .txt files (\r\n)
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();

                // if line not empty -> push line string to dialogue entry
                if (!line.empty()) 
                    dialogueEntry.push_back( std::move( line ) );

            }
            pak.dialogues[ name ] = std::move( dialogueEntry );
            std::cout << "Added " << name << " to dialogue map." << std::endl;
        }
    }

    entries.clear();
}

// Get an asset by name — throws if not found
const AssetPakManager::Entry& AssetPakManager::get( const std::string& name ) const {
    auto entry = entries.find( name );
    if ( entry == entries.end() ) {
        throw std::runtime_error( "Asset not found in pak: " + name );
    }
    return entry -> second;
}

bool AssetPakManager::has( const std::string& name ) const {
    return entries.count( name ) > 0;
}
