//
//  KMComponent.h
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMComponent__
#define __Bowling__KMComponent__

#include "Matrix.hpp"

class KMComponent
{
public:
    virtual void render(const mat4& mvm) = 0;
};

#endif /* defined(__Bowling__KMComponent__) */
