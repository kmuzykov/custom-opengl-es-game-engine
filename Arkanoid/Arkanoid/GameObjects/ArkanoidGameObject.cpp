//
//  ArkanoidGameObject.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 24/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "ArkanoidGameObject.h"
#include "Ball.h"

#include <assert.h>

ArkanoidGameObject::ArkanoidGameObject()
{
    
}

void ArkanoidGameObject::setPosition(const vec3& position)
{
    KMGameObject::setPosition(position);
    
    vec2 position2D = vec2(position.x, position.y);
    for (CollidableSurface& surf : _collidableSurfaces)
        surf.updateOrigin(position2D);    
}

void ArkanoidGameObject::calculateCollidableSurfaces(const std::vector<KMVertex>& vertices)
{
    unsigned long count = vertices.size();
    if (count == 0)
    {
        KMLOG("Can't calculate AABB for empty array of vertices");
        return;
    }
    
    const KMVertex& first = vertices.front();
    float minX = first.position.x;
    float minY = first.position.y;
    float maxX = minX;
    float maxY = minY;
    
    vec2 origin = vec2(_position.x, _position.y);
    
    for (int i = 0; i < count; i++)
    {
        const KMVertex& v = vertices[i];
        
        maxX = fmaxf(maxX, v.position.x);
        maxY = fmaxf(maxX, v.position.y);
        minX = fminf(minX, v.position.x);
        minY = fminf(minY, v.position.y);
    }
    
    _collidableSurfaces.clear();
    
    vec2 down(0, -1);
    vec2 up(0, 1);
    vec2 right(1, 0);
    vec2 left(-1, 0);
    
    _collidableSurfaces.push_back(CollidableSurface(origin, down,    vec2(minX, minY), vec2(maxX, minY)));    //bottom
    _collidableSurfaces.push_back(CollidableSurface(origin, right,   vec2(maxY, minY), vec2(maxX, maxY)));    //right
    _collidableSurfaces.push_back(CollidableSurface(origin, up,      vec2(maxX, maxY), vec2(minX, maxY)));    //top
    _collidableSurfaces.push_back(CollidableSurface(origin, left,    vec2(minX, maxY), vec2(minX, minY)));    //left
}




