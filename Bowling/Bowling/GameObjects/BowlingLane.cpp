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

BowlingLane::BowlingLane()
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
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, nullptr, shape, bodyInertia);
    bodyCI.m_restitution = 0.0;
    bodyCI.m_friction = 0.5;
    
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);
}

btCollisionShape* BowlingLane::createShape(const std::vector<KMVertex>& laneVertices)
{
    static auto _Shape = KMPhysicsWorld::triangleMeshFromVertices(laneVertices);
    return _Shape.get();
}