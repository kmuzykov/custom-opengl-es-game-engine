//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "GameScene.h"
#include "Level.h"

static const float Z_PLANE = -2.0f;

#define kGameFieldHalfWidth  0.7f
#define kGameFieldHalfHeigt  1.0f

GameScene::GameScene()
: KMScene()
{
    this->addLightSource(vec3(0,0.5,-1));

    addWalls();
    addBallAndBat();
    addBricks();
}

void GameScene::addBallAndBat()
{
    vec3 batPosition(0,-1, Z_PLANE);
    vec3 ballPosition = batPosition + vec3(0, 0.25f, 0);
    
    _bat = std::make_shared<Bat>();
    _bat->setPosition(batPosition);
    this->addChild(_bat);
    
    _ball = std::make_shared<Ball>();
    _ball->setPosition(ballPosition);
    this->addChild(_ball);
    
    //Starting movement vector
    _ball->setMovementVector(vec2(0.5f,0.5f));
}

void GameScene::addWalls()
{
    auto leftWall = std::make_shared<SideWall>();
    leftWall->setTag("left_wall");
    leftWall->setPosition(vec3(-0.8,0, Z_PLANE));
    this->addChild(leftWall);
    
    auto rightWall = std::make_shared<SideWall>();
    rightWall->setTag("right_wall");
    rightWall->setPosition(vec3(0.8,0, Z_PLANE));
    this->addChild(rightWall);
    
    auto topWall = std::make_shared<TopWall>();
    topWall->setTag("top_wall");
    topWall->setPosition(vec3(0,1.2, Z_PLANE));
    this->addChild(topWall);
    
    std::shared_ptr<ArkanoidGameObject> walls[] = {topWall, rightWall, leftWall};
    for (const auto& wall : walls)
    {
        for (const CollidableSurface& surf : wall->getCollidableSurfaces())
        {
            _collidableSurfaces.push_back(surf);
        }
    }
}

void GameScene::addBricks()
{
    Level l1 = Level::getLevelByNumber(0);
    
    for (const vec2& brickPos : l1.getBrickPositions())
    {
        vec3 brickPos3D = vec3(brickPos.x, brickPos.y, Z_PLANE);
        
        auto brick = std::make_shared<Brick>();
        brick->setPosition(brickPos3D);
        this->addChild(brick);
        
        for (const CollidableSurface& surf : brick->getCollidableSurfaces())
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
    CollidableSurface* collidedSurf = nullptr;
    
    //Adding bat at its current position to the list of surfaces to check
    std::list<CollidableSurface> surfacesToCheck(_collidableSurfaces);
    for (const CollidableSurface& batSurface : _bat->getCollidableSurfaces())
    {
        surfacesToCheck.push_back(batSurface);
    }
    
    //Iterating over that extended list (that includes bat)
    for (CollidableSurface& surf : surfacesToCheck)
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
    
    if (intersectsAtLeastOnce && collidedSurf)
    {
        handleCollision(collidedSurf, finalIntersectionPoint, ballMovementVec);
    }
    else
    {
        _ball->setPosition2D(ballDesiredPos);
    }
}

void GameScene::handleCollision(const CollidableSurface* collidedSurf, const vec2& finalIntersectionPoint, const vec2& ballMovementVec)
{
    const ArkanoidGameObject* go = collidedSurf->getOwner();
    //KMLOG("Collided with: %s", go->getTag().c_str());

    
    ArkanoidGameObjectType goType = go->getObjectType();
    if (goType == ArkanoidGameObjectType::Brick)
    {
        _collidableSurfaces.remove_if([go](const CollidableSurface& surf) { return surf.getOwner() == go;});
        _bricks.remove_if([go](const Brick* brick) { return brick == go;});


        this->removeChildRaw(go);
    }
    
    vec2 reflectVec = collidedSurf->reflectVector(ballMovementVec);
    _ball->setMovementVector(reflectVec);

}
