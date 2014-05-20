//
//  KMDirector.cpp
//  KMEngine
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMDirector.h"
#include "KMMacros.h"
#include "KMScene.h"

void KMDirector::initialize(int width, int height, float scaleFactor)
{
    _currentScene = nullptr;
    _scaleFactor = scaleFactor;
    
    _viewWidth = width;
    _viewHeight = height;
    _viewWidthInPixels = width * scaleFactor;
    _viewHeightInPixels = height * scaleFactor;
    
    //Frustum
    //GLfloat size = 0.25f * tanf(DEGREES_TO_RADIANS(90.0) / 2.0);
    //float aspectRatio = (float)_viewWidthInPixels/(float)_viewHeightInPixels;
    //_projectionMatrix = mat4::Frustum(-size, size, -size * aspectRatio, size * aspectRatio, 0.1, 1000);
    
    // Create a new perspective projection matrix. The height will stay the same
    // while the width will vary as per aspect ratio.
    float ratio = (float)height/(float)width;
    float left = -ratio;
    float right = ratio;
    float bottom = -1.0;
    float top = 1.0;
    float near = 2;
    float far = 100.0;
    _projectionMatrix = mat4::Frustum(left, right, bottom, top, near, far);
    
    glGenBuffers(1, &_frameBuffer);
    glGenBuffers(1, &_colorBuffer);
    glGenBuffers(1, &_depthBuffer);
    
    //FRAME & COLOR
    glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorBuffer);
    
    //DEPTH
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, _viewWidthInPixels, _viewHeightInPixels);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
    
    glViewport(0, 0, _viewWidthInPixels, _viewHeightInPixels);
    
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void KMDirector::validateInit()
{
    //Checking frame buffer for completeness
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        KMLOG("Failed to make complete framebuffer object :%d",status);
    }
    else
    {
        KMLOG("Framebuffer Complete");
    }
}

void KMDirector::update(float dt)
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (_currentScene)
    {
        _currentScene->update(dt);
        _currentScene->draw();
    }
}

void KMDirector::runScene(std::shared_ptr<KMScene> scene)
{
    //TODO: Check    
    _currentScene = scene;
}

KMDirector& KMDirector::getSharedDirector()
{
    static KMDirector _sharedDirector;
    return _sharedDirector;
};
