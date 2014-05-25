//
//  SideWall.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 24/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__SideWall__
#define __Arkanoid__SideWall__

#include "ArkanoidGameObject.h"

class SideWall : public ArkanoidGameObject
{
public:
    SideWall();

    const virtual ArkanoidGameObjectType getObjectType() const {return ArkanoidGameObjectType::Wall;}
};

#endif /* defined(__Arkanoid__SideWall__) */
