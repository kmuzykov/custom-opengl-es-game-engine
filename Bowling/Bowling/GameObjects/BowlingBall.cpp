//
//  BowlingBall.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 14/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "BowlingBall.h"

#include "KMVertex.h"
#include "KMMaterialTextureDiffuse.h"
#include "KMRendererMesh.h"

#include "btBulletDynamicsCommon.h"

BowlingBall::BowlingBall()
{
    //Setting up renderer
    KMTexture tex("ball_diffuse.png");
    auto ballVertices = KMVertex::loadFromObj("ball.obj");
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);
    
    //Setting up physics body
    btCollisionShape* shape = createShape();
    btScalar bodyMass = 5.0f;
    btVector3 bodyInertia;
    shape->calculateLocalInertia(bodyMass, bodyInertia);
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, nullptr, shape, bodyInertia);
    bodyCI.m_restitution = 0.7;
    bodyCI.m_friction = 0.2;
    bodyCI.m_rollingFriction = 0.3;
    
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);    
}

btCollisionShape* BowlingBall::createShape()
{
    //Storing only one instance of the shape
    static std::unique_ptr<btCollisionShape> _Shape = std::unique_ptr<btCollisionShape>(new btSphereShape(0.3f));
    return _Shape.get();
}