//
//  KMMacros.h
//  KMEngine
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef KM_Macros_h
#define KM_Macros_h

#ifdef DEBUG
#include <stdio.h>
#endif

/** Log to console
 */
#ifdef DEBUG
#define KMLOG(FORMAT, ...) printf(FORMAT, ##__VA_ARGS__)
#else
#define KMLOG(FORMAT, ...) do {} while (0)
#endif

/** Checking GL error function fron cocos2d-iphone project.
 */
#ifdef DEBUG
#define CHECK_GL_ERROR() ({ GLenum __error = glGetError(); if(__error) printf("OpenGL error 0x%04X in %s %d : %s \n", __error, __FUNCTION__, __LINE__, __FILE__); })
#else
#define CHECK_GL_ERROR() do {} while (0)
#endif


#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180
#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180


#endif
