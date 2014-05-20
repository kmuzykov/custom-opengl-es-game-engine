//
//  TextureUnlit.h
//  KMEngine
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__TextureUnlit__
#define __KMEngine__TextureUnlit__

#include "KMMaterial.h"
#include "KMTexture.h"

class KMMaterialTextureUnlit : public KMMaterial
{
public:
    KMMaterialTextureUnlit(const KMTexture& texture);
    
    virtual void setUniforms(const mat4& mvm);
    virtual void clearUniforms();

protected:
    KMMaterialTextureUnlit(const KMTexture texture, std::shared_ptr<KMShader> shader); //Special constructor for diffuse mat
    const KMTexture _texture; //TODO: Texture cache and store reference here
    GLint _textureUniform;

public:
    static const char * u_texture0;
};


#endif /* defined(__KMEngine__TextureUnlit__) */
