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
class KMGameObject;

class TestScene : public KMScene
{
public:
    TestScene();

protected:
    virtual void update(float dt);
    virtual void draw();
    
private:
    KMPhysicsWorld* _physicsWorld;
    std::shared_ptr<KMGameObject> _ball;
    
    void addBall();
    void addTestPin();
    void addAllPins();
    void addLane();
};

#endif /* defined(__Bowling__TestScene__) */
