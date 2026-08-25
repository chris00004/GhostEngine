// #pragma once

// #include "../header/gameObject.h"
// #include "../header/utils/gameplayTypes.h"
// #include <vector>

// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>

// class Structure : public GameObject {
// public:
//     Structure( Vec3 pos, Vec3& playerPos, sf::Texture& texture );
//     void update(float dt);
//     void updateOnCollision() override;
//     void draw( sf::RenderWindow& window ) override;
//     void checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias ) override;

// private:
//     Vec3& playerPosRef;

//     sf::Sprite bodySprite;
//     sf::Sprite bodyShadowSprite;

//     float fadeAlpha;
//     int fadeAlphaDist;
//     float alpha = 255.0f;
//     bool isObjBehind;
//     float bladeRotation;

//     sf::Vector2< int > frameCellSize;
//     float animationTimer;
//     float frameDuration;
//     int frameCount;
//     int sheetRow;
//     int currentFrame;
// };