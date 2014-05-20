//
//  KMTexture.h
//  KMEngine
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMTexture__
#define __KMEngine__KMTexture__

#include <OpenGLES/ES2/gl.h>

/** Texture unit */
class KMTexture
{
public:
    KMTexture(const char* fileName);
    inline GLuint getTextureName() const {return _name;}
    
private:
    GLuint _name;
    static unsigned int nextPot(unsigned int n);
};

#endif /* defined(__Bowling__KMTexture__) */
