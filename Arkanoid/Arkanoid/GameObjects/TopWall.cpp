//
//  TopWall.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 24/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "TopWall.h"

TopWall::TopWall()
{
    KMTexture tex("arkanoid_ball.png");
    auto ballVertices = KMVertex::loadFromObj("arkanoid_top_wall.obj");
    auto mat = std::make_shared<KMMaterialTextureUnlit>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);
    
    this->calculateCollidableSurfaces(ballVertices);
}