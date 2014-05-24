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

class GameScene : public KMScene
{
public:
    GameScene();

protected:
    virtual void update(float dt);

private:
    std::vector<CollidableSurface> _collidableSurfaces;
    
    std::shared_ptr<Ball> _ball;
    std::shared_ptr<Bat> _bat;
    
    std::vector<std::shared_ptr<Brick>> _bricks;    
};


#endif /* defined(__Arkanoid__GameScene__) */
