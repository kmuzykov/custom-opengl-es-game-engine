//
//  KMVertex.h
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMVertex__
#define __Bowling__KMVertex__

#include "Vector.hpp"
#include <OpenGLES/ES2/gl.h>

#include <vector>

struct KMVertex
{
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    
    static std::vector<KMVertex> loadFromObj(const char* file);

    static void cuboid(float width, float height, float depth,
                       std::vector<KMVertex>& vertices, std::vector<GLushort>& indices);
    
    static void sphere(float radius, unsigned short verticalSegments, unsigned short horizontalSegments,
                       std::vector<KMVertex>& vertices, std::vector<GLushort>& indices);
};



#endif /* defined(__Bowling__KMVertex__) */