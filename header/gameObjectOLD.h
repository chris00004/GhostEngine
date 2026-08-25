// #pragma once

// #include <iostream>
// #include "utils/gameplayTypes.h"

// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>

// class GameObject{
//     public:
//         GameObject( );

//         enum ObjectType { Player, Wall, Flower, Phone };
//         enum CollisionShape { AABB, Circle, Ellipse };

//         virtual void update(float dt);
//         virtual void draw( sf::RenderWindow& window );
        
        
        
//         virtual void updateOnCollision();
//         virtual void checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias );

//         virtual ObjectType getObjType() const;
//         virtual Vec3 getPosition() const;
//         virtual CollisionShape getCollisionShape() const;
//         virtual sf::FloatRect getBounds() const;
//         virtual sf::Vector2f getCenter();
//         virtual float getRadius();
//         virtual sf::Vector2f getEllipseRadii();
//         virtual float getZHeight();
//         virtual float getDrawDepth();
//         virtual bool getIsActive() const;
//         virtual bool checkHasFloor() const;
//         virtual bool checkIsSolid() const;
        
        

//     protected:
//         struct Timer{ 
//             float current = 0.0f; 
//             float base = 1.0f; 
//         };
// ;
//         ObjectType objType;
//         CollisionShape collisionShape = AABB;
//         Vec3 pos;
//         float zHeight;
//         bool isActive;
//         bool isSolid = false;
//         bool hasFloor = false;
//         float depthOffset = 0.0f;
        
//         //hitbox
//         sf::Vector2<float> hitBoxPos;
//         sf::Vector2<float> hitBoxSize;

//         //circle / ellipse
//         sf::Vector2f center;
//         float radius;
//         sf::Vector2f ellipseRadii;
// };