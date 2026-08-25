#pragma once

#include "commonTypes.h"
#include "gameObjectTypes.h"

#include "SFML/Graphics.hpp"

class GameObject {
    public:
        GameObject( Vec3 position );
        void init();
        void update();

        const Vec3 getPosition();
        const Vec3 getSize();

    private:

        bool isActive;

        ObjectType objectType;
        CollisionShape collisionShape;

        //3D Properties
        Vec3 position; // { 0, 0, 0 }
        Vec3 size; // { 24, 24, 24 }

        //quick hand z attributes
        float zTop; // position.z - size.z;
        float zBottom; // position.z;
};