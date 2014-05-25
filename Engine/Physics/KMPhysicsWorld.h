//
//  KMPhysicsWorld.h
//  KMEngine
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#if KM_PHYSICS > 0
#ifndef __KMEngine__KMPhysicsWorld__
#define __KMEngine__KMPhysicsWorld__

#include <memory>
#include <vector>

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btBvhTriangleMeshShape;

class KMVertex;
class KMGameObject;

/** 
 * Wrapper around Bullet Physics world.
 * Add all nodes with physics bodies to it to add them into simulation.
 */
class KMPhysicsWorld
{
public:
    KMPhysicsWorld();
    ~KMPhysicsWorld();
    
    void addObject(KMGameObject* physicsObject);
    void step(float dt);
    void drawDebug();
    
    static std::auto_ptr<btBvhTriangleMeshShape> triangleMeshFromVertices(const std::vector<KMVertex>& vertices);
private:
    btBroadphaseInterface*                  _broadphase;
    btDefaultCollisionConfiguration*        _collisionConfiguration;
    btCollisionDispatcher*                  _dispatcher;
    btSequentialImpulseConstraintSolver*    _solver;
    btDiscreteDynamicsWorld*                _world;
};


#endif /* defined(__Bowling__KMPhysicsWorld__) */
#endif
