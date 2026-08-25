#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

#include <filesystem>

//TO RUN: CTRL+SHIFT+P -> ENTER

// PAK format:
// [4 bytes] file count
// per file:
//   [4 bytes] name length
//   [N bytes] name (used as the lookup key e.g. "assets/tile.png")
//   [8 bytes] data length
//   [N bytes] raw data

void packFiles( const std::string& outPath, const std::vector <std::string>& files ) {
    
    std::cout << "CWD: " << std::filesystem::current_path() << "\n" << std::flush;
    //creates out pak file, opens in binary mode
    std::ofstream out( outPath, std::ios::binary );
    if ( !out ) {
        std::cerr << "Failed to create: " << outPath << "\n";
        return;
    }

    //calc file count 
    uint32_t count = static_cast <uint32_t> ( files.size() );

    //weed out invalid files
    for ( const auto& path : files ) {
        std::ifstream in ( path, std::ios::binary );
        if ( !in ) count --;
    }
    
    //&count -> mem address of count
    //sizeof(count) -> num of bytes to write
    out.write( reinterpret_cast<char*>( &count ), sizeof( count ) );

    //loop through each file in pak
    for ( const auto& path : files ) {

        //do invalid check again after file size calculated, just for feedback in terminal
        std::ifstream in( path, std::ios::binary );
        if ( !in ) {
            std::cerr << "Skipping (not found): " << path << "\n";
            continue;
        }

        //read file into vector
        std::vector<char> data{
            //start
            std::istreambuf_iterator <char> ( in ),
            //endpoint
            std::istreambuf_iterator <char> ()
        };

        //path.size() -> num of chars in path string
        //EX: "assets/image.png" -> has 16 chars -> 16 = integer -> uint32 = 4 bytes
        //nameLen -> num of chars in string -> uint32, in memory 4 bytes
        std::filesystem::path fsPath ( path );
        std::string fileName = fsPath.filename().string();
        uint32_t nameLen = static_cast<uint32_t> ( fileName.size() );

        //1st write length in binary [uint32 - 4 bytes]
        out.write( reinterpret_cast <char*> ( &nameLen ), sizeof ( nameLen ) );

        //2nd write data in bianry [char - 1 byte] 16 chars = 16 bytes
        //path.data() -> pointer to 1st char
        out.write( fileName.data(), nameLen );

        //data.size() num of bytes in file (ogg, png, etc..)
        //dataLen -> length of data -> uint64, in memory 8 bytes
        uint64_t dataLen = static_cast<uint64_t>( data.size() );

        //1st write length in binary [ uint64 - 8 bytes ]
        out.write( reinterpret_cast<char*> ( &dataLen ) , sizeof ( dataLen ) );

        //2nd write file's data
        //data.data() -> start point for write
        //dataLen -> how many bytes to write
        out.write( data.data(), dataLen );

        std::cout << "Packed: " << path << " ( " << dataLen << " bytes )\n";
    }

    //writes in chunks of [count][nameLen][dataLen][data]

    std::cout << "\nDone -> " << outPath << "\nCount: " << count;
}

//run pakker
int main() {
    // create global pak file
    packFiles("../../build/global-test.pak", 
        {
        "../../assets-test/graphics/sprite-sheets/test.png",
        "../../assets-test/audio/sfx/test.wav",
        "../../assets-test/fonts/test.otf",
        "../../assets-test/dialogues/test.txt",

        "../../assets-test/nonExistant.png",
        "../../assets-test/graphics/sprite-sheets/sprite-sheet.png",
        "../../assets-test/audio/sfx/sfx.wav",
        "../../assets-test/dialogues/intro.txt",
        "../../assets-test/dialogues/stage1.txt"
    } );

    // create stage common pak file
    packFiles("../../build/stage-common-test.pak", 
        {
        "../../assets-test/graphics/sprite-sheets/test.png",
        "../../assets-test/audio/sfx/test.wav",
        "../../assets-test/fonts/test.otf",
        "../../assets-test/dialogues/test.txt",
        
        "../../assets-test/nonExistant.png"
    } );

    //create stage 0 pak file
    packFiles("../../build/stage-0-test.pak", 
        {
        "../../assets-test/graphics/sprite-sheets/test.png",
        "../../assets-test/audio/sfx/test.wav",
        "../../assets-test/fonts/test.otf",
        "../../assets-test/dialogues/test.txt",
        
        "../../assets-test/dialogues/intro.txt",
        "../../assets-test/dialogues/stage1.txt",
        "../../assets-test/graphics/stamp.jpg",
        "../../assets-test/graphics/cher.jpg",
        "../../assets-test/graphics/wifi.jpg",
        "../../assets-test/graphics/folder.jpg"
    } );

    std::cout << "\nPress enter to close\n";
    std::cin.get();
}
