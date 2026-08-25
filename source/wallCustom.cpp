// #include "../header/wallCustom.h"

// WallCustom::WallCustom( Vec3 pos, Vec3& playerPos, sf::Texture& texture, sf::Vector2< int > frameCellSize, 
//             int sheetRow, int currentFrame, sf::Vector2< float > hitBoxPos, sf::Vector2< float > hitBoxSize,
//             sf::Vector2 <int> spritePosOffset, float zHeight ) 
//             : bodySprite( texture ), bodyShadowSprite( texture ), playerPosRef( playerPos ){

//     objType = Wall;
//     collisionShape = GameObject::CollisionShape::AABB;
//     isSolid = true;

//     this -> pos = pos;
//     this -> frameCellSize = frameCellSize;
//     this -> sheetRow = sheetRow;
//     this -> currentFrame = currentFrame;
//     this -> hitBoxPos = hitBoxPos;
//     this -> hitBoxSize = hitBoxSize;
//     this -> spritePosOffset = spritePosOffset;
//     this -> zHeight = zHeight + pos.z;

//     animationTimer = 0.0f;
//     frameDuration = 0.1f;
//     currentFrame = 0;
//     sheetRow = randomRange( 0, 4 );
//     fadeAlpha = 178;
//     fadeAlphaDist = 256;
//     frameCellSize = { 192, 288 };
 
//     //set starting texture pos
//     bodyShadowSprite.setTextureRect(sf::IntRect({frameCellSize.x*currentFrame, sheetRow}, {frameCellSize.x, frameCellSize.y}));
//     bodySprite.setTextureRect(sf::IntRect({frameCellSize.x*(currentFrame+1), sheetRow}, {frameCellSize.x, frameCellSize.y}));
// }

// void WallCustom::update( float dt ){

//     if ( playerPosRef.z <= zHeight ) 
//     {
//         isSolid = false;
//     }
//     else 
//     {
//         isSolid = true;
//     }

//     if ( playerPosRef.z <= zHeight ) isSolid = false;
//     else isSolid = true;

//     float fadeSpeed = 20.0f;
//     float target = isObjBehind ? fadeAlpha : 255.f;
//     alpha += (target - alpha) * (fadeSpeed * dt);
// }

// void WallCustom::updateOnCollision(){
//     // itemState = TRANSFORM;
//     // isActive = false;
// }

// void WallCustom::draw( sf::RenderWindow& window ){

//     sf::Vector2 spritePos = { float( pos.x - frameCellSize.x/2 + spritePosOffset.x ), 
//                               float( pos.y - frameCellSize.y/2 + spritePosOffset.y ) };

//     // windmill body setup
//     bodyShadowSprite.setPosition( { spritePos.x, spritePos.y } );
//     bodySprite.setPosition( { spritePos.x, spritePos.y + pos.z } );

//     bodySprite.setColor( sf::Color( 255, 255, 255, alpha ) );

//     //center debug setup
//     sf::CircleShape dotCenter(1.0f); 
//     dotCenter.setFillColor(sf::Color::Red);
//     dotCenter.setPosition({pos.x, pos.y});
    
//     //hitbox debug setup
//     sf::RectangleShape hitboxRect;
//     hitboxRect.setPosition( hitBoxPos );
//     hitboxRect.setSize( hitBoxSize );
//     hitboxRect.setFillColor( sf::Color::Transparent );
//     hitboxRect.setOutlineColor( sf::Color::Magenta );
//     hitboxRect.setOutlineThickness( 1.0f );

//     //draw calls
//     window.draw( bodyShadowSprite );
//     window.draw( bodySprite );

//     window.draw( hitboxRect );
//     window.draw(dotCenter);
// }

// void WallCustom::checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias ){
//     //check area behind object -> decide to fade or not
//     if ( checkPos.x + widthBias > hitBoxPos.x 
//         && checkPos.x - widthBias < hitBoxPos.x + hitBoxSize.x 
//         && checkPos.y > hitBoxPos.y - fadeAlphaDist 
//         && checkPos.y < pos.y && playerPosRef.z > zHeight) 
//     {  
//         isObjBehind = true;
//     }
//     else
//     {
//         isObjBehind = false;
//     }
// }