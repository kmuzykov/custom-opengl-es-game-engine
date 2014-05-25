//
//  KMTextureCache.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__KMTextureCache__
#define __Arkanoid__KMTextureCache__

#include "KMTexture.h"
#include <map>
#include <string>

class KMTextureCache
{
public:
    static const KMTexture& loadTexture(const std::string& path);
    static KMTextureCache& getSharedTextureCache();

private:
    std::map<std::string, KMTexture> _textures;
    
    KMTextureCache() {}
    KMTextureCache(const KMTextureCache& other) = delete;
    KMTextureCache& operator=(const KMTextureCache& other) = delete;
};

#endif /* defined(__Arkanoid__KMTextureCache__) */
