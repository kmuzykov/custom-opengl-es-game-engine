//
//  KMGameObject.h
//  KMEngine
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMGameObject__
#define __KMEngine__KMGameObject__

#include "KMNode.h"
#include <memory>

class KMRenderer;

#if KM_PHYSICS > 0
class KMPhysicsBody;
class btRigidBody;
#endif

class KMGameObject : public KMNode
{
public:
    KMGameObject();
    virtual ~KMGameObject();
    
    virtual void update(float dt);
    virtual void draw();
    
    void setRenderer(const std::shared_ptr<KMRenderer>& renderer) { _renderer = renderer;}
    
#if KM_PHYSICS > 0
    //Overriding position and rotation in case we need to take into account physics body.
    virtual const vec3& getPosition();
    virtual void setPosition(const vec3& position);
    virtual const Quaternion& getRotation();
    virtual void setRotation(const Quaternion& rotation);
    
    virtual void rotateBy(Quaternion rotateBy);

    btRigidBody* getPhysicsBody() const { return _physicsBody.get(); }
#endif

protected:
    std::shared_ptr<KMRenderer>  _renderer;
    
#if KM_PHYSICS > 0
    std::unique_ptr<btRigidBody> _physicsBody;
#endif
};


#endif
