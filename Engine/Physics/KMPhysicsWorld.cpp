//
//  KMPhysicsWorld.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//


#include "KMPhysicsWorld.h"
#include "btBulletDynamicsCommon.h"

#include "KMGameObject.h"
#include "KMVertex.h"
#include "KMMacros.h"

#include "GLDebugDrawer.h"

KMPhysicsWorld::KMPhysicsWorld()
{
    _broadphase = new btDbvtBroadphase();//new btAxisSweep3(btVector3(-100,-100,-100), btVector3(100,100,100));

    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);

    _solver = new btSequentialImpulseConstraintSolver();
    
    _world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
    _world->setGravity(btVector3(0.0f, -10.0f, 0.0f));
    

    _world->setDebugDrawer(new GLDebugDrawer());
}

KMPhysicsWorld::~KMPhysicsWorld()
{
    delete _world;
    delete _solver;
    delete _collisionConfiguration;
    delete _dispatcher;
    delete _broadphase;
}

void KMPhysicsWorld::addObject(KMGameObject* physicsObject)
{
    btRigidBody *physicsBody = physicsObject->getPhysicsBody();
    if (!physicsBody)
    {
        KMLOG("Trying to add object without physics body. The object will be ignored.");
        return;
    }
    
    //TODO: Reset postion of the physicsObject
    _world->addRigidBody(physicsObject->getPhysicsBody());
}

void KMPhysicsWorld::step(float dt)
{
    //_world->stepSimulation(dt, 32, 1.0/120.0f);
    _world->stepSimulation(dt);
}

void KMPhysicsWorld::drawDebug()
{
#if KM_RENDER_PHYSICS_DEBUG_ENABLED > 0
    _world->debugDrawWorld();
#endif
}

std::auto_ptr<btBvhTriangleMeshShape> KMPhysicsWorld::triangleMeshFromVertices(const std::vector<KMVertex>& vertices)
{
    btTriangleMesh* mesh = new btTriangleMesh();
    for (int i=0; i < vertices.size(); i += 3)
    {
        KMVertex v1 = vertices[i];
        KMVertex v2 = vertices[i+1];
        KMVertex v3 = vertices[i+2];
        
        btVector3 bv1 = btVector3(v1.position.x, v1.position.y, v1.position.z);
        btVector3 bv2 = btVector3(v2.position.x, v2.position.y, v2.position.z);
        btVector3 bv3 = btVector3(v3.position.x, v3.position.y, v3.position.z);
        
        mesh->addTriangle(bv1, bv2, bv3);
    }
    
    return std::auto_ptr<btBvhTriangleMeshShape>(new btBvhTriangleMeshShape(mesh, true));
}
