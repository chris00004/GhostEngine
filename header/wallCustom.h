// #pragma once

// #include "../header/gameObject.h"
// #include "../header/utils/gameplayTypes.h"
// #include <vector>

// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>

// class WallCustom : public GameObject {
// public:
//     WallCustom( Vec3 pos, Vec3& playerPos, sf::Texture& texture, sf::Vector2< int > frameCellSize, 
//             int sheetRow, int currentFrame, sf::Vector2< float > hitBoxPos, sf::Vector2< float > hitBoxSize,
//             sf::Vector2 <int> spritePosOffset, float zHeight );
//     void update(float dt);
//     void updateOnCollision() override;
//     void draw( sf::RenderWindow& window ) override;
//     void checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias ) override;

// private:
//     Vec3& playerPosRef;

//     sf::Sprite bodySprite;
//     sf::Sprite bodyShadowSprite;

//     float fadeAlpha;
//     float alpha = 255.0f;
//     int fadeAlphaDist;
//     bool isObjBehind;

//     sf::Vector2< float > hitBoxPosDefault;
//     sf::Vector2< float > hitBoxSizeDefault;

//     sf::Vector2 <int> spritePosOffset;
//     sf::Vector2< int > frameCellSize;
//     float animationTimer;
//     float frameDuration;
//     int frameCount;
//     int sheetRow;
//     int currentFrame;
// };