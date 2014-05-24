//
//  CollidableSurface.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 24/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__CollidableSurface__
#define __Arkanoid__CollidableSurface__

#include "KMEngine.h"
class ArkanoidGameObject;

class CollidableSurface
{
public:
    CollidableSurface(const vec2& origin, const vec2& normal, const vec2& p1, const vec2& p2, ArkanoidGameObject* owner);
    
    void updateOrigin(const vec2& newOrigin) { _origin = newOrigin; }

    bool isBallMovingTowards(const vec2& movementVec) { return _normal.Dot(movementVec) < 0; }
    
    bool ballIntersectsWhileMoving(const vec2& ballPos, const vec2& ballDesiredPos, const vec2& ballMovementVec, const float ballRadius, vec2& intersectionPoint);
    
    vec2 reflectVector(const vec2& movementVec) { return movementVec - _normal * movementVec.Dot(_normal) * 2.0f;}
    
    const ArkanoidGameObject* const getOwner() const {return _owner;}
private:
    vec2 _origin;
    vec2 _normal;
    vec2 _p1;
    vec2 _p2;
    
    ArkanoidGameObject *_owner;
};

#endif /* defined(__Arkanoid__CollidableSurface__) */
