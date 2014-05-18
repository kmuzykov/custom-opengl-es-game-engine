//
//  KMRendererMesh.h
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMRendererMesh__
#define __Bowling__KMRendererMesh__

#include "KMRenderer.h"
#include "KMMaterial.h"
#include "KMVertex.h"

#include <memory>
#include <vector>

class KMRendererMesh : public KMRenderer
{
public:
    KMRendererMesh(std::shared_ptr<KMMaterial> material, std::vector<KMVertex> vertices);
    KMRendererMesh(std::shared_ptr<KMMaterial> material, std::vector<KMVertex> vertices, std::vector<GLushort> indices);
    virtual ~KMRendererMesh();
    
    virtual void render(const mat4& mvm);    
protected:
    bool _useIndices;
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    GLushort _elementsCount;
    
    GLint _positionAttrib;
    GLint _textureCoordsAttrib;
    GLint _normalAttrib;
    
    std::shared_ptr<KMMaterial> _material;
};

#endif /* defined(__Bowling__KMRendererMesh__) */
