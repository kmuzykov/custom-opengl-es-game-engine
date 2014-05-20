//
//  KMGameObject.cpp
//  KMEngine
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMGameObject.h"

#include "btBulletDynamicsCommon.h"
#include "KMRenderer.h"
#include "KMMacros.h"


KMGameObject::KMGameObject()
: KMNode(),
  _renderer(nullptr),
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

const vec3& KMGameObject::getPosition()
{
    //If we don't have physics body then we use parent function.
    if (!_physicsBody)
     return KMNode::getPosition();

    //Getting transform from motion state.
    btTransform trans;
    _physicsBody->getMotionState()->getWorldTransform(trans);
    
    //Updaging ivar and returning it
    _position = vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
    return _position;
}

void KMGameObject::setPosition(const vec3& position)
{
    //Setting position ivar using parent function in any case.
    if (!_physicsBody)
        KMNode::setPosition(position);
    
    //Setting the linked physics body position.
    btTransform trans = _physicsBody->getWorldTransform();
    trans.setOrigin(btVector3(position.x, position.y, position.z));
    _physicsBody->setWorldTransform(trans);
}

const Quaternion& KMGameObject::getRotation()
{
    if (!_physicsBody)
        return KMNode::getRotation();

    btTransform trans;
    _physicsBody->getMotionState()->getWorldTransform(trans);
    btQuaternion rot = trans.getRotation();
    
    _rotation = Quaternion(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
    return _rotation;
}

void KMGameObject::setRotation(const Quaternion& rotation)
{
    if (!_physicsBody)
        KMNode::setRotation(rotation);
    
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
