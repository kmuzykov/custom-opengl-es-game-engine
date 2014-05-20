//
//  KMRenderer.h
//  KMEngine
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMRenderer__
#define __KMEngine__KMRenderer__

#include "Matrix.hpp"

class KMRenderer
{
public:
    virtual void render(const mat4& mvm) = 0;
};


#endif /* defined(__Bowling__KMRenderer__) */
