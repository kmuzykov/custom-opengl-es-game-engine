//
//  BowlingPin.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "BowlingPin.h"

#include "KMVertex.h"
#include "KMMaterialTextureDiffuse.h"
#include "KMRendererMesh.h"

#include "btBulletDynamicsCommon.h"
#include "KMPhysicsMotionState.h"

#include "KMMacros.h"

static btConvexHullShape* loadConvexHull();

BowlingPin::BowlingPin(const vec3& position)
{
    //Setting up renderer
    KMTexture tex("pin_diffuse.png");
    
    auto pinVertices = cachedVertices();
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, pinVertices);
    
    //Setting up physics body
    btCollisionShape* shape = createShape(pinVertices);
    btScalar bodyMass = 1.6f;
    btVector3 bodyInertia(0,0,0);
    shape->calculateLocalInertia(bodyMass, bodyInertia);
    
    btTransform trasn;
    trasn.setIdentity();
    trasn.setOrigin(btVector3(position.x, position.y, position.z));
    
    btDefaultMotionState *motionState = new btDefaultMotionState(trasn);
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, shape, bodyInertia);
    bodyCI.m_restitution = 0.7f;
    bodyCI.m_friction = 0.9f;
    
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);
    //_physicsBody->setDeactivationTime(0.0f);
    //_physicsBody->setDamping(0.1f, 0.2f);
    //_physicsBody->setAnisotropicFriction(shape->getAnisotropicRollingFrictionDirection(),btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
}

btCollisionShape* BowlingPin::createShape(const std::vector<KMVertex>& pinVertices)
{
    static auto _Shape = std::unique_ptr<btCollisionShape>(loadConvexHull());
    //_Shape->setMargin(0.05f);
    return _Shape.get();
}

const std::vector<KMVertex>& BowlingPin::cachedVertices()
{
    static auto _PinVertices = KMVertex::loadFromObj("pin.obj");
    return _PinVertices;
}

static btConvexHullShape* loadConvexHull()
{
    auto vertices = KMVertex::loadFromObj("pin_collider.obj", false);
    
    btConvexHullShape *convexHull = new btConvexHullShape();
    for (const KMVertex& vec : vertices)
    {
        convexHull->addPoint(btVector3(vec.position.x, vec.position.y, vec.position.z));
    }
    
    return convexHull;
}
