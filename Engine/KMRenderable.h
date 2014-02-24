//
//  P3DDrawable.h
//  Bowling
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__P3DDrawable__
#define __Bowling__P3DDrawable__

#include <OpenGLES/ES2/gl.h>
#include <vector>
#include <map>

#include "KMShader.h"
#include "KMNode.h"
#include "Vector.hpp"
#include "KMVertex.h"
#include "KMRenderableModule.h"

class KMRenderable : public KMNode
{
public:
    KMRenderable(KMShader shader, std::vector<KMVertex> vertices);
    KMRenderable(KMShader shader, std::vector<KMVertex> vertices, std::vector<GLushort> indices);
    virtual ~KMRenderable();
    
    void addModule(std::unique_ptr<KMRenderableModule> module);
    
    virtual void draw();
protected:
    KMShader _shader;
    
private:
    std::vector<std::unique_ptr<KMRenderableModule>> _modules;

    bool _useIndices;
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    GLushort _elementsCount;
    
    GLint _positionAttrib;
    GLint _textureCoordsAttrib;
    GLint _normalAttrib;
};

#endif /* defined(__Bowling__P3DDrawable__) */
