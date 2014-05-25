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
    auto batVertices = KMVertex::loadFromObj("arkanoid_bat.obj");
    auto mat = std::make_shared<KMMaterialTextureUnlit>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, batVertices);
 
    this->calculateCollidableSurfaces(batVertices);    
}

void Bat::setPosition(const vec3& position)
{
    ArkanoidGameObject::setPosition(position);
    _desiredPosition = position.x;
}

void Bat::setDesiredPosition(const float x)
{
    _desiredPosition = x;
}

void Bat::applyDesiredPosition()
{
    vec3 newPosition = _position;
    newPosition.x = _desiredPosition;
    this->setPosition(newPosition);
}