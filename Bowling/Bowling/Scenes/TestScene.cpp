//
//  TestScene.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "TestScene.h"
#include "KMRenderable.h"
#include "KMMacros.h"
#include "KMRenderableModuleUniformColor.h"
#include "KMRenderableModuleTextured.h"
#include "KMRenderableModuleLighting.h"
#include "KMTexture.h"

#include "KMLightSourceNode.h"

#include "KMPhysicsNode.h"
#include "KMPhysicsWorld.h"

using namespace std;


TestScene::TestScene()
{
    
//    vector<KMVertex> vertices;
//    vector<GLushort> indices;
//    KMVertex::sphere(10, 16, 16, vertices, indices);
//    
//    KMShader ucShader("uniform_color.vsh", "uniform_color.fsh");
//    auto sphere = make_shared<KMRenderable>(ucShader, vertices, indices);
//
//    unique_ptr<KMRenderableModule> ucModule(new KMRenderableModuleUniformColor(vec4(1,0,0,1)));
//    
//    sphere->addModule(std::move(ucModule));
//    sphere->setPosition(vec3(0,0,-2));
//    this->addChild(sphere);
    
    auto ligh0 = make_shared<KMLightSourceNode>();
    ligh0->setPosition(vec3(0, 3, -2));
    ligh0->setIntensity(1.0f);
    this->addChild(ligh0);
    
    auto ligh1 = make_shared<KMLightSourceNode>();
    ligh1->setPosition(vec3(0, 3, -15));
    ligh1->setIntensity(0.6f);
    this->addChild(ligh1);

    auto ligh2 = make_shared<KMLightSourceNode>();
    ligh2->setPosition(vec3(0, 3, -30));
    ligh2->setIntensity(0.4f);
    this->addChild(ligh2);    
    
    _physicsWorld = new KMPhysicsWorld();
    
    auto laneVertices = KMVertex::loadFromObj("lane.obj");
    auto ballVertices = KMVertex::loadFromObj("ball.obj");
    auto pinVertices = KMVertex::loadFromObj("pin.obj");

    KMTexture laneTex("lane_diffuse.png");
    KMTexture ballTex("ball_diffuse.png");
    KMTexture pinTex("pin_diffuse.png");
    KMShader texturedShader("textureLightened.vsh", "textureLightened.fsh");
    
    KMPhysicsProperties ballProps;
    ballProps.mass = 5.0f;
    ballProps.restitution = 0.7;
    ballProps.friction = 0.2;
    ballProps.rollingFriction = 0.3f;
    ballProps.isSphere = true;
    ballProps.radius = 0.3f;
    
    _ball =  make_shared<KMPhysicsNode>(texturedShader, ballVertices, *_physicsWorld, ballProps);
    _ball->setPosition(vec3(0.7, -0.7, -3));
    
    unique_ptr<KMRenderableModule> ballTexModule(new KMRenderableModuleTextured(ballTex));
    unique_ptr<KMRenderableModuleLighting> ballLightingModule(new KMRenderableModuleLighting());
    
    ballLightingModule->setLight0(ligh0);
    ballLightingModule->setLight1(ligh1);
    ballLightingModule->setLight2(ligh2);

    _ball->addModule(std::move(ballTexModule));
    _ball->addModule(std::move(ballLightingModule));

    this->addChild(_ball);
    
    KMPhysicsProperties laneProps;
    laneProps.mass = 0;
    laneProps.restitution = 0.6;
    laneProps.friction = 0.5;
    
    auto lane = make_shared<KMPhysicsNode>(texturedShader, laneVertices, *_physicsWorld, laneProps);
    lane->setPosition(vec3(0,-1.5, -15));
    
    unique_ptr<KMRenderableModule> laneTexModule(new KMRenderableModuleTextured(laneTex));
    unique_ptr<KMRenderableModuleLighting> laneLightningModule(new KMRenderableModuleLighting());
    
    laneLightningModule->setLight0(ligh0);
    laneLightningModule->setLight1(ligh1);
    laneLightningModule->setLight2(ligh2);
    
    lane->addModule(std::move(laneTexModule));
    lane->addModule(std::move(laneLightningModule));
    
    this->addChild(lane);
    
    
    vector<vec3> pinPositions;
    vec3 basePos = {0, -0.73, -34};
    //float marginX = 0.25f;
    float marginX = 0.3f;
    float marginZ = 0.305f;
    
    for (int  i = 0; i < 4; i++)
    {
        float z = basePos.z - marginZ * i;

        for (int j = 0; j <=i ;j ++)
        {
            float mx = -marginX * i + marginX * 2.0 * j;
            float x = basePos.x + mx;
            
            vec3 pinPos(x, basePos.y, z);
            pinPositions.push_back(pinPos);

        }
    }
    
    KMPhysicsProperties pinProps;
    pinProps.mass = 1.6;
    pinProps.restitution = 0.7;
    pinProps.friction = 0.9;
    pinProps.isConvex = true;
    
    for (int i = 0; i < pinPositions.size(); i++)
    {
        vec3 pos = pinPositions[i];
        auto pin = make_shared<KMPhysicsNode>(texturedShader, pinVertices, *_physicsWorld, pinProps);
        pin->setPosition(pos);
        
        unique_ptr<KMRenderableModule> pinTexModule(new KMRenderableModuleTextured(pinTex));
        unique_ptr<KMRenderableModuleLighting> pinLightingModule(new KMRenderableModuleLighting());
        
        pinLightingModule->setLight0(ligh0);
        pinLightingModule->setLight1(ligh1);
        pinLightingModule->setLight2(ligh2);
        
        pin->addModule(std::move(pinTexModule));
        pin->addModule(std::move(pinLightingModule));
        
        this->addChild(pin);
    }
    
    _ball->getPhysicsBody()->setLinearVelocity(btVector3(-0.02,0,-10));
}


void TestScene::update(float dt)
{
    KMScene::update(dt);
    _physicsWorld->step(dt);

    vec3 ballPos = _ball->getPosition();
    vec3 pos = this->getPosition();
    
    pos.z = -1 * ballPos.z - 3;
    
    if (pos.z > 30)
        pos.z = 30;
    
    this->setPosition(pos);
//
//    vec3 position = this->getPosition();
//    position.z += dt;
//    this->setPosition(position);
    
//    float rads = DEGREES_TO_RADIANS(-15 * dt);
//    Quaternion rot = Quaternion::CreateFromAxisAngle(vec3(0.5,1,1), rads);
//    
//    for (auto& child : this->getChildren())
//    {
//        child->rotateBy(rot);
//    }
}





