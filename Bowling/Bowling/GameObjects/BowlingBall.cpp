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
#include "KMPhysicsMotionState.h"


BowlingBall::BowlingBall(const vec3& position)
{
    //Setting up renderer
    KMTexture tex("ball_diffuse.png");
    auto ballVertices = KMVertex::loadFromObj("ball.obj");
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, ballVertices);
    
    //Setting up physics body
    btCollisionShape* shape = createShape();
    btScalar bodyMass = 10.0f;
    btVector3 bodyInertia;
    shape->calculateLocalInertia(bodyMass, bodyInertia);
    
    btTransform trasn;
    trasn.setIdentity();
    trasn.setOrigin(btVector3(position.x, position.y, position.z));
    
    btDefaultMotionState *motionState = new btDefaultMotionState(trasn);
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, shape, bodyInertia);
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);
    
    _physicsBody->setRestitution(0.6f);
    _physicsBody->setFriction(.1f);
//    _physicsBody->setRollingFriction(.2f);
//    _physicsBody->setAnisotropicFriction(shape->getAnisotropicRollingFrictionDirection(),btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
}

btCollisionShape* BowlingBall::createShape()
{
    //Storing only one instance of the shape
    static std::unique_ptr<btCollisionShape> _Shape = std::unique_ptr<btCollisionShape>(new btSphereShape(0.3f));
    return _Shape.get();
}