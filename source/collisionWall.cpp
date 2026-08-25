// #include "../header/collisionWall.h"

// CollisionWall::CollisionWall( Vec3 pos, Vec3& playerPos, sf::Vector2f hBoxSize ) : playerPosRef( playerPos )
// {
//     isSolid = true;
//     hasFloor = true;
//     this -> pos = pos;
//     zHeight = -2222.0f;

//     collisionShape = GameObject::CollisionShape::AABB;
//     hitBoxPos = { pos.x - hBoxSize.x/2, pos.y - hBoxSize.y/2 };
//     hitBoxSize = hBoxSize;
// }

// void CollisionWall::update( float dt ){

//     if ( playerPosRef.z <= zHeight ) isSolid = false;
//     else isSolid = true;
// }

// void CollisionWall::draw( sf::RenderWindow& window ){
//     //center debug setup
//     // sf::CircleShape dotCenter(1.0f); 
//     // dotCenter.setFillColor( sf::Color::Red );
//     // dotCenter.setPosition( { pos.x, pos.y } );
    
//     // //hitbox debug setup
//     // sf::RectangleShape hitboxRect;
//     // hitboxRect.setPosition( hitBoxPos );
//     // hitboxRect.setSize( hitBoxSize );
//     // hitboxRect.setFillColor( sf::Color::Transparent );
//     // hitboxRect.setOutlineColor( sf::Color::Magenta );
//     // hitboxRect.setOutlineThickness( 1.0f );

//     // //draw calls
//     // window.draw( hitboxRect );
//     // window.draw(dotCenter);
// }