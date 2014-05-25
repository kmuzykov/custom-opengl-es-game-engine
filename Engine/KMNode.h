//
//  KMNode.h
//  KMEngine
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __KMEngine__Node__
#define __KMEngine__Node__

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
    void removeChildRaw(const KMNode* node);
    
    const std::list<std::shared_ptr<KMNode>>& getChildren() const;
    
    virtual const vec3& getPosition() { return _position; }
    virtual void setPosition(const vec3& position) { _position = position; }
    
    virtual float getScale() const { return _scale; }
    virtual void setScale(float scale) { _scale = scale; }
    
    virtual const Quaternion& getRotation() { return _rotation; }
    virtual void setRotation(const Quaternion& rotation) { _rotation = rotation; }
    virtual void rotateBy(const Quaternion& rotateBy) { _rotation.Rotate(rotateBy); }

    virtual mat4 modelViewMatrix(bool includeParent);
protected:
    vec3        _position;
    Quaternion  _rotation;
    float       _scale;

    KMNode* _parent;
    std::list<std::shared_ptr<KMNode>> _children;
    
    virtual void update(float dt);
    virtual void draw();
};

#endif /* defined(__Bowling__Node__) */
