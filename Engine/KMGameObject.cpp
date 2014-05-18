//
//  KMGameObject.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMGameObject.h"

KMGameObject::KMGameObject()
:KMNode()
{
    
}

KMGameObject::~KMGameObject()
{
    
}

void KMGameObject::update(float dt)
{
    KMNode::update(dt);
}

void KMGameObject::addComponent(std::shared_ptr<KMComponent> component)
{
    _components.push_back(component);
}

void KMGameObject::draw()
{
    KMNode::draw();
    
    mat4 mvm = this->modelViewMatrix(true);
    for (auto& component : _components)
    {
        component->render(mvm);
    }
}
