#include "GameMainScene.h"
#include "GameSpileLayer.h"
USING_NS_CC;

GameMainScene::GameMainScene():
m_gamemainLayer(NULL),
m_mianMenuLayer(NULL)
{
}
bool GameMainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    return true;
}

void GameMainScene::initMainLayer(){

    m_gamemainLayer = GameMainLayer::create();
    addChild(m_gamemainLayer,0);
    
}
void GameMainScene::initGameAlertLayer(gameStatus gameS){
    m_mianMenuLayer = MainLayer::create(gameS);
    this->addChild(m_mianMenuLayer,1);
   
}
GameMainScene* GameMainScene::createWithTag(gameStatus gameS){
    GameMainScene* sc = new GameMainScene();
    if (sc->init()) {
        sc->initMainLayer();
        sc->initGameAlertLayer(gameS);
        return sc;
    }
    return NULL;
}
void GameMainScene::startGame(){
    if(m_mianMenuLayer){
        m_mianMenuLayer ->removeFromParentAndCleanup(true);
        m_mianMenuLayer =NULL;
    }
}
void GameMainScene::gameOver(){
}













