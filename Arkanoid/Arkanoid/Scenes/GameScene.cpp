//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "GameScene.h"

#define kGameFieldHalfWidth  0.7f
#define kGameFieldHalfHeigt  1.0f

GameScene::GameScene()
: KMScene()
{
    this->addLightSource(vec3(0,0.5,-1));
    
    _ball = std::make_shared<Ball>();
    _ball->setPosition(vec3(0,0,-2));
    this->addChild(_ball);
    
    _bat = std::make_shared<Bat>();
    _bat->setPosition(vec3(0,-1,-2));
    this->addChild(_bat);
    
    auto brick = std::make_shared<Brick>();
    brick->setPosition(vec3(0.7,1,-2));
    this->addChild(brick);
}

void GameScene::update(float dt)
{
    KMScene::update(dt);
    
    vec2    ballPosition = _ball->getPosition2D();
    vec2    ballMovementVec    = _ball->getMovementVector();
    vec2    ballPosChange      = ballMovementVec * dt;
    vec2    ballDesiredPos     = ballPosition + ballPosChange;
    
    //Checking intersection with walls
    
//    if ((ballDesiredPos.x > kGameFieldHalfWidth) || (ballDesiredPos.x < -1 * kGameFieldHalfWidth))
//    {
//        ballPosition.x = -1 * ballPosition.x;
//        _ball->setPosition2D(ballPosition);
//    }
//    else if (ballDesiredPos.y > kGameFieldHalfHeigt)
//    {
//        ballPosition.x
//    }
    
    

    
    
//    Line2D  ballMovementLine   = Line2D(ballPos, ballDesiredPos);
//    float   distanceToMove     = ballMovementLine.Length();

}
