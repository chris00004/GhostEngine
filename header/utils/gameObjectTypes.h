#pragma once

enum class ObjectType {
    NULL_OBJECT,
    SOLID,
    NON_SOLID_PLATFORM,
    ENTITY,
    DECORATION  
};

enum class SolidType {
    SOLID_INFINITE_HEIGHT,
    SOLID_INFINITE_HEIGHT_UP,
    SOLID_INFINITE_HEIGHT_DOWN,
    SOLID_FLOOR_ONLY,
    SOLID_CIELING_ONLY,
    SOLID_FLOOR_AND_CIELING
};

enum class CollisionShape {
    NGON,
    CIRCLE,
    ELLIPSE
};