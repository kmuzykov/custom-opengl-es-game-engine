//
//  TestScene.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "TestScene.h"

#include "KMMacros.h"
#include "KMPhysicsWorld.h"

#include "BowlingBall.h"
#include "BowlingLane.h"
#include "BowlingPin.h"

#include "btBulletDynamicsCommon.h"

using namespace std;

TestScene::TestScene()
{
    //Adding lights (let there be light :)
    this->addLightSource(vec3(0, 3, -2));
    this->addLightSource(vec3(0, 3, -15), 0.5f);
    this->addLightSource(vec3(0, 3, -30), 0.25f);

    //Creating physics world to add all objects for simulation
    _physicsWorld = new KMPhysicsWorld();
    
    addLane();
    addAllPins();
    addBall();
}

void TestScene::addBall()
{
    //Creating ball
    _ball = std::make_shared<BowlingBall>(vec3(0.7f, -0.7f, -3.0f));
    this->addChild(_ball);
    _physicsWorld->addObject(_ball.get());
    
    
    //Applying impulse to move forward and spin
    _ball->getPhysicsBody()->applyCentralImpulse(btVector3(0, 10,-50));
    //_ball->getPhysicsBody()->applyTorqueImpulse(btVector3(0,0, 30)); //left rot
    _ball->getPhysicsBody()->applyTorqueImpulse(btVector3(0,0, -30)); //right rot
}

void TestScene::addTestPin()
{
    auto pin = std::make_shared<BowlingPin>(vec3(0, -1, -3));
    this->addChild(pin);
    _physicsWorld->addObject(pin.get());

    //Deactivating pin so that it stayed EXACTLY where we put it before the ball
    //or another pon hits it.
    //pin->getPhysicsBody()->setActivationState(WANTS_DEACTIVATION);
}

void TestScene::addAllPins()
{
    //Generating pins
    //z: -34 end of lane base, -10 is just to put them closer where we can see them (before I implement camera following the ball)
    vec3 basePos = {0, -1, -10};
    float marginX = 0.3f;
    float marginZ = 0.305f;
    
    for (int  i = 0; i < 4; i++)
    {
        float z = basePos.z - marginZ * i;
        for (int j = 0; j <=i ;j ++)
        {
            //Calculating pin position
            float mx = -marginX * i + marginX * 2.0 * j;
            float x = basePos.x + mx;
            vec3 pinPos(x, basePos.y, z);

            //Creating actual pin and adding it to scene and physics world
            auto pin = std::make_shared<BowlingPin>(pinPos);
            this->addChild(pin);
            _physicsWorld->addObject(pin.get());

            //Deactivating pin so that it stayed exactly where it was
            pin->getPhysicsBody()->setActivationState(WANTS_DEACTIVATION);
        }
    }
}

void TestScene::addLane()
{
    auto bowlingLane = std::make_shared<BowlingLane>(vec3(0,-1.5, -15));
    this->addChild(bowlingLane);
    _physicsWorld->addObject(bowlingLane.get());
}


void TestScene::update(float dt)
{
    KMScene::update(dt);
    _physicsWorld->step(dt);
}

void TestScene::draw()
{
    KMScene::draw();
    _physicsWorld->drawDebug();
}
