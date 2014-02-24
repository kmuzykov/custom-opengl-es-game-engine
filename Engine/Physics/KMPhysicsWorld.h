//
//  KMPhysicsWorld.h
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMPhysicsWorld__
#define __Bowling__KMPhysicsWorld__

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

class KMPhysicsNode;

class KMPhysicsWorld
{
    friend class KMPhysicsNode;

public:
    KMPhysicsWorld();
    virtual ~KMPhysicsWorld();
    
    void step(float dt);
private:
    btBroadphaseInterface*                  _broadphase;
    btDefaultCollisionConfiguration*        _collisionConfiguration;
    btCollisionDispatcher*                  _dispatcher;
    btSequentialImpulseConstraintSolver*    _solver;
    btDiscreteDynamicsWorld*                _world;
    
    void addObject(KMPhysicsNode* physicsObject);
};


#endif /* defined(__Bowling__KMPhysicsWorld__) */
