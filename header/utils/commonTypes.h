#pragma once

#include <random>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>

#include <SFML/System.hpp>

/**
 * @brief Safely gets enum value as an integer
 *
 * @param enumVal the enum value to static cast
 * @return enum val as int
 */
template<typename T>
auto enumToInt ( T enumVal ) { return static_cast<int>( enumVal ); }


/**
 * @brief Safely gets object from unordered map
 *
 * @param map The unordered map to search through
 * @param key Key to find object in map
 * @return second value paired to given key
 *
 * @note ex: findMapObject ( pakData.fonts, "font3.otf" ) -> returns sf:Font font3
 */
template<typename Map>

auto findMapObject( Map& map, const typename Map::key_type& key ) { //-> typename Map::mapped_type*

    auto entry = map.find( key );
    return ( entry != map.end() ) ? &entry -> second : nullptr;
}


inline int randomRange( int min, int max ) {

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

inline float randomRange( float min, float max ) {

    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

inline float distSquared( float x1, float y1, float x2, float y2 ) {

    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx * dx + dy * dy;
}

inline float vecDistSquared( sf::Vector2f vec1, sf::Vector2f vec2 ) {

    float dx = vec2.x - vec1.x;
    float dy = vec2.y - vec1.y;
    return dx * dx + dy * dy;
}

inline float lerp( float a, float b, float t ) {

    return a + ( b - a ) * t;
}

inline sf::Vector2f lerpVec( sf::Vector2f a, sf::Vector2f b, float t ) {

    return {

        lerp( a.x, b.x, t ),
        lerp( a.y, b.y, t )
    };
}

struct Vec3 { float x = 0.0f; float y = 0.0f; float z = 0.0f; };

struct Timer { float base = 15.0f; float current = 15.0f; };

inline void timerUpdate( Timer& timer, float rate ) { 

    if ( timer.current > 0.0f ) {

        timer.current -= rate; 

        if ( timer.current < 0.0f ) {

            timer.current = 0.0f;
        }
    }

};
inline void timerReset( Timer& timer ) { timer.current = timer.base; };
inline bool timerIsDone( Timer& timer ) { return timer.current <= 0.0f; };