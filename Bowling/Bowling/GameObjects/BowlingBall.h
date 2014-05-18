//
//  BowlingBall.h
//  Bowling
//
//  Created by Kirill Muzykov on 14/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__BowlingBall__
#define __Bowling__BowlingBall__

#include "KMGameObject.h"

class btCollisionShape;

class BowlingBall : public KMGameObject
{
public:
    BowlingBall();

private:
    static btCollisionShape* createShape();
};

#endif /* defined(__Bowling__BowlingBall__) */
