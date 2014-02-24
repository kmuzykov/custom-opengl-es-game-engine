//
//  P3DFileUtils.h
//  Bowling
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__P3DFileUtils__
#define __Bowling__P3DFileUtils__

#include <memory>
#include <OpenGLES/ES2/gl.h>

class KMTexture;

class KMFileUtils
{
public:
    static KMFileUtils& getSharedFileUtils();
    virtual const char* loadFile(const char* fileName) = 0;
    virtual const char* getFilePath(const char* fileName) = 0;
    virtual GLuint loadTexture(const char* imgName) = 0;
};

#endif /* defined(__Bowling__P3DFileUtils__) */
