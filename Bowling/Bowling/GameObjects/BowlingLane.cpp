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
#include "KMPhysicsMotionState.h"

#include "KMMacros.h"

BowlingLane::BowlingLane(const vec3& position)
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
    
    btTransform trasn;
    trasn.setIdentity();
    trasn.setOrigin(btVector3(position.x, position.y, position.z));    
    btDefaultMotionState *motionState = new btDefaultMotionState(trasn);
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, shape, bodyInertia);
    _physicsBody = std::unique_ptr<btRigidBody>(new btRigidBody(bodyCI));
    _physicsBody->setUserPointer(this);
    
    _physicsBody->setRestitution(0.6f);
    _physicsBody->setFriction(1.0f);
    _physicsBody->setRollingFriction(1.0f);
}


/** 
    Creates a compound (multi-shape) shape for the bowling lane.
 */
btCompoundShape* initCompoundShape()
{
    //We'll use transform to place different shapes at different positions in local space.
    btTransform transform;
    transform.setIdentity();
    
    //This will be the result
    btCompoundShape* compound = new btCompoundShape();
    
    //Few constants we have from Blender. If you change models this needs to be adjusted.
    const float halfLaneBodyX = 1.1875f;    //Half of the middle part of the lane (no trenches)
    const float halfLaneBodyY = 0.17585f;   //Half height of the model
    const float laneZ = 21.5f;              //Half lenght of the bowling lane
    const float halfOutfallX = 0.37f;       //Half width of the outfall (trench)
    const float halfOutfallY = 0.01f;       //A small value used as depth for boxes of the trenches.
    
    //  ||       |___________________ ... symmetric on the other side
    //  ||       |
    //  ||       |    *labeBody*
    //  ||_______ ____________________
    //    |______| <- laneOutfallLeft
    //  ^ laneEdgeLeft
    
    
    //Creating middle part of the lane
    btBoxShape* laneBody = new btBoxShape(btVector3(halfLaneBodyX, halfLaneBodyY, laneZ));
    compound->addChildShape(transform, laneBody);
    
    //Few more positioning constants
    const float edgeHeight    = halfOutfallX * 1.1f;                            //Making edge a bit higher
    const float leftEdgeX     = -halfLaneBodyX - 2.0f * halfOutfallX + 0.09f;   //X-coordinage of center of the left edge box.
    const float leftOutfallX  = -halfLaneBodyX - halfOutfallX;                  //X-coordinate of the horizontal outfall box on the left
    const float rightOutfallX = -1 * leftOutfallX;                              //Mirrored for right outfall
    const float rightEdgeX    = -1 * leftEdgeX;                                 //Mirrored for right edge

    //Left edge (side of the trench)
    btBoxShape* laneEdgeLeft = new btBoxShape(btVector3(halfOutfallY, edgeHeight, laneZ));
    transform.setOrigin(btVector3(leftEdgeX, 0, 0));
    compound->addChildShape(transform, laneEdgeLeft);
    
    //Left outfall (floor of the trench)
    btBoxShape* laneOutfallLeft = new btBoxShape(btVector3(halfOutfallX, halfOutfallY, laneZ));
    transform.setOrigin(btVector3(leftOutfallX, -halfLaneBodyY, 0));
    compound->addChildShape(transform, laneOutfallLeft);

    //Right Edge
    btBoxShape* laneEdgeRight = new btBoxShape(btVector3(halfOutfallY, edgeHeight, laneZ));
    transform.setOrigin(btVector3(rightEdgeX, 0, 0));
    compound->addChildShape(transform, laneEdgeRight);
    
    //Right outfall
    btBoxShape* laneOutfallRight = new btBoxShape(btVector3(halfOutfallX, halfOutfallY, laneZ));
    transform.setOrigin(btVector3(rightOutfallX, -halfLaneBodyY, 0));
    compound->addChildShape(transform, laneOutfallRight);
    
    return compound;
}

btCollisionShape* BowlingLane::createShape(const std::vector<KMVertex>& laneVertices)
{
    static auto _Shape = std::unique_ptr<btCollisionShape>(initCompoundShape());
    return _Shape.get();
}
