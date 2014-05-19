//
//  P3DFileUtils.h
//  Bowling
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMFileUtils.h"

/** iOS implementation of file utils */
class KMFileUtilsIOS : public KMFileUtils
{
public:
    virtual const char* loadFile(const char* fileName);
    virtual const char* getFilePath(const char* fileName);
    virtual GLuint loadTexture(const char* imgName);
};
