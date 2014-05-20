//
//  KMFileUtils.h
//  KMEngine
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMFileUtils__
#define __KMEngine__KMFileUtils__

#include <OpenGLES/ES2/gl.h>

class KMTexture;

/** 
    Single class that returns platform specific file utils instance 
 */
class KMFileUtils
{
public:
    virtual const char* loadFile(const char* fileName) = 0;
    virtual const char* getFilePath(const char* fileName) = 0;
    virtual GLuint loadTexture(const char* imgName) = 0;
 
    static KMFileUtils& getSharedFileUtils();
};

#endif /* defined(__Bowling__P3DFileUtils__) */
