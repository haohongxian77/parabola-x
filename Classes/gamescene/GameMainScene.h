#ifndef __GameMain_SCENE_H__
#define __GameMain_SCENE_H__

#include "cocos2d.h"
#include "mainlayer/MainLayer.h"
#include "GameMainLayer.h"
class GameMainScene : public cocos2d::Scene
{
private:
    GameMainScene();
    GameMainLayer* m_gamemainLayer;
    MainLayer* m_mianMenuLayer;
public:
    bool init();
    void initMainLayer();
    void initGameAlertLayer(gameStatus gameS);
    
    // a selector callback
    //CREATE_FUNC(GameMainScene);
    static GameMainScene* createWithTag(gameStatus gameS);
    void startGame();
    void gameOver();
    
};

#endif // __HELLOWORLD_SCENE_H__
