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

class GameScene : public KMScene, public ITouchSubscriber
{
public:
    GameScene();
    virtual ~GameScene();
    
    virtual void touchBegan(const vec2& location);
    virtual void touchMoved(const vec2& location);
    virtual void touchEnded(const vec2& location);

protected:
    virtual void update(float dt);

private:
    unsigned long _brickCount;
    std::shared_ptr<Ball> _ball;
    std::shared_ptr<Bat> _bat;
    std::list<CollidableSurface> _collidableSurfaces;
    
    void addBallAndBat();
    void addWalls();
    void addBricks();
    
    void handleCollision(const CollidableSurface* collidedSurf, const vec2& finalIntersectionPoint, const vec2& ballMovementVec);
    void moveBatToPosition(const vec2& position);
    
    void win();
    void lost();
    void restart();
    
    enum class GameState
    {
        Init,
        Playing,
        Won,
        Lost
    } _gameState;
};


#endif /* defined(__Arkanoid__GameScene__) */
