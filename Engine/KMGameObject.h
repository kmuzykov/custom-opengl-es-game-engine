//
//  KMGameObject.h
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMGameObject__
#define __Bowling__KMGameObject__

#include "KMRenderer.h"
#include "KMComponent.h"
#include "KMNode.h"

#include <memory>
#include <vector>

class KMGameObject : public KMNode
{
public:
    KMGameObject();
    virtual ~KMGameObject();
    
    virtual void update(float dt);
    virtual void draw();
    
    void addComponent(std::shared_ptr<KMComponent> component);

private:
    std::vector<std::shared_ptr<KMComponent>> _components;
};


#endif /* defined(__Bowling__KMGameObject__) */
