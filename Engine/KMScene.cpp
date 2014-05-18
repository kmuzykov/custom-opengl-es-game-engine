//
//  KMScene.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMScene.h"
#include "KMConfig.h"
#include "KMMacros.h"

KMScene::KMScene()
: KMNode()
{
    
}

void KMScene::addLightSource(const vec3& pos, float intensity)
{
    if (_lightSources.size() >= KM_MAX_LIGHTS)
    {
        KMLOG("Maximum amount of light sources (%d) reached. Ignoring light at (%f, %f, %f)", KM_MAX_LIGHTS, pos.x, pos.y, pos.z);
        return;
    }
    
    _lightSources.push_back(pos);
    _lightIntensities.push_back(intensity);
}
