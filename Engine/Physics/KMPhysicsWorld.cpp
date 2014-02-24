//
//  KMPhysicsWorld.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMPhysicsWorld.h"
#include "btBulletDynamicsCommon.h"
#include "KMPhysicsNode.h"

KMPhysicsWorld::KMPhysicsWorld()
{
    _broadphase = new btDbvtBroadphase();

    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);

    _solver = new btSequentialImpulseConstraintSolver();
    
    _world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
    _world->setGravity(btVector3(0, -9.8, 0));
}

KMPhysicsWorld::~KMPhysicsWorld()
{
    delete _world;
    delete _solver;
    delete _collisionConfiguration;
    delete _dispatcher;
    delete _broadphase;
}

void KMPhysicsWorld::addObject(KMPhysicsNode* physicsObject)
{
    //TODO: Reset postion of the physicsObject
    _world->addRigidBody(physicsObject->getPhysicsBody());
}

void KMPhysicsWorld::step(float dt)
{
    _world->stepSimulation(dt);    
}
