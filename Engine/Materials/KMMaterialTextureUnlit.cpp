//
//  TextureUnlit.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMMaterialTextureUnlit.h"
#include "KMMacros.h"

const char* KMMaterialTextureUnlit::u_texture0 = "u_texture0";

KMMaterialTextureUnlit::KMMaterialTextureUnlit(const KMTexture texture)
:  KMMaterialTextureUnlit(texture, KMShader::make("textured"))
{
}

KMMaterialTextureUnlit::KMMaterialTextureUnlit(const KMTexture texture, std::shared_ptr<KMShader> shader)
: KMMaterial(shader),
  _texture(texture)
{
    _textureUniform = glGetUniformLocation(_shader->getGLProgram(), u_texture0);
}

void KMMaterialTextureUnlit::setUniforms(const mat4& mvm)
{
    KMMaterial::setUniforms(mvm);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.getTextureName());
    glUniform1i(_textureUniform, 0);
    
    CHECK_GL_ERROR();
}

void KMMaterialTextureUnlit::clearUniforms()
{
    glBindTexture(GL_TEXTURE_2D, 0);    
    CHECK_GL_ERROR();
}

