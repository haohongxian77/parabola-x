#include "GameMainScene.h"
#include "GameMainLayer.h"
#include "GameSpileLayer.h"
USING_NS_CC;


bool GameMainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    initLayer();
    return true;
}

void GameMainScene::initLayer(){
//    GameSpileLayer* spileLayer = GameSpileLayer::create();
//    addChild(spileLayer);

    GameMainLayer* mainLayer = GameMainLayer::create();
    addChild(mainLayer);
    
    }



