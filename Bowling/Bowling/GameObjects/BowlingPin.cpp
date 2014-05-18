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

BowlingPin::BowlingPin()
{
    //Setting up renderer
    KMTexture tex("pin_diffuse.png");
    auto pinVertices = KMVertex::loadFromObj("pin.obj");
    auto mat = std::make_shared<KMMaterialTextureDiffuse>(tex);
    _renderer = std::make_shared<KMRendererMesh>(mat, pinVertices);
    
    //Setting up physics body
    btCollisionShape* shape = createShape();
    btScalar bodyMass = 1.5f;
    btVector3 bodyInertia(0,0,0);
    shape->calculateLocalInertia(bodyMass, bodyInertia);
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, nullptr, shape, bodyInertia);
    bodyCI.m_restitution = 0.1;
    bodyCI.m_friction = 0.8;
    bodyCI.m_rollingFriction = .2f;
    
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);
}

btCollisionShape* BowlingPin::createShape()
{
//    btTransform transform;
//    transform.setIdentity();
//    
//    btCompoundShape *compound = new btCompoundShape();
//    btCylinderShape *cylinder = new btCylinderShape(btVector3(0.15f, 0.4f, 0.15f));
//    btSphereShape *topSphere = new btSphereShape(0.13f);
//    
//    
//    transform.setOrigin(btVector3(0, -0.1f, 0));
//    compound->addChildShape(transform, cylinder);
//    
//    transform.setOrigin(btVector3(0, 0.35f, 0));
//    compound->addChildShape(transform, topSphere);
//    
//    static btCollisionShape* _Shape = compound;
    
    static std::unique_ptr<btCollisionShape> _Shape = std::unique_ptr<btCollisionShape>(new btCylinderShape(btVector3(0.15f, 0.5f, 0.15f)));
    return _Shape.get();
}