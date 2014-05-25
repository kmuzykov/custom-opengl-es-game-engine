//
//  Brick.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__Brick__
#define __Arkanoid__Brick__

#include "KMEngine.h"
#include "ArkanoidGameObject.h"

class Level;

class Brick : public ArkanoidGameObject
{
    friend class Level;
public:
    Brick();
    const virtual ArkanoidGameObjectType getObjectType() const {return ArkanoidGameObjectType::Brick;}
    
private:
    static const std::vector<KMVertex>& getBrickVertices();
};


#endif /* defined(__Arkanoid__Brick__) */
