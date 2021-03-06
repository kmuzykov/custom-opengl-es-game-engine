//
//  KMMaterial.h
//  KMEngine
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMMaterial__
#define __KMEngine__KMMaterial__

#include <memory>
#include <OpenGLES/ES2/gl.h>
#include "Matrix.hpp"

class KMShader;

class KMMaterial
{
public:
    KMMaterial(std::shared_ptr<KMShader> shader);
    
    void useProgram();
    void setBlendingFunc();
    
    virtual void setAtrributes();
    virtual void setUniforms(const mat4& mvm);

    virtual void clearAttributes();
    virtual void clearUniforms();

    void clearProgram();

protected:    
    std::shared_ptr<KMShader> _shader;    
    GLint _positionAttrib;
    GLint _textureCoordsAttrib;
    GLint _normalAttrib;
    
    GLint _modelViewUniform;
    GLint _projectionUniform;

public:
    static const char* a_position;
    static const char* a_texCoords;
    static const char* a_normal;
    
    static const char* u_mvMatrix;
    static const char* u_pMatrix;
};

#endif /* defined(__Bowling__KMMaterial__) */
