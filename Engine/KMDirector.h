//
//  KMDirector.h
//  KMEngine
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__P3DDirector__
#define __KMEngine__P3DDirector__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <memory>

#include "Matrix.hpp"

class KMScene;

class KMDirector
{
public:
    void initialize(int width, int height, float scaleFactor);
    void validateInit();
    
    void update(float dt);
    void runScene(std::shared_ptr<KMScene> scene);
    std::shared_ptr<KMScene>& getCurrenScene() { return _currentScene;}
    
    int getViewWidth() const { return _viewWidth; }
    int getViewHeight() const { return _viewHeight; }
    int getViewWidthInPixels() const {return _viewWidthInPixels; }
    int getViewHeightInPixels() const {return _viewHeightInPixels; }
    int getScaleFactor() const { return _scaleFactor; }
    
    const mat4& getProjectionMatrix() const { return _projectionMatrix; }
    
    static KMDirector& getSharedDirector();
private:
    GLuint _frameBuffer;
    GLuint _colorBuffer;
    GLuint _depthBuffer;
    
    int _viewWidth;
    int _viewHeight;
    int _viewWidthInPixels;
    int _viewHeightInPixels;
    float _scaleFactor;
    
    mat4 _projectionMatrix;
    
    std::shared_ptr<KMScene> _currentScene;
    
    KMDirector() {};
    KMDirector(const KMDirector& that) = delete;
};

#endif /* defined(__Bowling__P3DDirector__) */
