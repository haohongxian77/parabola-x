#ifndef __GameMain_SCENE_H__
#define __GameMain_SCENE_H__

#include "cocos2d.h"
#include "menulayer/MainLayer.h"
#include "gamelayer/GameMainLayer.h"
#include "gamelayer/GameBgLayer.h"
class GameMainScene : public cocos2d::Scene
{
private:
    GameMainScene();
    ~GameMainScene();
    GameMainLayer* m_gamemainLayer;
    MainLayer* m_mianMenuLayer;
    GameBgLayer* m_bgLayer;
public:
    bool init();
    void initMainLayer();
    void initGameAlertLayer(gameStatus gameS);
    void initGameBgLayer();
    
    // a selector callback
    //CREATE_FUNC(GameMainScene);
    static GameMainScene* createWithTag(gameStatus gameS);
    void startGame();
    void gameOver();
    std::string cutOff();
    
    void onEnter();
    void onExit();
};

#endif // __HELLOWORLD_SCENE_H__
