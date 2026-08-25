// #pragma once

// #include "gameObject.h"
// #include "utils/gameplayTypes.h"
// #include <vector>
// #include <iostream>
// #include <cstdio>

// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>
// //include <SFML/Audio.hpp>

// class Item : public GameObject {
// public:
//     Item( Vec3 pos, sf::Texture& texture, int& plantCountRef );
//     void update(float dt);
//     void updateOnCollision() override;
//     void draw( sf::RenderWindow& window ) override;
//     void checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias ) override;
//     // float getDrawDepth() override;

// private:
//     enum ItemState { SEED, TRANSFORM, FLOWER };
//     ItemState itemState;

//     sf::Sprite sprite;
//     sf::Sprite shadowSprite;

//     bool fadeAlpha;
//     int fadeAlphaDist;
//     int alpha;
//     bool isObjBehind;

//     int frameCellSize;
//     float animationTimer;
//     float frameDuration;
//     int frameCount;
//     int sheetRow;
//     int currentFrame;

//     int& countRef;
// };