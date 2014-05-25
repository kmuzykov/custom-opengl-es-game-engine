//
//  ITouchSubscriber.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__ITouchSubscriber__
#define __Arkanoid__ITouchSubscriber__

#include "Vector.hpp"

class ITouchSubscriber
{
public:
    virtual void touchBegan(const vec2& location) = 0;
    virtual void touchMoved(const vec2& location) = 0;
    virtual void touchEnded(const vec2& location) = 0;
};

#endif /* defined(__Arkanoid__ITouchSubscriber__) */
