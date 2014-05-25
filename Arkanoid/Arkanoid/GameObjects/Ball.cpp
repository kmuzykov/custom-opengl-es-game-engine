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
    KMTexture tex("arkanoid_ball.png");
    auto ballVertices = KMVertex::loadFromObj("arkanoid_ball.obj");
    auto mat = std::make_shared<KMMaterialTextureUnlit>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);
    
    //TODO: This is only temp need to inherit ball straight from KMGameOBject and calcualte radius much faster
    this->calculateCollidableSurfaces(ballVertices);
    

    
}