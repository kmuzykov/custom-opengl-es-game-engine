//
//  GLDebugDrawer.h
//  Bowling
//
//  Created by Kirill Muzykov on 18/05/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.


#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H

#include "btBulletDynamicsCommon.h"

#include "KMShader.h"

class KMPhysicsDebugDrawer : public btIDebugDraw
{
private:
    int m_debugMode;
    KMShader _shader;    
    
public:    
    KMPhysicsDebugDrawer();
    
    virtual void   drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
    virtual void   drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
    virtual void   reportErrorWarning(const char* warningString);

    virtual void   draw3dText(const btVector3& location,const char* textString);
    virtual void   setDebugMode(int debugMode);
    virtual int      getDebugMode() const { return m_debugMode;}
};
#endif