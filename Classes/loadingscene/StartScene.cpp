//
//  StartScene.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#include "StartScene.h"
#include "StartLayer.h"
bool StartScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    initLayer();
    return true;
}

void StartScene::initLayer(){
    //    GameSpileLayer* spileLayer = GameSpileLayer::create();
    //    addChild(spileLayer);
    
    StartLayer* startLayer = StartLayer::create();
    addChild(startLayer);
    
}