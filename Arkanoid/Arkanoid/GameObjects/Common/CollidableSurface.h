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

class CollidableSurface
{
public:
    CollidableSurface(const vec2& p1, const vec2& p2);

private:
    vec2 _p1;
    vec2 _p2;
};

#endif /* defined(__Arkanoid__CollidableSurface__) */
