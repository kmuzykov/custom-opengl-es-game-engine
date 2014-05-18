//
//  BowlingLane.h
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__BowlingLane__
#define __Bowling__BowlingLane__

#include "KMGameObject.h"
#include <vector>

class btCollisionShape;
class KMVertex;

class BowlingLane : public KMGameObject
{
public:
    BowlingLane();
private:
    static btCollisionShape* createShape(const std::vector<KMVertex>& laneVertices);
};


#endif /* defined(__Bowling__BowlingLane__) */
