//
//  GameScene.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__GameScene__
#define __Arkanoid__GameScene__

#include "KMEngine.h"
#include "Ball.h"
#include "Bat.h"
#include "Brick.h"
#include "SideWall.h"
#include "TopWall.h"

#include "CollidableSurface.h"

#include <memory>
#include <vector>
#include <list>

class GameScene : public KMScene
{
public:
    GameScene();

protected:
    virtual void update(float dt);

private:
    std::shared_ptr<Ball> _ball;
    std::shared_ptr<Bat> _bat;
    std::list<Brick*> _bricks;
    std::list<CollidableSurface> _collidableSurfaces;
    
    void addBallAndBat();
    void addWalls();
    void addBricks();
    
    void handleCollision(const CollidableSurface* collidedSurf, const vec2& finalIntersectionPoint, const vec2& ballMovementVec);
};


#endif /* defined(__Arkanoid__GameScene__) */
