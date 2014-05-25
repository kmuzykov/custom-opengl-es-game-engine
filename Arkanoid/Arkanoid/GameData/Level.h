//
//  Level.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__Level__
#define __Arkanoid__Level__

#include "KMEngine.h"

class Level
{
public:
    const std::vector<vec2>& getBrickPositions() { return _brickPositions; }
    
    static Level getLevelByNumber(int levelNumber);

private:
    std::vector<vec2> _brickPositions;
};

#endif /* defined(__Arkanoid__Level__) */
