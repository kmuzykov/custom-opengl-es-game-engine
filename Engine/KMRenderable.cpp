//
//  P3DDrawable.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMRenderable.h"
#include "KMMacros.h"
#include "KMDirector.h"


KMRenderable::KMRenderable(KMShader shader, std::vector<KMVertex> vertices)
: KMNode(), _shader(shader)
{
    _useIndices = false;
    _elementsCount = vertices.size();
    
    _positionAttrib = glGetAttribLocation(_shader.getGLProgram(), "a_position");
    _textureCoordsAttrib = glGetAttribLocation(_shader.getGLProgram(), "a_texCoords");
    _normalAttrib = glGetAttribLocation(_shader.getGLProgram(), "a_normal");
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
}

KMRenderable::KMRenderable(KMShader shader, std::vector<KMVertex> vertices, std::vector<GLushort> indices)
: KMRenderable(shader, vertices)
{
    _useIndices = true;
    _elementsCount = indices.size();
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
}

KMRenderable::~KMRenderable()
{
    glDeleteBuffers(1, &_vertexBuffer);
    
    if (_useIndices)
        glDeleteBuffers(1, &_indexBuffer);
}

void KMRenderable::addModule(std::unique_ptr<KMRenderableModule> module)
{
    //giving a chance to get uniform locations
    module->onAdd(this, _shader);
    
    //TODO: Check for compatability with already existing modules
    _modules.push_back(std::move(module));
}

void KMRenderable::draw()
{
    //shader
    glUseProgram(_shader.getGLProgram());
    
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    CHECK_GL_ERROR();
    
    //vbo's
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    
    if (_useIndices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    //offset & stride for attribs
    const GLsizei stride = sizeof(KMVertex);
    const GLvoid* positionOffset = 0;
    const GLvoid* normalOffset = (GLvoid*)offsetof(KMVertex, normal);
    const GLvoid* texCoordsOffset = (GLvoid*)offsetof(KMVertex, texCoords);
    
    //position attrib
    if (_positionAttrib >= 0)
    {
        glEnableVertexAttribArray(_positionAttrib);
        glVertexAttribPointer(_positionAttrib, 3, GL_FLOAT, GL_FALSE, stride, positionOffset);
    }
    
    //normal attrib
    if (_normalAttrib >= 0)
    {
        glEnableVertexAttribArray(_normalAttrib);
        glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, stride, normalOffset);
    }

    //texture corods attrib
    if (_textureCoordsAttrib >= 0)
    {
        glEnableVertexAttribArray(_textureCoordsAttrib);
        glVertexAttribPointer(_textureCoordsAttrib, 2, GL_FLOAT, GL_FALSE, stride, texCoordsOffset);
    }
    
    //mvm matrix
    mat4 mvm = this->modelViewMatrix(true);
    GLuint mvmUniform = glGetUniformLocation(_shader.getGLProgram(), "u_mvMatrix");
    glUniformMatrix4fv(mvmUniform, 1, 0, mvm.Pointer());
    
    //projection matrix
    const mat4& pMatrix = KMDirector::getSharedDirector().getProjectionMatrix();
    GLuint pMatrixUniform = glGetUniformLocation(_shader.getGLProgram(), "u_pMatrix");
    glUniformMatrix4fv(pMatrixUniform, 1, 0, pMatrix.Pointer());
    
    CHECK_GL_ERROR();
    
    //Modules: PRE-RENDER
    for (auto& module : _modules)
    {
        module->preRender();
    }
    
    //RENDER
    if (_useIndices)
        glDrawElements(GL_TRIANGLES, _elementsCount, GL_UNSIGNED_SHORT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, _elementsCount);
    
    CHECK_GL_ERROR();
    
    //Modules: POST-RENDER
    for (auto& module : _modules)
    {
        module->postRender();
    }
   
    //cleanup: attribs
    if (_positionAttrib >= 0)
        glDisableVertexAttribArray(_positionAttrib);
    
    if (_normalAttrib >= 0)
        glDisableVertexAttribArray(_normalAttrib);
    
    if(_textureCoordsAttrib >= 0)
        glDisableVertexAttribArray(_textureCoordsAttrib);
    
    CHECK_GL_ERROR();
    
    //cleanup: buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (_useIndices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //cleanup: shaders
    glUseProgram(0);
    
    CHECK_GL_ERROR();
}