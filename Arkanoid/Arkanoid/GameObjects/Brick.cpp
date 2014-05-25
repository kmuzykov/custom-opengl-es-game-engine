//
//  Brick.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "Brick.h"

Brick::Brick()
{
    //TODO: Texture cache!
    KMTexture tex("arkanoid_ball.png");
    auto mat = std::make_shared<KMMaterialTextureUnlit>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, getBrickVertices());
    
    this->calculateCollidableSurfaces(getBrickVertices()); //TODO: Cache
}

const std::vector<KMVertex>& Brick::getBrickVertices()
{
    static const std::vector<KMVertex> _Vertices = KMVertex::loadFromObj("arkanoid_brick.obj");
    return _Vertices;
};