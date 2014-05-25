//
//  KMScene.h
//  KMEngine
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMScene__
#define __KMEngine__KMScene__

#include "KMNode.h"
#include <vector>

/** Scene contains all nodes displayed on the screen at once. You can switch between scenes just as between views */
class KMScene : public KMNode
{
public:
    KMScene();
    
    void addLightSource(const vec3& pos, float intensity = 1.0f);
    const std::vector<vec3>& getLightSources() const {return _lightSources;}
    const std::vector<float>& getLightIntensities() const {return _lightIntensities;}
    
private:
    std::vector<vec3> _lightSources;
    std::vector<float> _lightIntensities;
};

#endif /* defined(__Bowling__KMScene__) */
