//
//  KMRenderableModule.h
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef Bowling_KMRenderableModule_h
#define Bowling_KMRenderableModule_h

class KMRenderable;
class KMShader;

enum class KMRenderableModuleType
{
    UniformColor,
    Texture,
    Lighting
};

class KMRenderableModule
{
    friend class KMRenderable;
    
public:
    virtual KMRenderableModuleType getModuleType() = 0;
protected:
    KMRenderable* _owner;
    
    virtual void onAdd(KMRenderable* owner, const KMShader& shader) { _owner = owner;}
    virtual void preRender() = 0;
    virtual void postRender() = 0;
};


#endif
