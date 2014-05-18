//
//  BowlingPin.h
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__BowlingPin__
#define __Bowling__BowlingPin__

#include "KMGameObject.h"

class btCollisionShape;

class BowlingPin : public KMGameObject
{
public:
    BowlingPin();
    
private:
    static btCollisionShape* createShape();
};


#endif /* defined(__Bowling__BowlingPin__) */
