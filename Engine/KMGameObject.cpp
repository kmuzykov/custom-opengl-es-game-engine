//
//  KMGameObject.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMGameObject.h"

#include "btBulletDynamicsCommon.h"
#include "KMRenderer.h"
#include "KMMacros.h"


KMGameObject::KMGameObject()
: _renderer(nullptr),
  _physicsBody(nullptr)
{
    
}

KMGameObject::~KMGameObject()
{
    
}

void KMGameObject::update(float dt)
{
    KMNode::update(dt);
}

void KMGameObject::draw()
{
    KMNode::draw();
    
    mat4 mvm = this->modelViewMatrix(true);
    _renderer->render(mvm);
}

vec3 KMGameObject::getPosition() const
{
    if (!_physicsBody)
     return KMNode::getPosition();
    
//    btTransform trans = _physicsBody->getWorldTransform();
    btTransform trans;
    _physicsBody->getMotionState()->getWorldTransform(trans);
    return vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
}

void KMGameObject::setPosition(const vec3& position)
{
    if (!_physicsBody)
    {
        KMNode::setPosition(position);
    }
    
    btTransform trans = _physicsBody->getWorldTransform();
    trans.setOrigin(btVector3(position.x, position.y, position.z));
    _physicsBody->setWorldTransform(trans);
}

Quaternion KMGameObject::getRotation() const
{
    if (!_physicsBody)
        return KMNode::getRotation();

    //btTransform trans = _physicsBody->getWorldTransform();
    btTransform trans;
    _physicsBody->getMotionState()->getWorldTransform(trans);
    btQuaternion rot = trans.getRotation();
    return Quaternion(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
}

void KMGameObject::setRotation(Quaternion rotation)
{
    if (!_physicsBody)
    {
        KMNode::setRotation(rotation);        return;
    }
    
    btTransform trans = _physicsBody->getWorldTransform();
    btQuaternion btRot = btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    trans.setRotation(btRot);
    _physicsBody->setWorldTransform(trans);    
}

void KMGameObject::rotateBy(Quaternion rotateBy)
{
    //TODO: Implement
    KMLOG("KMGameObject::rotateBy is not yet implemented");
}
