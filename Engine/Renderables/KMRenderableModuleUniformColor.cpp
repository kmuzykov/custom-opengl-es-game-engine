//
//  KMRenderableColored.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMRenderableModuleUniformColor.h"
#include "KMMacros.h"

#include <OpenGLES/ES2/gl.h>


KMRenderableModuleUniformColor::KMRenderableModuleUniformColor(vec4 color)
: _color(color)
{
    
}

void KMRenderableModuleUniformColor::onAdd(KMRenderable* owner, const KMShader& shader)
{
    KMRenderableModule::onAdd(owner, shader);
    
    _colorUniformLocation = glGetUniformLocation(shader.getGLProgram(), "u_color");
    if (_colorUniformLocation < 0)
    {
        KMLOG("KMRenderableModuleUniformColorc can't find 'u_color' uniform in shader program.");
        return;    }
    
    CHECK_GL_ERROR();
}

void KMRenderableModuleUniformColor::preRender()
{
    glUniform4fv(_colorUniformLocation, 1, _color.Pointer());
    CHECK_GL_ERROR();
};

void KMRenderableModuleUniformColor::postRender()
{
}
