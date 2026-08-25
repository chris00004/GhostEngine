// #include "../header/item.h"


// Item::Item( Vec3 pos, sf::Texture& texture, int& plantCountRef ) : sprite( texture ), shadowSprite( texture ), countRef( plantCountRef ){

//     objType = Flower;
//     itemState = SEED;
//     isSolid = false;

//     this -> pos = pos;

//     animationTimer = 0.0f;
//     frameDuration = 0.1f;
//     currentFrame = 0;
//     sheetRow = randomRange( 0, 4 );
//     fadeAlpha = false;
//     fadeAlphaDist = 24;
//     frameCellSize = 32;

//     hitBoxPos = { pos.x - frameCellSize/2, pos.y - frameCellSize/2 };
//     hitBoxSize = { static_cast<float>( frameCellSize ), static_cast<float>( frameCellSize ) };
 
//     //set starting texture pos
//     shadowSprite.setTextureRect(sf::IntRect({0, 0}, {frameCellSize, frameCellSize}));
//     sprite.setTextureRect(sf::IntRect({0, frameCellSize}, {frameCellSize, frameCellSize}));

//     //printf( "obj pos(X,Y,Z): [ %f, %f, %f ]\n", pos.x, pos.y, pos.z );
    
// }

// void Item::update( float dt ){
//     int endFrame = 5;

//     switch(itemState)
//     {
//         case SEED:
//         break;

//         case TRANSFORM:
//             animationTimer += dt;

//             while (animationTimer >= frameDuration)
//             {
//                 animationTimer -= frameDuration;
//                 frameCount++;
//                 currentFrame++;
//             }

//             if (currentFrame > endFrame) 
//             {
//                 currentFrame = endFrame;
//                 itemState = FLOWER;
//             }
//         break;
//     }
// }

// void Item::updateOnCollision(){
//     itemState = TRANSFORM;
//     isActive = false;
//     countRef++;
// }

// void Item::draw( sf::RenderWindow& window ){

//     //for testing width -> radius
//     int width = 16;

//     sf::CircleShape dot(width);
//     sf::CircleShape dotCenter(1.0f); 

//     // dot.setFillColor(sf::Color::Blue);
//     // dot.setPosition({pos.x-width, pos.y-width});
//     // window.draw(dot);

//     /* DRAW PLAYER TO SCREEN */
//     sprite.setTextureRect( sf::IntRect( { currentFrame * frameCellSize, sheetRow * frameCellSize }, { frameCellSize, frameCellSize } ) );
//     shadowSprite.setPosition( { pos.x - frameCellSize/2, pos.y - 0 } );
//     sprite.setPosition( { pos.x - frameCellSize/2, ( pos.y - frameCellSize ) + pos.z } );
//     //window.draw( shadowSprite );
//     // if (isObjBehind) sprite.setColor( sf::Color( 255, 255, 255, 128) );
//     // else sprite.setColor( sf::Color( 255, 255, 255, 255) );

//     window.draw( sprite );

//     // dot.setFillColor(sf::Color::Red);
//     // dotCenter.setPosition({pos.x, pos.y});
//     // window.draw(dotCenter);

//     // sf::RectangleShape hitboxRect;
//     // hitboxRect.setPosition( hitBoxPos );
//     // hitboxRect.setSize( hitBoxSize );
//     // hitboxRect.setFillColor( sf::Color::Transparent );
//     // hitboxRect.setOutlineColor( sf::Color::Magenta );
//     // hitboxRect.setOutlineThickness( 1.0f );
//     // window.draw( hitboxRect );
// }

// void Item::checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias ){
//     //check area behind object -> decide to fade or not
//     if ( checkPos.x + widthBias > hitBoxPos.x 
//         && checkPos.x - widthBias < hitBoxPos.x + hitBoxSize.x 
//         && checkPos.y > hitBoxPos.y - fadeAlphaDist 
//         && checkPos.y < pos.y ) 
//     {  
//         isObjBehind = true;
//     }
//     else
//     {
//         isObjBehind = false;
//     }
// }

// // float Item::getDrawDepth(){ return pos.y; }