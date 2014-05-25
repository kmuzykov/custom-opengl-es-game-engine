//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "GameScene.h"
#include "Level.h"
#include <cmath>

static const float Z_PLANE = -2.0f;
static const float MAX_BAT_REFLECT_ANGLE = 30.0f;
static const float DEATH_DISTANCE = -0.25f;

#define kGameFieldHalfWidth  0.7f
#define kGameFieldHalfHeigt  1.0f

GameScene::GameScene()
: KMScene(),
_brickCount(0)
{
    _gameState = GameState::Init;
    
    this->addLightSource(vec3(0,0.5,-1));
    
    addWalls();
    addBallAndBat();
    addBricks();
    
    KMTouchDispatcher::getSharedInstance().subscribe(this);
}

GameScene::~GameScene()
{
    KMTouchDispatcher::getSharedInstance().unsubscribe(this);
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
    //_ball->setMovementVector(vec2(0.75f,0.75f));
    _ball->setMovementVector(vec2(0,0.75f));
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
    auto brickPositions = l1.getBrickPositions();
    _brickCount = brickPositions.size();
    
    for (const vec2& brickPos : brickPositions)
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
    
    //If not playing do nothing
    if (_gameState != GameState::Playing)
        return;
    
    //Checking if ball fallen
    vec2    ballPosition = _ball->getPosition2D();
    if (ballPosition.y < (_bat->getPosition().y + DEATH_DISTANCE))
    {
        lost();
        return;
    }
    
    //Few values we'll need for CCD
    vec2    ballMovementVec    = _ball->getMovementVector();
    vec2    ballPosChange      = ballMovementVec * dt;
    vec2    ballDesiredPos     = ballPosition + ballPosChange;
    
    //Results of collision detection
    vec2 finalIntersectionPoint;
    bool intersectsAtLeastOnce = false;
    CollidableSurface* collidedSurf = nullptr;
    
    //Moving bat into desired position (to keep in sync with visual position and collidable surfaces)
    _bat->applyDesiredPosition();
    
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
                bool newPointCloser = ((intersectionPoint - ballPosition).LengthSquared() < (finalIntersectionPoint - ballPosition).LengthSquared());
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
        //In case ball collided with something we've got stuff to do.
        handleCollision(collidedSurf, finalIntersectionPoint, ballMovementVec);
    }
    else
    {
        //In case there are no obstacles simply putting the bal where it wants to be
        _ball->setPosition2D(ballDesiredPos);
    }
}

void GameScene::handleCollision(const CollidableSurface* collidedSurf, const vec2& finalIntersectionPoint, const vec2& ballMovementVec)
{
    const ArkanoidGameObject* go = collidedSurf->getOwner();
    //KMLOG("Collided with: %s", go->getTag().c_str());
    
    //Getting type of object (brick, bat, wall)
    ArkanoidGameObjectType goType = go->getObjectType();
    
    //If we hit brick need to remove it.
    if (goType == ArkanoidGameObjectType::Brick)
    {
        //Removing everything brick from everywhere
        _collidableSurfaces.remove_if([go](const CollidableSurface& surf) { return surf.getOwner() == go;}); //removing brick surfaces
        this->removeChildRaw(go);                                                                            //removing from the scene
        
        //If no more bricks we won
        _brickCount--;
        if (_brickCount <= 0)
            win();
    }

    //If we hit top surface of the bat we need to adjust reflect angle, since in Arkanoid it depends on where you hit the bat.
    vec2 up(0,1);
    const vec2& normal = collidedSurf->getNormal();
    if (goType == ArkanoidGameObjectType::Bat && (normal == up))
    {
        float x = finalIntersectionPoint.x;                 //Point we've hit the bat
        float batCenterX = _bat->getPosition().x;           //Center of the bat
        float batHalf = collidedSurf->getLength() * 0.5f;   //Half of the bat width
        float distanceFromCenter = x - batCenterX;          //Distance we've hit from centers
        
        //Calculating angle we should get reflected
        float turnAngle = -MAX_BAT_REFLECT_ANGLE * (distanceFromCenter/batHalf);
        
        vec2 reflectVec = normal.Rotate(turnAngle) * ballMovementVec.Length();
        _ball->setMovementVector(reflectVec);
    }
    else
    {
        //In all other cases calculating standard reflect vector.
        vec2 reflectVec = collidedSurf->reflectVector(ballMovementVec);
        _ball->setMovementVector(reflectVec);
    }
    
    //Moving ball to the point of intersection (since it can't go further)
    vec2 newBallPosition = finalIntersectionPoint + (normal * 0.01f);
    _ball->setPosition2D(newBallPosition);
}

void GameScene::win()
{
    _gameState = GameState::Won;
}

void GameScene::lost()
{
    _gameState = GameState::Lost;
}

void GameScene::restart()
{
    //Restarting by simply reloading scene to test scene management.
    auto newInstanceOfScene = std::make_shared<GameScene>();
    KMDirector::getSharedDirector().runScene(newInstanceOfScene);
}

void GameScene::touchBegan(const vec2& location)
{
    if (_gameState == GameState::Init)
    {
        //If we touched the screen and game not started yet. Starting the game.
        _gameState = GameState::Playing;
    }
    else if (_gameState == GameState::Lost || _gameState == GameState::Won)
    {
        //If touching the screen when won/lost restarting the game.
        restart();
    }
    
    //If playing then simply allowing to control the bat.
    if (_gameState == GameState::Playing)
        moveBatToPosition(location);
}

void GameScene::touchMoved(const vec2& location)
{
    if (_gameState == GameState::Playing)
        moveBatToPosition(location);
}

void GameScene::touchEnded(const vec2& location)
{
    
}

inline float clampf( float v, float min, float max )
{
    if( v < min ) v = min;
    if( v > max ) v = max;
    
    return v;
}

void GameScene::moveBatToPosition(const vec2& position)
{
    static float screenWidth = KMDirector::getSharedDirector().getViewWidth();
    static float gameFieldWidth = 1.6f;
    
    float normalizedPos = position.x/screenWidth;
    float gamePos = (gameFieldWidth * normalizedPos) - gameFieldWidth * 0.5f;
    
    //Using clamping instead of setting gameFieldWidth to [-0.5, 0.5] gives better bat control
    //since its center always right below the finger.  If uisng mapping interval the bat handling point tends
    //to go closer to edge when finger near the edge screen.
    gamePos = clampf(gamePos, -0.5f, 0.5f);
    
    _bat->setDesiredPosition(gamePos);
}
