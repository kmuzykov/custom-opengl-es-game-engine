//
//  KMConfig.h
//  KMEngine
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


//Can be useful to disable and see only physics wireframe
#define KM_RENDER_ENABLED 1
#define KM_RENDER_PHYSICS_DEBUG_ENABLED 0


#endif
