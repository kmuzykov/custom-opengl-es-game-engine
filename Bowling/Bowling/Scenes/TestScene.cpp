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
    //Creating physics world to add all objects for simulation
    _physicsWorld = new KMPhysicsWorld();
    
    //Adding lights
    this->addLightSource(vec3(0, 3, -2));
    this->addLightSource(vec3(0, 3, -15), 0.5f);
    this->addLightSource(vec3(0, 3, -30), 0.25f);
    
    //Creating ball & adding it to physics world
    _ball = std::make_shared<BowlingBall>();
    _ball->setPosition(vec3(0.7f, -0.7f, -3.0f));
    this->addChild(_ball);
    //_physicsWorld->addObject(_ball.get());
    
    //Bowling lane
    auto bowlingLane = std::make_shared<BowlingLane>();
    bowlingLane->setPosition(vec3(0,-1.5, -15));
    this->addChild(bowlingLane);
    _physicsWorld->addObject(bowlingLane.get());
    
    //Generating pins
//    vec3 basePos = {0, -0.73, -34};
//    float marginX = 0.3f;
//    float marginZ = 0.305f;
//
//    for (int  i = 0; i < 4; i++)
//    {
//        float z = basePos.z - marginZ * i;
//        for (int j = 0; j <=i ;j ++)
//        {
//            //Calculating pin position
//            float mx = -marginX * i + marginX * 2.0 * j;
//            float x = basePos.x + mx;
//            vec3 pinPos(x, basePos.y, z);
//            
//            //Creating actual pin and adding it to scene and physics world
//            auto pin = std::make_shared<BowlingPin>();
//            pin->setPosition(pinPos);
//            this->addChild(pin);
//            _physicsWorld->addObject(pin.get());
//        }
//    }
    
    //Single pin for tests
    auto pin = std::make_shared<BowlingPin>();
    pin->setPosition(vec3(0,-0.73, -3));
    this->addChild(pin);
    _physicsWorld->addObject(pin.get());
    
    //_ball->getPhysicsBody()->setLinearVelocity(btVector3(-0.02,0,-10));
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

///void TestScene::update(float dt)
//{
//    KMScene::update(dt);
//    _physicsWorld->step(dt);
//
//    vec3 ballPos = _ball->getPosition();
//    vec3 pos = this->getPosition();
//    
//    pos.z = -1 * ballPos.z - 3;
//    
//    if (pos.z > 30)
//        pos.z = 30;
//    
//    this->setPosition(pos);
////
////    vec3 position = this->getPosition();
////    position.z += dt;
////    this->setPosition(position);
//    
////    float rads = DEGREES_TO_RADIANS(-15 * dt);
////    Quaternion rot = Quaternion::CreateFromAxisAngle(vec3(0.5,1,1), rads);
////    
////    for (auto& child : this->getChildren())
////    {
////        child->rotateBy(rot);
////    }
//}
