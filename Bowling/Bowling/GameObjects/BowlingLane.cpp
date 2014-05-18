//
//  BowlingLane.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "BowlingLane.h"
#include "KMVertex.h"
#include "KMMaterialTextureUnlit.h"
#include "KMRendererMesh.h"
#include "KMMaterialTextureDiffuse.h"

BowlingLane::BowlingLane()
{
    auto laneVertices = KMVertex::loadFromObj("lane.obj");
    KMTexture tex("lane_diffuse.png");

    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    std::shared_ptr<KMRenderer> renderer = std::make_shared<KMRendererMesh>(mat, laneVertices);
    this->addComponent(renderer);
}