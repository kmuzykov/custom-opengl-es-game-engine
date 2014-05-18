//
//  P3DConfig.h
//  Pixel3D
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#ifndef KMConfig_h
#define KMConfig_h

#define KM_PLATFORM_IOS        1
#define KM_PLATFORM_ANDROID    2

#define KM_PLATFORM  KM_PLATFORM_IOS

#if KM_PLATFORM == KM_PLATFORM_IOS
    #define IOS
#else
    #define ANDROID
#endif


#define KM_MAX_LIGHTS   8


#endif
