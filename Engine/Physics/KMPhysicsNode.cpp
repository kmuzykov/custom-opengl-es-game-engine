//
//  KMRenderablePhysics.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMPhysicsNode.h"

KMPhysicsNode::KMPhysicsNode(KMShader shader, std::vector<KMVertex> vertices, KMPhysicsWorld& world, KMPhysicsProperties& props)
: KMRenderable(shader, vertices)
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
    
    btCollisionShape* shape = nullptr;
    
    if (props.isSphere)
    {
        shape = new btSphereShape(props.radius); //todo: actual shapes
    }
    else if (props.isConvex)
    {
        shape = new btConeShape(0.1, 1);
    }
    else
    {
        shape = new btBvhTriangleMeshShape(mesh, true);
    }
    
    //1    
    vec3 initPos =  KMNode::getPosition();
    Quaternion initRot = KMNode::getRotation();
    
    btQuaternion rotation = btQuaternion(initRot.x, initRot.y, initRot.z, initRot.w);
    btVector3 position = btVector3(initPos.x, initPos.y, initPos.z);
    
    //3
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(rotation, position));
    
    //4
    btScalar bodyMass = props.mass;
    btVector3 bodyInertia;
    shape->calculateLocalInertia(bodyMass, bodyInertia);
    
    //5
    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, shape, bodyInertia);
    
    //6
    bodyCI.m_restitution = props.restitution;
    bodyCI.m_friction = props.friction;
    bodyCI.m_rollingFriction = props.rollingFriction;
    
    //7
    _physicsBody = new btRigidBody(bodyCI);
    
	//8
    _physicsBody->setUserPointer(this);
    
    //Addint ourselv to the world
    world.addObject(this);
}

vec3 KMPhysicsNode::getPosition() const
{
    btTransform trans = _physicsBody->getWorldTransform();
    return vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
}

void KMPhysicsNode::setPosition(const vec3& position)
{
    btTransform trans = _physicsBody->getWorldTransform();
    trans.setOrigin(btVector3(position.x, position.y, position.z));
    _physicsBody->setWorldTransform(trans);
}

Quaternion KMPhysicsNode::getRotation() const
{
    btTransform trans = _physicsBody->getWorldTransform();
    btQuaternion rot = trans.getRotation();
    return Quaternion(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
}

void KMPhysicsNode::setRotation(Quaternion rotation)
{
    btTransform trans = _physicsBody->getWorldTransform();
    btQuaternion btRot = btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    trans.setRotation(btRot);
    _physicsBody->setWorldTransform(trans);
}

void KMPhysicsNode::rotateBy(Quaternion rotateBy)
{
//    btTransform trans = _physicsBody->getWorldTransform();
//    btQuaternion btRot = btQuaternion(rotateBy.x, rotateBy.y, rotateBy.z, rotateBy.w);
//
//    btRot =
//    
//    trans.setRotation(btRot);
//    _physicsBody->setWorldTransform(trans);

    //TODO: fix and complete this
}
//
//mat4 KMPhysicsNode::modelViewMatrix(bool includeParent)
//{
//    return KMNode::modelViewMatrix(includeParent);
//    
////    //TODO: cache and mark dirty (check with profiler first)
////    mat4 translate = mat4::Translate(this->getPosition());
////    mat4 rotate = this->getRotation().ToMatrix();
////    mat4 scale = mat4::Scale(this->getScale());
////    
////    mat4 mvm = scale * rotate * translate;
////    
////    //TODO: Test big level of nested nodes
////    //BUG: Doesn't work with physics node
////    //    if (includeParent && _parent)
////    //        mvm = _parent->modelViewMatrix(true) * mvm;
////    
////    return mvm;
//};


