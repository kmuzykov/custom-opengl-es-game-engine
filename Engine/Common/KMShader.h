//
//  P3DShader.h
//  Pixel3D
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMSHader_h
#define __KMSHader_h

#include <OpenGLES/ES2/gl.h>
#include <memory>

class KMShader
{
public:
    KMShader(const char* vertex, const char* fragment);
    virtual ~KMShader();
    
    GLuint getGLProgram() const { return _glProgram; }
    
    static std::shared_ptr<KMShader> make(const char* nameWithoutExtension);
    
private:
    GLuint _glProgram;
    
    static GLuint buildShader(const char* source, GLenum shaderType);
    static GLuint buildShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
    static const char* loadFile(const char* path);
};

#endif /* defined(__Bowling__P3DShader__) */
