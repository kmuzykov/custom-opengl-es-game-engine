//
//  BowlingBall.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 14/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "BowlingBall.h"
#include "KMVertex.h"
#include "KMMaterialColorUniform.h"
#include "KMMaterialTextureUnlit.h"

#include "KMRendererMesh.h"

BowlongBall::BowlongBall() : KMGameObject()
{
    auto ballVertices = KMVertex::loadFromObj("ball.obj");
    //auto mat = std::make_shared<KMMaterialColorUniform>(vec3(1,0,0));
    
    KMTexture tex("ball_diffuse.png");
    
    auto mat = std::make_shared<KMMaterialTextureUnlit>(tex);
    
    std::shared_ptr<KMRenderer> renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);
    
    this->addComponent(renderer);
}