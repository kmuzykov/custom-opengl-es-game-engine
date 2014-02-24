//
//  KMLightSourceNode.h
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMLightSourceNode__
#define __Bowling__KMLightSourceNode__

#include "KMNode.h"

class KMLightSourceNode : public KMNode
{
    friend class KMRenderableModuleLighting;
    
public:
    KMLightSourceNode();
    
    float getIntensity() const { return _intensity; }
    void setIntensity(float intensity) { _intensity = intensity; }
    
private:
    float _intensity;
};

#endif /* defined(__Bowling__KMLightSourceNode__) */
