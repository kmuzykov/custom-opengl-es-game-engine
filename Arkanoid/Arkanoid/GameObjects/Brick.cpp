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
    const KMTexture& tex =  KMTextureCache::loadTexture("arkanoid_brick.png");
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, getBrickVertices());
    
    this->calculateCollidableSurfaces(getBrickVertices()); //TODO: Cache
}

const std::vector<KMVertex>& Brick::getBrickVertices()
{
    static const std::vector<KMVertex> _Vertices = KMVertex::loadFromObj("arkanoid_brick.obj");
    return _Vertices;
};