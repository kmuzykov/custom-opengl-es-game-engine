//
//  KMRendererMesh.h
//  KMEngine
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMRendererMesh__
#define __KMEngine__KMRendererMesh__

#include "KMRenderer.h"
#include "KMMaterial.h"
#include "KMVertex.h"

#include <memory>
#include <vector>

/** Mesh Renderer. Renders models consisting of KMVertex vertices. */
class KMRendererMesh : public KMRenderer
{
public:
    /** Create Mesh with no indices (glDrawArrays) */
    KMRendererMesh(std::shared_ptr<KMMaterial> material, std::vector<KMVertex> vertices);
     
    /** Create Mesh that has indices (glDrawElements) */
    KMRendererMesh(std::shared_ptr<KMMaterial> material, std::vector<KMVertex> vertices, std::vector<GLushort> indices);

    virtual ~KMRendererMesh();
    
    virtual void render(const mat4& mvm);    
protected:
    //Flag if we use indices VBO
    bool _useIndices;
    
    //VBOs
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    GLushort _elementsCount;
    
    //Main attributes
    GLint _positionAttrib;
    GLint _textureCoordsAttrib;
    GLint _normalAttrib;
    
    //Material used by renderer (uniform color, texture, texture with light)
    std::shared_ptr<KMMaterial> _material;
};

#endif /* defined(__Bowling__KMRendererMesh__) */
