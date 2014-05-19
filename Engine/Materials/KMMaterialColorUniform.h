//
//  KMMaterialColorUniform.h
//  Bowling
//
//  Created by Kirill Muzykov on 14/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMMaterialColorUniform__
#define __Bowling__KMMaterialColorUniform__

#include "KMMaterial.h"

class KMMaterialColorUniform : public KMMaterial
{
public:
    KMMaterialColorUniform(const vec3& color);
    virtual void setUniforms(const mat4& mvm);

protected:
    GLint _colorUniform;
    vec3 _color;

public:
    static const char* u_color;
};

#endif /* defined(__Bowling__KMMaterialColorUniform__) */
