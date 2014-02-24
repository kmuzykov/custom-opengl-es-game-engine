//
//  KMRenderableColored.h
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMRenderableColored__
#define __Bowling__KMRenderableColored__

#include "KMRenderable.h"
#include "Vector.hpp"

class KMRenderableModuleUniformColor : public KMRenderableModule
{
public:
    KMRenderableModuleUniformColor(vec4 color);
    
    virtual KMRenderableModuleType getModuleType() { return KMRenderableModuleType::UniformColor; }
    
    vec4 getColor() const { return _color; }
    void setColor(const vec4& color) { _color = color; }
    
protected:
    virtual void onAdd(KMRenderable* owner, const KMShader& shader);
    virtual void preRender();
    virtual void postRender();
    
private:
    vec4 _color;
    GLint _colorUniformLocation;
};


#endif /* defined(__Bowling__KMRenderableColored__) */
