// #include "../header/structure.h"

// Structure::Structure( Vec3 pos, Vec3& playerPos, sf::Texture& texture ) : bodySprite( texture ), bodyShadowSprite( texture ), playerPosRef( playerPos ){

//     objType = Wall;
//     isSolid = true;
//     hasFloor = true;

//     this -> pos = pos;
//     zHeight = -168.0f;

//     animationTimer = 0.0f;
//     frameDuration = 0.1f;
//     currentFrame = 0;
//     sheetRow = 0;
//     fadeAlpha = 178.0f;
//     fadeAlphaDist = 228;
//     frameCellSize = { 192, 288 };

//     collisionShape = GameObject::CollisionShape::Ellipse;
//     center = { pos.x, pos.y };
//     ellipseRadii = { 92.0f, 62.0f };
 
//     //set starting texture pos
//     bodyShadowSprite.setTextureRect(sf::IntRect( { frameCellSize.x * 4, 0}, { frameCellSize.x, frameCellSize.y} ) );
//     bodySprite.setTextureRect(sf::IntRect( { frameCellSize.x * ( 5 ), 0}, { frameCellSize.x, frameCellSize.y} ) );

//     //printf( "obj pos(X,Y,Z): [ %f, %f, %f ]\n", pos.x, pos.y, pos.z );
    
// }

// void Structure::update( float dt ){

//     // float fadeSpeed = 200.0f;
//     float fadeSpeed = 20.0f;
//     float target = isObjBehind ? fadeAlpha : 255.f;
//     alpha += (target - alpha) * (fadeSpeed * dt);

//     if ( playerPosRef.z <= zHeight ) 
//     {
//         isSolid = false;
//         ellipseRadii = { 44.0f, 28.0f };
//     }
//     else 
//     {
//         isSolid = true;
//         ellipseRadii = { float( 92.0f + playerPosRef.z/3.5 ), 62.0f + float( playerPosRef.z/4.94 ) };
//     }

//     // animationTimer += dt;

//     // while (animationTimer >= frameDuration)
//     // {
//     //     animationTimer -= frameDuration;
//     //     bladeRotation += randomRange(2,3);
//     // }

//     // if (sndWindmill.getStatus() != sf::SoundSource::Status::Playing)
//     // {
//     //     sndWindmill.play();
//     // }
//     // sndWindmill.setVolume( getDistVolume( { playerPosRef.x, playerPosRef.y }, { pos.x, pos.y - 100.0f }, 350.0f ) );

// }

// void Structure::updateOnCollision(){
//     // itemState = TRANSFORM;
//     // isActive = false;
// }

// void Structure::draw( sf::RenderWindow& window ){

//     sf::Vector2 spritePos = { float( pos.x - frameCellSize.x/2 ), float( ( pos.y - 215 ) + pos.z ) };

//     // structure setup
//     bodyShadowSprite.setPosition( spritePos );
//     bodySprite.setPosition( spritePos );
//     bodySprite.setColor( sf::Color( 255, 255, 255, alpha ) );


//     //center debug setup
//     // sf::CircleShape dotCenter(1.0f); 
//     // dotCenter.setFillColor(sf::Color::Red);
//     // dotCenter.setPosition({pos.x, pos.y});
    
//     //hitbox debug setup
//     // sf::RectangleShape hitboxRect;
//     // hitboxRect.setPosition( hitBoxPos );
//     // hitboxRect.setSize( hitBoxSize );
//     // hitboxRect.setFillColor( sf::Color::Transparent );
//     // hitboxRect.setOutlineColor( sf::Color::Magenta );
//     // hitboxRect.setOutlineThickness( 1.0f );

//     //ellipse debug setup
//     // sf::CircleShape hitboxEllipse(1.0f);
//     // hitboxEllipse.setOrigin( { 1.0f, 1.0f } );
//     // hitboxEllipse.setPosition( { pos.x, pos.y } );
//     // hitboxEllipse.setScale( { ellipseRadii.x, ellipseRadii.y } );
//     // hitboxEllipse.setFillColor( sf::Color::Transparent );
//     // hitboxEllipse.setOutlineColor( sf::Color::Magenta );
//     // hitboxEllipse.setOutlineThickness( 0.025f );

//     //draw calls
//     window.draw( bodyShadowSprite );
//     window.draw( bodySprite );

//     // window.draw( hitboxEllipse );
//     // window.draw(dotCenter);
// }

// void Structure::checkIfPosIsBehind( sf::Vector2<float> checkPos, int widthBias ){

//     //custom boundaries
//     float xEdge = 80.0f;
//     float yEdge = 55.0f;

//     //check area behind object -> decide to fade or not
//     if ( checkPos.x + widthBias > pos.x - xEdge
//         && checkPos.x - widthBias < pos.x + xEdge 
//         && checkPos.y > pos.y - yEdge - fadeAlphaDist 
//         && checkPos.y < pos.y && playerPosRef.z > zHeight) 
//     {  
//         isObjBehind = true;
//     }
//     else
//     {
//         isObjBehind = false;
//     }
// }