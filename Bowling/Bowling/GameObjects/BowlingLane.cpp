//
//  BowlingLane.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "BowlingLane.h"
#include "KMVertex.h"
#include "KMMaterialTextureUnlit.h"
#include "KMRendererMesh.h"
#include "KMMaterialTextureDiffuse.h"

#include "btBulletDynamicsCommon.h"
#include "KMPhysicsWorld.h"
#include "KMPhysicsMotionState.h"

#include "KMMacros.h"

BowlingLane::BowlingLane(const vec3& position)
{
    //Setting renderer
    KMTexture tex("lane_diffuse.png");
    auto laneVertices = KMVertex::loadFromObj("lane.obj");
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, laneVertices);
    
    //Setting up physics body
    btCollisionShape* shape = createShape(laneVertices);
    btScalar bodyMass = 0.0f;
    btVector3 bodyInertia(0,0,0);
    //shape->calculateLocalInertia(bodyMass, bodyInertia);
    
    btTransform trasn;
    trasn.setIdentity();
    trasn.setOrigin(btVector3(position.x, position.y, position.z));    
    btDefaultMotionState *motionState = new btDefaultMotionState(trasn);
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, shape, bodyInertia);
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);
    
    _physicsBody->setRestitution(0.6f);
    _physicsBody->setFriction(1.0f);
    _physicsBody->setRollingFriction(1.0f);
}



btCompoundShape* initCompoundShape()
{
    btTransform transform;
    transform.setIdentity();
    
    btCompoundShape* compound = new btCompoundShape();
    
    const float halfLaneBodyX = 1.1875f;
    const float halfLaneBodyY = 0.17585f;
    const float laneZ = 21.5f;

    btBoxShape* laneBody = new btBoxShape(btVector3(halfLaneBodyX, halfLaneBodyY, laneZ));
    compound->addChildShape(transform, laneBody);
    
    const float halfOutfallX = 0.37f;
    const float halfOutfallY = 0.01f;
    
    btBoxShape* laneRight = new btBoxShape(btVector3(halfOutfallX, halfOutfallY, laneZ));
    transform.setOrigin(btVector3(halfLaneBodyX + halfOutfallX, -halfLaneBodyY, 0));
    compound->addChildShape(transform, laneRight);
    
    btBoxShape* laneLeft = new btBoxShape(btVector3(halfOutfallX, halfOutfallY, laneZ));
    transform.setOrigin(btVector3(-halfLaneBodyX - halfOutfallX, -halfLaneBodyY, 0));
    compound->addChildShape(transform, laneLeft);
    
    btBoxShape* laneEdgeLeft = new btBoxShape(btVector3(halfOutfallY, halfOutfallX * 2.0f, laneZ));
    transform.setOrigin(btVector3(-halfLaneBodyX - 2.0f * halfOutfallX + 0.09f, 0, 0));
    compound->addChildShape(transform, laneEdgeLeft);
    
    btBoxShape* laneEdgeRight = new btBoxShape(btVector3(halfOutfallY, halfOutfallX * 2.0f, laneZ));
    transform.setOrigin(btVector3(halfLaneBodyX + 2.0f * halfOutfallX - 0.09f, 0, 0));
    compound->addChildShape(transform, laneEdgeRight);
    
    return compound;
}

btCollisionShape* BowlingLane::createShape(const std::vector<KMVertex>& laneVertices)
{
    static auto _Shape = std::unique_ptr<btCollisionShape>(initCompoundShape());
    //_Shape->setMargin(0.05f);
    return _Shape.get();
}
