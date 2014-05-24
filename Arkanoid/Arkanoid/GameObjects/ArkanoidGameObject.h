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
#include <string>

class ArkanoidGameObject : public KMGameObject
{
public:
    ArkanoidGameObject();

    void setTag(const std::string& tag) { _tag = tag; }
    const std::string& getTag() const { return _tag; }
    
    virtual void setPosition(const vec3& position);
    
    const std::vector<CollidableSurface>& getCollidableSurfaces() const { return _collidableSurfaces; }
    
    bool doesCollidesWithBall(const vec2& ballPosition, const vec2& ballDesiredPosition, const float radius, const float distanceToTravel);

protected:
    std::vector<CollidableSurface> _collidableSurfaces;
    virtual void calculateCollidableSurfaces(const std::vector<KMVertex>& vertices);
    std::string _tag;
    
};

#endif /* defined(__Arkanoid__ArkanoidGameObject__) */
