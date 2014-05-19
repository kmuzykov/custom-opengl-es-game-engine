//
//  KMMaterialTextureDiffuse.h
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMMaterialTextureDiffuse__
#define __KMEngine__KMMaterialTextureDiffuse__

#include "KMMaterialTextureUnlit.h"
#include "KMTexture.h"

class KMMaterialTextureDiffuse : public KMMaterialTextureUnlit
{
public:
    KMMaterialTextureDiffuse(const KMTexture& texture);
    
    virtual void setUniforms(const mat4& mvm);

protected:
    GLuint _lightsCountUniform;
    GLuint _lightsPosUniform;
    GLuint _lightsIntensityUniform;
    GLuint _normalMatrixUniform;

public:
    static const char* u_lights_count;
    static const char* u_lights_pos;
    static const char* u_lights_intensity;
    static const char* u_normalMatrix;
};


#endif /* defined(__Bowling__KMMaterialTextureDiffuse__) */
