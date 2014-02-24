//
//  Node.h
//  Bowling
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__Node__
#define __Bowling__Node__

#include "Vector.hpp"
#include "Quaternion.hpp"
#include "Matrix.hpp"

#include <memory>
#include <list>


class KMNode
{
    friend class KMDirector;
    
public:
    KMNode();
    virtual ~KMNode();
    
    void addChild(const std::shared_ptr<KMNode>& node);
    void removeChild(const std::shared_ptr<KMNode>& node);
    const std::list<std::shared_ptr<KMNode>>& getChildren() const;
    
    virtual vec3 getPosition() const { return _position; }
    virtual void setPosition(const vec3& position) { _position = position; }
    
    virtual float getScale() const { return _scale; }
    virtual void setScale(float scale) { _scale = scale; }
    
    virtual Quaternion getRotation() const { return _rotation; }
    virtual void setRotation(Quaternion rotation) { _rotation = rotation; }
    virtual void rotateBy(Quaternion rotateBy) { _rotation.Rotate(rotateBy); }

    virtual mat4 modelViewMatrix(bool includeParent);
protected:
    KMNode* _parent;
    
    virtual void update(float dt);
    virtual void draw();
    
private:
    vec3 _position;
    Quaternion _rotation;
    float _scale;
    
    std::list<std::shared_ptr<KMNode>> _children;
};

#endif /* defined(__Bowling__Node__) */
