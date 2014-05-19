//
//  KMPhysicsMotionState.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 19/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMPhysicsMotionState.h"
#include "KMGameObject.h"
#include "KMMacros.h"

KMPhysicsMotionState::KMPhysicsMotionState(KMGameObject* const node)
: _node(node)
{
    
}

void KMPhysicsMotionState::getWorldTransform(btTransform &worldTrans) const
{
    if (_node)
    {
        vec3 pos = _node->KMNode::getPosition();
        Quaternion rot = _node->KMNode::getRotation();
        
        worldTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));
        worldTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
    }
}

void KMPhysicsMotionState::setWorldTransform(const btTransform &worldTrans)
{
    if (_node)
    {
        
        const btVector3& pos = worldTrans.getOrigin();
        const btQuaternion& rot = worldTrans.getRotation();
        
//        KMLOG("World trans pos (%f, %f, %f) \n", pos.x(), pos.y(), pos.z());
        
        
        _node->KMNode::setPosition((vec3(pos.x(), pos.y(), pos.z())));
        _node->KMNode::setRotation(Quaternion(rot.x(), rot.y(), rot.z(), rot.w()));
    }
}
