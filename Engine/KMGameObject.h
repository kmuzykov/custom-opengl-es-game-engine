//
//  KMGameObject.h
//  Bowling
//
//  Created by Kirill Muzykov on 13/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__KMGameObject__
#define __KMEngine__KMGameObject__

#include "KMNode.h"
#include <memory>

class KMRenderer;
class KMPhysicsBody;
class btRigidBody;

class KMGameObject : public KMNode
{
public:
    KMGameObject();
    virtual ~KMGameObject();
    
    virtual void update(float dt);
    virtual void draw();
    
    //Overriding position and rotation in case we need to take into account physics body.
    virtual vec3 getPosition() const;
    virtual void setPosition(const vec3& position);
    virtual Quaternion getRotation() const;
    virtual void setRotation(Quaternion rotation);
    
    virtual void rotateBy(Quaternion rotateBy);

    btRigidBody* getPhysicsBody() const { return _physicsBody.get(); }

protected:
    std::shared_ptr<KMRenderer>  _renderer;
    std::unique_ptr<btRigidBody> _physicsBody;
};


#endif
