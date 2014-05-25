//
//  KMTextureCache.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "KMTextureCache.h"

KMTextureCache& KMTextureCache::getSharedTextureCache()
{
    static KMTextureCache _Instance;
    return _Instance;
};

const KMTexture& KMTextureCache::loadTexture(const std::string& path)
{
    KMTextureCache& cache = getSharedTextureCache();
    
    auto iter = cache._textures.find(path);
    if (iter != cache._textures.end())
    {
        return (*iter).second;
    }
    else
    {
        cache._textures.insert(std::pair<std::string,KMTexture>(path, KMTexture(path.c_str())));
        return cache._textures.at(path);
    }
}
