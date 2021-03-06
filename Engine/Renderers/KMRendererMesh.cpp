//
//  KMRendererMesh.cpp
//  KMEngine
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMRendererMesh.h"
#include "KMMacros.h"
#include "KMConfig.h"

KMRendererMesh::KMRendererMesh(std::shared_ptr<KMMaterial> material, std::vector<KMVertex> vertices)
: _material(material)
{
    _useIndices = false;
    _elementsCount = vertices.size();
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

KMRendererMesh::KMRendererMesh(std::shared_ptr<KMMaterial> material, std::vector<KMVertex> vertices, std::vector<GLushort> indices)
: KMRendererMesh(material, vertices)
{
    //We've called second constructor so all we need is to override some values and generate indices VBO
    _useIndices = true;
    _elementsCount = indices.size();

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

KMRendererMesh::~KMRendererMesh()
{
    glDeleteBuffers(1, &_vertexBuffer);
    
    if (_useIndices)
        glDeleteBuffers(1, &_indexBuffer);
}

void KMRendererMesh::render(const mat4& mvm)
{
#if KM_RENDER_ENABLED > 0
    _material->useProgram();
    _material->setBlendingFunc();
    
    //VBO's
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    
    if (_useIndices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

    _material->setAtrributes();    
    _material->setUniforms(mvm);
    
    //RENDER
    if (_useIndices)
        glDrawElements(GL_TRIANGLES, _elementsCount, GL_UNSIGNED_SHORT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, _elementsCount);
    CHECK_GL_ERROR();
    
    _material->clearAttributes();
    _material->clearUniforms();
    
    //Cleanup: VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (_useIndices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    _material->clearProgram();
#endif
}