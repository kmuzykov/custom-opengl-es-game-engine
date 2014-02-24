//
//  KMRenderableTextured.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMRenderableModuleTextured.h"
#include "KMMacros.h"


KMRenderableModuleTextured::KMRenderableModuleTextured(const KMTexture& texture)
 : KMRenderableModuleTextured(texture, 0)
{
   
}

KMRenderableModuleTextured::KMRenderableModuleTextured(const KMTexture& texture, unsigned int textureNumber)
: _texture(texture), _textureNumber(textureNumber)
{
    
}

void KMRenderableModuleTextured::onAdd(KMRenderable* owner, const KMShader& shader)
{
    KMRenderableModule::onAdd(owner, shader);
    
    char textureUniformName[256] = "";
    sprintf(textureUniformName, "u_texture%d", _textureNumber);
    _textureUniform = glGetUniformLocation(shader.getGLProgram(), textureUniformName);

    if (_textureUniform < 0)
        KMLOG("KMRenderableModuleUniformColorc can't find '%s' uniform in shader program.", textureUniformName);
}

void KMRenderableModuleTextured::preRender()
{
    glActiveTexture(GL_TEXTURE0 + _textureNumber);
    glBindTexture(GL_TEXTURE_2D, _texture.getTextureName());
    glUniform1i(_textureUniform, _textureNumber);
    
    CHECK_GL_ERROR();
}

void KMRenderableModuleTextured::postRender()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}