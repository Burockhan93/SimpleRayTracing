#pragma once
#include "..\Math\Vec3.h"
#include "..\Math\Vec2.h"
struct Vertex
{
public:
    Vec3 Position;
    Vec2 TextureCoordinate;
    Vec3 Normal;
};