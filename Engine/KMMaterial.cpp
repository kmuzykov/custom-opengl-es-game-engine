//
//  KMMaterial.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMMaterial.h"
#include "KMMacros.h"
#include "KMVertex.h"
#include "KMDirector.h"
#include "Matrix.hpp"

const char* KMMaterial::a_position  = "a_position";
const char* KMMaterial::a_texCoords = "a_texCoords";
const char* KMMaterial::a_normal = "a_normal";

const char* KMMaterial::u_mvMatrix = "u_mvMatrix";
const char* KMMaterial::u_pMatrix = "u_pMatrix";


KMMaterial::KMMaterial(std::shared_ptr<KMShader> shader):_shader(shader)
{
    _positionAttrib      = glGetAttribLocation(_shader->getGLProgram(), a_position);
    _textureCoordsAttrib = glGetAttribLocation(_shader->getGLProgram(), a_texCoords);
    _normalAttrib        = glGetAttribLocation(_shader->getGLProgram(), a_normal);
    
    _modelViewUniform = glGetUniformLocation(_shader->getGLProgram(), u_mvMatrix);
    _projectionUniform = glGetUniformLocation(_shader->getGLProgram(), u_pMatrix);
}

void KMMaterial::useProgram()
{
    glUseProgram(_shader->getGLProgram());
    CHECK_GL_ERROR();
}

void KMMaterial::setBlendingFunc()
{
    //TODO: Add flag to enable, disable function and set SRC and DST
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    CHECK_GL_ERROR();
}

void KMMaterial::setAtrributes()
{
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
}

void KMMaterial::setUniforms(const mat4& mvm)
{
    //mvm matrix
    glUniformMatrix4fv(_modelViewUniform, 1, 0, mvm.Pointer());
    
    //projection matrix
    const mat4& pMatrix = KMDirector::getSharedDirector().getProjectionMatrix();
    glUniformMatrix4fv(_projectionUniform, 1, 0, pMatrix.Pointer());
}

void KMMaterial::clearAttributes()
{
    //cleanup: attribs
    if (_positionAttrib >= 0)
        glDisableVertexAttribArray(_positionAttrib);
    
    if (_normalAttrib >= 0)
        glDisableVertexAttribArray(_normalAttrib);
    
    if(_textureCoordsAttrib >= 0)
        glDisableVertexAttribArray(_textureCoordsAttrib);
    
    CHECK_GL_ERROR();
}

void KMMaterial::clearUniforms()
{
    //Right now we have nothing to do here
}

void KMMaterial::clearProgram()
{
    glUseProgram(0);
    CHECK_GL_ERROR();    
}

