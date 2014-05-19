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
#include <vector>

class btCollisionShape;
class KMVertex;

class BowlingPin : public KMGameObject
{
public:
    BowlingPin(const vec3& position);
private:
    static btCollisionShape* createShape(const std::vector<KMVertex>& pinVertices);
    static const std::vector<KMVertex>& cachedVertices();
};


#endif /* defined(__Bowling__BowlingPin__) */
