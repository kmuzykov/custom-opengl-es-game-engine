//
//  Level.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "Level.h"

using namespace std;

Level Level::getLevelByNumber(int levelNumber)
{
    vector<vector<int>> l1
    {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 1, 1},
        {1, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
    };
    
    float brickWidth = 0.2f;
    float brickHeight = 0.09f;
    float paddingX = 0.025f;
    float paddingY = 0.01f;
    float startX = -0.65f;
    float startY = -0.3f;
    
    Level level1;
    for (int col = 0; col < l1.size(); col++)
    {
        for (int row = 0; row < l1[col].size(); row++)
        {
            if (l1[col][row])
            {
                float x = startX + brickWidth * row + brickWidth * 0.5f + (paddingX * row);
                float y = startY - brickHeight * col - brickHeight * 0.5f - (paddingY * col);
                level1._brickPositions.push_back(vec2(x,y));
            }
        }
    }
    
    return level1;
}
