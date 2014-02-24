//
//  TestScene.h
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__TestScene__
#define __Bowling__TestScene__

#include "KMScene.h"

class KMPhysicsWorld;
class KMPhysicsNode;

class TestScene : public KMScene
{
public:
    TestScene();

protected:
    virtual void update(float dt);
    
private:
    KMPhysicsWorld* _physicsWorld;
    std::shared_ptr<KMPhysicsNode> _ball;
};

#endif /* defined(__Bowling__TestScene__) */
