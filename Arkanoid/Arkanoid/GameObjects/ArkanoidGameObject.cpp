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
    _aabb.origin = vec2(position.x, position.y);
    
    for (TriangleFace& face : _faces)
    {
        face.origin = _aabb.origin;
    }
}

void ArkanoidGameObject::calculateAABB(const std::vector<KMVertex>& vertices)
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
    
    //Going in steps by 3 since we need also to create triangle faces
    for (int i = 0; i < count; i+= 3)
    {
        const KMVertex& v1 = vertices[i];
        const KMVertex& v2 = vertices[i + 1];
        const KMVertex& v3 = vertices[i + 2];
        
        vec2 normal = vec2(v1.normal.x, v1.normal.y).Normalized();
        
        TriangleFace face;
        face.origin = origin;
        face.normal = normal;
        face.vertices[0] = vec2(v1.position.x, v1.position.y);
        face.vertices[1] = vec2(v2.position.x, v2.position.y);
        face.vertices[2] = vec2(v3.position.x, v3.position.y);
        
        _faces.push_back(face);
        
        maxX = fmaxf(maxX, v1.position.x);
        maxX = fmaxf(maxX, v2.position.x);
        maxX = fmaxf(maxX, v3.position.x);
        
        maxY = fmaxf(maxX, v1.position.y);
        maxY = fmaxf(maxX, v2.position.y);
        maxY = fmaxf(maxX, v3.position.y);
        
        minX = fminf(minX, v1.position.x);
        minX = fminf(minX, v2.position.x);
        minX = fminf(minX, v3.position.x);
        
        minY = fminf(minY, v1.position.y);
        minY = fminf(minY, v2.position.y);
        minY = fminf(minY, v3.position.y);
    }
    
    _aabb.origin = origin;
    _aabb.leftBottom    = vec2(minX, minY);
    _aabb.rightBottom   = vec2(maxX, minY);
    _aabb.rightTop      = vec2(maxX, maxY);
    _aabb.leftTop       = vec2(minX, maxY);
}

static bool checkLineAndLineIntersection(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, float& s, float &t, vec2& pointOfIntersection);
bool ArkanoidGameObject::doesCollidesWithBall(const vec2& ballPosition, const vec2& ballDesiredPosition, const float radius, const float distanceToTravel)
{
    //Checking ray intersects with AABB
    Vector2<vec2> aabFaces[] = {
        {_aabb.leftBottom, _aabb.rightBottom},
        {_aabb.rightBottom, _aabb.rightTop},
        {_aabb.rightTop, _aabb.leftTop},
        {_aabb.leftTop, _aabb.leftBottom},
    };
    
    float minDistanceSQ = -1;
    
    for (auto& face : aabFaces)
    {
        float s,t;
        vec2 intersectionPoint;
        
        bool intersectsAABB = checkLineAndLineIntersection(ballPosition,
                                                           ballDesiredPosition,
                                                           face.x,
                                                           face.y,
                                                           s, t, intersectionPoint);
        if (intersectsAABB)
        {
            float distanceSQ = (intersectionPoint - ballPosition).LengthSquared();
            if (minDistanceSQ < 0 || minDistanceSQ > distanceSQ)
            {
                minDistanceSQ = distanceSQ;
            }
        }
    }
    
    if (minDistanceSQ > 0 && minDistanceSQ < radius)
    {
        return true;
    }
    
    return false;
}

static bool checkLineAndLineIntersection(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, float& s, float &t, vec2& pointOfIntersection)
{
    // FAIL: Line undefined
    if ( (p1.x==p2.x && p1.y==p2.y) || (p3.x==p4.x && p3.y==p4.y) ) return false;
    
    const float BAx = p2.x - p1.x;
    const float BAy = p2.y - p1.y;
    const float DCx = p4.x - p3.x;
    const float DCy = p4.y - p3.y;
    const float ACx = p1.x - p3.x;
    const float ACy = p1.y - p3.y;
    
    const float denom = DCy*BAx - DCx*BAy;
    
    s = DCx*ACy - DCy*ACx;
    t = BAx*ACy - BAy*ACx;
    
    if (denom == 0) {
        if (s == 0 || t == 0) {
            // Lines incident
            return true;
        }
        // Lines parallel and not incident
        return false;
    }
    
    s = s / denom;
    t = t / denom;

    // Point of intersection
    pointOfIntersection.x = p1.x + s * (p2.x - p1.x);
    pointOfIntersection.y = p1.y + s * (p2.y - p1.y);
        
    return true;
}


