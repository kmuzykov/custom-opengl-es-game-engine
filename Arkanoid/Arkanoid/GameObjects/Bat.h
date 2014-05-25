//
//  Bat.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__Bat__
#define __Arkanoid__Bat__

#include "KMEngine.h"
#include "ArkanoidGameObject.h"

class Bat : public ArkanoidGameObject
{
public:
    Bat();
    const virtual ArkanoidGameObjectType getObjectType() const {return ArkanoidGameObjectType::Bat;}

    virtual void setPosition(const vec3& position);
    
    void setDesiredPosition(const float x);
    void applyDesiredPosition();
    
private:
    float _desiredPosition;
};


#endif /* defined(__Arkanoid__Bat__) */
