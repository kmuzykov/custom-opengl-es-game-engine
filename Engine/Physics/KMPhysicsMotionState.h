//
//  KMPhysicsMotionState.h
//  Bowling
//
//  Created by Kirill Muzykov on 19/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMPhysicsMotionState__
#define __KMEngine__KMPhysicsMotionState__

#include "btBulletDynamicsCommon.h"
#include <memory>

class KMGameObject;

class KMPhysicsMotionState : public btMotionState
{
public:
    KMPhysicsMotionState(KMGameObject * const node);
    virtual ~KMPhysicsMotionState(){}
    
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);
    
private:
    KMGameObject* const _node;
};



#endif /* defined(__Bowling__KMPhysicsMotionState__) */
