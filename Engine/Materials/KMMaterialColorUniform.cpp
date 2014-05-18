//
//  KMMaterialColorUniform.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 14/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMMaterialColorUniform.h"

const char* KMMaterialColorUniform::u_color = "u_color";

KMMaterialColorUniform::KMMaterialColorUniform(vec3 color)
 :  KMMaterial(std::make_shared<KMShader>("uniform_color.vsh", "uniform_color.fsh")),
   _color(color)
{
    _colorUniform = glGetUniformLocation(_shader->getGLProgram(), u_color);
}

void KMMaterialColorUniform::setUniforms(const mat4& mvm)
{
    KMMaterial::setUniforms(mvm);
    glUniform4fv(_colorUniform, 1, _color.Pointer());    
}