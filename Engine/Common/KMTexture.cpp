//
//  KMTexture.cpp
//  KMEngine
//
//  Created by Kirill Muzykov on 17/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMTexture.h"
#include "KMFileUtils.h"
#include "KMMacros.h"
#include "KMConfig.h"

KMTexture::KMTexture(const char* fileName)
{
    _name = KMFileUtils::getSharedFileUtils().loadTexture(fileName);
}