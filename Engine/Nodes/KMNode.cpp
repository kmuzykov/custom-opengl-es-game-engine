//
//  KMNode.cpp
//  KMEngine
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMNode.h"
#include "KMDirector.h"
#include "KMMacros.h"

using namespace std;

KMNode::KMNode()
{
    _scale = 1.0f;
    _parent = nullptr;
}

KMNode::~KMNode()
{
    _parent = nullptr;
}

void KMNode::update(float dt)
{
    for (auto& child : _children)
    {
        child->update(dt);
    }
}

void KMNode::draw()
{
    for (auto& child : _children)
    {
        child->draw();
    }    
};

void KMNode::addChild(const shared_ptr<KMNode>& node)
{
    node->_parent = this;
    _children.push_back(node);
}

void KMNode::removeChild(const shared_ptr<KMNode>& node)
{
    node->_parent = nullptr;
    _children.remove(node);
}

void KMNode::removeChildRaw(const KMNode* node)
{
    _children.remove_if([node](const std::shared_ptr<KMNode> child) {return child.get() == node; });    
}

const list<shared_ptr<KMNode>>& KMNode::getChildren() const
{
    return _children;
}

mat4 KMNode::modelViewMatrix(bool includeParent)
{
    //TODO: cache and mark dirty (check with profiler first)
    //TODO: Test big level of nested nodes

    //Calculating current node's MVM
    mat4 translate = mat4::Translate(this->getPosition());
    mat4 rotate = this->getRotation().ToMatrix();
    mat4 scale = mat4::Scale(this->getScale());
    mat4 mvm = scale * rotate * translate;
    
    //Multipluing with all parents.
    if (includeParent && _parent)
        mvm*= _parent->modelViewMatrix(true);
    
    return mvm;
};
