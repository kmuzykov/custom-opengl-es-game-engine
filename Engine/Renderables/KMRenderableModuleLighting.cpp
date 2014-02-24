//
//  KMRenderableTexturedLightened.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 19/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMRenderableModuleLighting.h"
#include "KMRenderable.h"
#include "KMLightSourceNode.h"
#include "KMMacros.h"

KMRenderableModuleLighting::KMRenderableModuleLighting()
: _light0(nullptr), _light1(nullptr), _light2(nullptr)
{
}

void KMRenderableModuleLighting::onAdd(KMRenderable* owner, const KMShader& shader)
{
    KMRenderableModule::onAdd(owner, shader);
    
    _normalMatrixUniform = glGetUniformLocation(shader.getGLProgram(), "u_normalMatrix");
    
    _light0PositionUniform = glGetUniformLocation(shader.getGLProgram(), "u_light0_pos");
    _light0IntensityUniform = glGetUniformLocation(shader.getGLProgram(), "u_light0_intensity");
    
    _light1PositionUniform = glGetUniformLocation(shader.getGLProgram(), "u_light1_pos");
    _light1IntensityUniform = glGetUniformLocation(shader.getGLProgram(), "u_light1_intensity");
    
    _light2PositionUniform = glGetUniformLocation(shader.getGLProgram(), "u_light2_pos");
    _light2IntensityUniform = glGetUniformLocation(shader.getGLProgram(), "u_light2_intensity");
    
    
    if (_light0PositionUniform <= 0 && _light1PositionUniform <= 0 && _light2PositionUniform <= 0)
        KMLOG("KMRenderableModuleLighting: Shader doesn't contain any light position uniform");
}

void KMRenderableModuleLighting::preRender()
{
    mat3 normalMatrix = _owner->modelViewMatrix(true).ToMat3();
    glUniformMatrix3fv(_normalMatrixUniform, 1, 0, normalMatrix.Pointer());
    
    if (_light0)
    {
        //This pos# manipulations are required so that the light didn't moved with the scene (or other parent)
        vec4 pos0(_light0->getPosition(), 1);
        if (_light0->_parent)
        {
            mat4 parentModelView = _light0->_parent->modelViewMatrix(true);
            pos0 = parentModelView.Transposed() * pos0; //note transposed matrix, it differs from what used with OpenGL
        }
        
        glUniform3fv(_light0PositionUniform, 1, pos0.Pointer());
        glUniform1f(_light0IntensityUniform, _light0->getIntensity());
    }
    
    if (_light1)
    {
        vec4 pos1(_light1->getPosition(), 1);
        if (_light1->_parent)
        {
            mat4 parentModelView = _light1->_parent->modelViewMatrix(true);
            pos1 = parentModelView.Transposed() * pos1;
        }
        
        glUniform3fv(_light1PositionUniform, 1, pos1.Pointer());
        glUniform1f(_light1IntensityUniform, _light1->getIntensity());
    }
    
    if (_light2)
    {
        vec4 pos2(_light2->getPosition(), 1);
        if (_light2->_parent)
        {
            mat4 parentModelView = _light2->_parent->modelViewMatrix(true);
            pos2 = parentModelView.Transposed() * pos2;
        }
        
        glUniform3fv(_light2PositionUniform, 1, pos2.Pointer());
        glUniform1f(_light2IntensityUniform, _light2->getIntensity());
    }
}

void KMRenderableModuleLighting::postRender()
{
}

void KMRenderableModuleLighting::setLight0(std::shared_ptr<KMLightSourceNode> light0)
{
    if (light0 && !light0->_parent)
        KMLOG("Adding light0 without parent (not in scene or node) is not reccomended");
    
    _light0 = light0;
}

void KMRenderableModuleLighting::setLight1(std::shared_ptr<KMLightSourceNode> light1)
{
    if (light1 && !light1->_parent)
        KMLOG("Adding light1 without parent (not in scene or node) is not reccomended");
    
    _light1 = light1;
}

void KMRenderableModuleLighting::setLight2(std::shared_ptr<KMLightSourceNode> light2)
{
    if (light2 && !light2->_parent)
        KMLOG("Adding light2 without parent (not in scene or node) is not reccomended");
    
    _light2 = light2;
}

