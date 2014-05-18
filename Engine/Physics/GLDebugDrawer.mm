//
//  GLDebugDrawer.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "GLDebugDrawer.h"

#include <stdio.h> //printf debugging
#include "Vector.hpp"
#include "Matrix.hpp"
#include "KMDirector.h"
#include "KMScene.h"
#include "KMMacros.h"

GLDebugDrawer::GLDebugDrawer()
:m_debugMode(1),
 _shader("uniform_color.vsh", "uniform_color.fsh")
{
    
}

void GLDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
    vec3 elemens[] = {vec3(from.x(),from.y(), from.z()),  vec3(to.x(), to.y(), to.z())};
    
    glUseProgram(_shader.getGLProgram());
    
    GLuint pos = glGetAttribLocation(_shader.getGLProgram(), "a_position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, &elemens[0]);
    
    auto scene = KMDirector::getSharedDirector().getCurrenScene();    
    mat4 mvmMatrix = scene->modelViewMatrix(true);
    mat4 projMatrix = KMDirector::getSharedDirector().getProjectionMatrix();
    GLuint mvmUniform  = glGetUniformLocation(_shader.getGLProgram(), "u_mvMatrix");
    GLuint projUniform = glGetUniformLocation(_shader.getGLProgram(), "u_pMatrix");
    
    glUniformMatrix4fv(mvmUniform, 1, 0, mvmMatrix.Pointer());
    glUniformMatrix4fv(projUniform, 1, 0, projMatrix.Pointer());
    
    GLuint colorUniform =  glGetUniformLocation(_shader.getGLProgram(), "u_color");
    glUniform4fv(colorUniform, 1, vec3(color.x(), color.y(), color.z()).Pointer());
    
    glDrawArrays(GL_LINES, 0, 2);
}

void GLDebugDrawer::setDebugMode(int debugMode)
{
    m_debugMode = debugMode;
}

void    GLDebugDrawer::draw3dText(const btVector3& location,const char* textString)
{
    //glRasterPos3f(location.x(),  location.y(),  location.z());
    //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
}

void GLDebugDrawer::reportErrorWarning(const char* warningString)
{
   KMLOG(warningString);
}

void GLDebugDrawer::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{
    {
        //btVector3 to=pointOnB+normalOnB*distance;
        //const btVector3&from = pointOnB;
        //glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);
        
        //GLDebugDrawer::drawLine(from, to, color);
        
        //glRasterPos3f(from.x(),  from.y(),  from.z());
        //char buf[12];
        //sprintf(buf," %d",lifeTime);
        //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
    }
}