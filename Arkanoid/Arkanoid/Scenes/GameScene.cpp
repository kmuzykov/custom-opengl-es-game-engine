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
    
//  _ball->setMovementVector(vec2(-0,0.25));
    _ball->setMovementVector(vec2(-0.25,0));
    
    auto leftWall = std::make_shared<SideWall>();
    leftWall->setPosition(vec3(-0.8,0, -2));
    this->addChild(leftWall);
    
    auto rightWall = std::make_shared<SideWall>();
    rightWall->setPosition(vec3(0.8,0, -2));
    this->addChild(rightWall);

    auto topWall = std::make_shared<TopWall>();
    topWall->setPosition(vec3(0,1.2,-2));
    this->addChild(topWall);
    
    std::shared_ptr<ArkanoidGameObject> walls[] = {topWall, rightWall, leftWall};
    for (auto& wall : walls)
    {
        for (const CollidableSurface& surf : wall->getCollidableSurfaces())
        {
            _collidableSurfaces.push_back(surf);
        }
    }
}

void GameScene::update(float dt)
{
    KMScene::update(dt);
    
    vec2    ballPosition = _ball->getPosition2D();
    vec2    ballMovementVec    = _ball->getMovementVector();
    vec2    ballPosChange      = ballMovementVec * dt;
    vec2    ballDesiredPos     = ballPosition + ballPosChange;
    
    vec2 finalIntersectionPoint;
    bool intersectsAtLeastOnce = false;
    CollidableSurface* collidedSurf;
    
    for (CollidableSurface& surf : _collidableSurfaces)
    {
        if (!surf.isBallMovingTowards(ballMovementVec))
            continue;
        
        vec2 intersectionPoint;
        if (surf.ballIntersectsWhileMoving(ballPosition, ballDesiredPos, ballMovementVec, 0.05, intersectionPoint)) //TODO: Don't hardcode radius
        {
            if (intersectsAtLeastOnce)
            {
                bool newPointCloser = (finalIntersectionPoint - ballPosition).LengthSquared() < (intersectionPoint - ballPosition).LengthSquared();
                if (newPointCloser)
                {
                    finalIntersectionPoint = intersectionPoint;
                    collidedSurf = &surf;
                }
            }
            else
            {
                finalIntersectionPoint = intersectionPoint;
                collidedSurf = &surf;
            }
            
            intersectsAtLeastOnce = true;
        }
    }
    
    if (intersectsAtLeastOnce)
    {
        vec2 reflectVec = collidedSurf->reflectVector(ballMovementVec);
        _ball->setMovementVector(reflectVec);
    }
    else
    {
        _ball->setPosition2D(ballDesiredPos);
    }
    
    
    //Checking intersection with walls
    
//    if ((ballDesiredPos.x > kGameFieldHalfWidth) || (ballDesiredPos.x < -1 * kGameFieldHalfWidth))
//    {
//        ballPosition.x = -1 * ballPosition.x;
//        _ball->setPosition2D(ballPosition);
//    }(finalIntersectionPoint - ballPosition).LengthSquared() < (intersectionPoint - ballPosition.LengthSquared())
//    else if (ballDesiredPos.y > kGameFieldHalfHeigt)
//    {
//        ballPosition.x
//    }
    
    

    
    
//    Line2D  ballMovementLine   = Line2D(ballPos, ballDesiredPos);
//    float   distanceToMove     = ballMovementLine.Length();

}
