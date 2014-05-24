//
//  ArkanoidGameObject.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 24/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__ArkanoidGameObject__
#define __Arkanoid__ArkanoidGameObject__

#include "KMEngine.h"
#include "CollidableSurface.h"

typedef struct _AABB
{
    vec2 origin;

    vec2 leftTop;
    vec2 leftBottom;
    vec2 rightBottom;
    vec2 rightTop;
    
} AABB;

typedef struct _TriangleFace
{
    vec2 normal;
    vec2 origin;
    
    vec2 vertices[3];
    
} TriangleFace;

class ArkanoidGameObject : public KMGameObject
{
public:
    ArkanoidGameObject();
    
    virtual void setPosition(const vec3& position);
    const AABB& getAABB() const { return _aabb; }
    
    bool doesCollidesWithBall(const vec2& ballPosition, const vec2& ballDesiredPosition, const float radius, const float distanceToTravel);
    

protected:
    AABB _aabb;
    std::vector<TriangleFace> _faces;
    void calculateAABB(const std::vector<KMVertex>& vertices);
};

#endif /* defined(__Arkanoid__ArkanoidGameObject__) */
