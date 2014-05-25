//
//  Ball.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__Ball__
#define __Arkanoid__Ball__

#include "KMEngine.h"
#include "ArkanoidGameObject.h"

class Ball : public KMGameObject
{
public:
    Ball();

    vec2 getPosition2D() const {return vec2(_position.x, _position.y);}
    void setPosition2D(const vec2& newPos) { KMGameObject::setPosition(vec3(newPos.x, newPos.y, _position.z));}
    
    void setMovementVector(const vec2& movement) { _movement = movement; }
    const vec2& getMovementVector() const {return _movement; }

private:
    vec2 _movement;
    float _radius;

};

#endif /* defined(__Arkanoid__Ball__) */
