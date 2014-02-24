//
//  P3DShader.cpp
//  Pixel3D
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMShader.h"
#include "KMMacros.h"
#include "KMConfig.h"
#include "KMFileUtils.h"

#ifdef IOS
#include <CoreFoundation/CoreFoundation.h> //for exit(1);
#endif


KMShader::KMShader(const char* vertex, const char* fragment)
{
    const char* vertexSource = KMFileUtils::getSharedFileUtils().loadFile(vertex);
    const char* fragmentSource = KMFileUtils::getSharedFileUtils().loadFile(fragment);
    _glProgram = buildShaderProgram(vertexSource, fragmentSource);
}

KMShader::~KMShader()
{
    //glDeleteProgram(_glProgram); //this causes errors, even if program is no longer used.
}

GLuint KMShader::buildShader(const char* source, GLenum shaderType)
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE)
    {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        KMLOG("Error building shader: %s", messages);
        exit(1);
    }
    
    return shaderHandle;
}

GLuint KMShader::buildShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    GLuint vertexShader = buildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = buildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    
    if (linkSuccess == GL_FALSE)
    {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        KMLOG("Error building shaderProgram: %s", messages);
        exit(1);
    }
    
    return programHandle;
}

                        
