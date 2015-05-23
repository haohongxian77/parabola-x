#ifndef __GameMain_SCENE_H__
#define __GameMain_SCENE_H__

#include "cocos2d.h"
#include "menulayer/MainLayer.h"
#include "gamelayer/GameMainLayer.h"
#include "gamelayer/GameBgLayer.h"
#include "gamelayer/GameBgBeforeLayer.h"
#include "helper/CommomData.h"
#include "gamelayer/GameUIlayer.h"
typedef enum{
    GAMEBGLAYER = -10,      //背景层
    GAMEMAINLAYER ,       //游戏层
    GAMEBGBEFORELAYER,        //前景层
    GAMEUILAYER,      //游戏UI层
    GAMEMENULAYER,          //开始和死亡按钮层
} LayerIndex;
class GameMainHelper;
class GameMainScene : public cocos2d::Scene
{
private:
    GameMainScene();
    ~GameMainScene();
    GameBgLayer* m_bgLayer;
    GameMainLayer* m_gamemainLayer;
    GameBgBeforeLayer* m_bgBfLayer;
    GameUIlayer* m_gameUILayer;
    MainLayer* m_mianMenuLayer;
    
    GameMainHelper* m_helper;
private:
    void initHelper();
    
    
public:
  
    bool init();
    void initMainLayer();
    void initGameAlertLayer(gameStatus gameS);
    void initGameBgLayer();
    void initGameBgBFLayer();
    void initGameUIlayer();
    
    // a selector callback
    //CREATE_FUNC(GameMainScene);
    static GameMainScene* create();
    void startGame();
    void gameOver();
    void showAlertView();
    void changeScore();
    
    void onEnter();
    void onExit();
    void update(float dt);
//    std::string cutOff(int shareType);
private:
    int m_shareType = 0;
};

#endif // __HELLOWORLD_SCENE_H__
