//
//  KMMaterialTextureDiffuse.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMMaterialTextureDiffuse.h"
#include "KMShader.h"
#include "KMDirector.h"
#include "KMScene.h"

const char* KMMaterialTextureDiffuse::u_lights_count = "u_lights_count";
const char* KMMaterialTextureDiffuse::u_lights_pos = "u_lights_pos";
const char* KMMaterialTextureDiffuse::u_lights_intensity = "u_lights_intensity";
const char* KMMaterialTextureDiffuse::u_normalMatrix = "u_normalMatrix";

KMMaterialTextureDiffuse::KMMaterialTextureDiffuse(const KMTexture& texture)
 : KMMaterialTextureUnlit(texture, KMShader::make("textureDiffuse"))
{
    _lightsCountUniform = glGetUniformLocation(_shader->getGLProgram(), u_lights_count);
    _lightsPosUniform = glGetUniformLocation(_shader->getGLProgram(), u_lights_pos);
    _lightsIntensityUniform = glGetUniformLocation(_shader->getGLProgram(), u_lights_intensity);
    _normalMatrixUniform = glGetUniformLocation(_shader->getGLProgram(), u_normalMatrix);
}

void KMMaterialTextureDiffuse::setUniforms(const mat4& mvm)
{
    KMMaterialTextureUnlit::setUniforms(mvm);

    //Getting scene
    auto scene =  KMDirector::getSharedDirector().getCurrenScene();

    //NOTE: This doesn't work correctly in 2 cases
    //1: If we move the scene (since its model view moves with it)
    //2: If we want to add light sources to a moving object (this currently is not supported at all)
    mat3 normalMatrix = scene->modelViewMatrix(true).ToMat3();
    glUniformMatrix3fv(_normalMatrixUniform, 1, 0, normalMatrix.Pointer());
    
    //Getting light positions and intensities
    const std::vector<vec3>& ligtPositions = scene->getLightSources();
    const std::vector<float>& lightIntensities = scene->getLightIntensities();
    
    //Passing lights and their intesity as uniforms
    glUniform3fv(_lightsPosUniform, (GLsizei)ligtPositions.size(), (GLfloat*)&ligtPositions[0]);
    glUniform1fv(_lightsIntensityUniform, (GLsizei)lightIntensities.size(), (GLfloat*)&lightIntensities[0]);
    
    //Passing count of currently used lights
    glUniform1i(_lightsCountUniform, (GLsizei)ligtPositions.size());
}