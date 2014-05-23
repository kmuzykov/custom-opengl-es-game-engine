//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 23/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "GameScene.h"

GameScene::GameScene()
: KMScene()
{
    this->addLightSource(vec3(0,0.5,-1));
    
    auto ball = std::make_shared<Ball>();
    ball->setPosition(vec3(0,0,-2));
    this->addChild(ball);
    
    auto bat = std::make_shared<Bat>();
    bat->setPosition(vec3(0,-1,-2));
    this->addChild(bat);
}
