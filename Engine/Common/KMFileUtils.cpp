//
//  P3DFileUtils.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMFileUtils.h"
#include "KMConfig.h"

#ifdef IOS
#import "KMFileUtilsIOS.h"
#endif

KMFileUtils& KMFileUtils::getSharedFileUtils()
{
#ifdef IOS
    static KMFileUtilsIOS fileUtils;
#endif
    return fileUtils;
}

