//
//  KMRenderableTexturedLightened.h
//  Bowling
//
//  Created by Kirill Muzykov on 19/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef __Bowling__KMRenderableTexturedLightened__
#define __Bowling__KMRenderableTexturedLightened__

#include <OpenGLES/ES2/gl.h>

#include "KMRenderableModule.h"
#include <memory>

class KMLightSourceNode;

class KMRenderableModuleLighting : public KMRenderableModule
{
public:
    KMRenderableModuleLighting();
    virtual KMRenderableModuleType getModuleType() {return KMRenderableModuleType::Lighting; }
    
    void setLight0(std::shared_ptr<KMLightSourceNode> light0);
    void setLight1(std::shared_ptr<KMLightSourceNode> light1);
    void setLight2(std::shared_ptr<KMLightSourceNode> light2);
    
protected:
    virtual void onAdd(KMRenderable* owner, const KMShader& shader);
    virtual void preRender();
    virtual void postRender();
    
    std::shared_ptr<KMLightSourceNode>  _light0;
    std::shared_ptr<KMLightSourceNode>  _light1;
    std::shared_ptr<KMLightSourceNode>  _light2;
    
private:
    GLint _normalMatrixUniform;
    
    GLint _light0PositionUniform;
    GLint _light0IntensityUniform;
    
    GLint _light1PositionUniform;
    GLint _light1IntensityUniform;
    
    GLint _light2PositionUniform;
    GLint _light2IntensityUniform;
};


#endif /* defined(__Bowling__KMRenderableTexturedLightened__) */
