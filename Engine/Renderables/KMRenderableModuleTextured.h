//
//  KMRenderableTextured.h
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMRenderableTextured__
#define __Bowling__KMRenderableTextured__

#include "KMRenderable.h"
#include "KMTexture.h"

#include <vector>
#include <memory>


class KMRenderableModuleTextured : public KMRenderableModule
{
public:
    KMRenderableModuleTextured(const KMTexture& texture);
    KMRenderableModuleTextured(const KMTexture& texture, unsigned int textureNumber);

public:
    virtual KMRenderableModuleType getModuleType() { return KMRenderableModuleType::Texture; }
protected:
    virtual void onAdd(KMRenderable* owner, const KMShader& shader);
    virtual void preRender();
    virtual void postRender();
    
private:
    KMTexture _texture;
    unsigned int _textureNumber;
    GLint _textureUniform;
};

#endif /* defined(__Bowling__KMRenderableTextured__) */
