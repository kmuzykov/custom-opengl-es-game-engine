//
//  Ball.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "Ball.h"

Ball::Ball()
{
    //Setting up renderer
    const KMTexture& tex =  KMTextureCache::loadTexture("earth.png");
    auto ballVertices = KMVertex::loadFromObj("arkanoid_ball.obj");
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);    
}