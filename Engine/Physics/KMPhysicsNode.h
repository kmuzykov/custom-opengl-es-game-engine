//
//  KMRenderablePhysics.h
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMRenderablePhysics__
#define __Bowling__KMRenderablePhysics__

#include "KMRenderable.h"
#include "KMPhysicsWorld.h"

#include "btBulletDynamicsCommon.h"

struct  KMPhysicsProperties
{
    float mass;
    float restitution;
    float friction;
    float rollingFriction;
    
    bool isConvex;
    bool isSphere;
    float radius;
    
    KMPhysicsProperties()
    {
        mass = 0.0;
        restitution = 1.0;
        friction = 0;
        rollingFriction = 0;
        isConvex = false;
        isSphere = false;
        radius = 1;
    }
};

class KMPhysicsNode : public KMRenderable
{
public:
    KMPhysicsNode(KMShader shader, std::vector<KMVertex> vertices, KMPhysicsWorld& world, KMPhysicsProperties& props);
    
    virtual vec3 getPosition() const;
    virtual void setPosition(const vec3& position);
    
    btRigidBody* getPhysicsBody() {return _physicsBody;}
    
//    virtual float getScale() const { return _scale; }
//    virtual void setScale(float scale) { _scale = scale; }

    virtual Quaternion getRotation() const;
    virtual void setRotation(Quaternion rotation);
    virtual void rotateBy(Quaternion rotateBy);

   // virtual mat4 modelViewMatrix(bool includeParent);
private:
    btRigidBody* _physicsBody;
};


#endif /* defined(__Bowling__KMRenderablePhysics__) */
