//
//  Bat.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "Bat.h"

Bat::Bat()
{
    KMTexture tex("arkanoid_ball.png");
    auto ballVertices = KMVertex::loadFromObj("arkanoid_bat.obj");
    auto mat = std::make_shared<KMMaterialTextureUnlit>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);
    
}
