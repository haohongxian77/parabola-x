//
//  StartLayer.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#ifndef __GWPJUMP__StartLayer__
#define __GWPJUMP__StartLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class StartLayer :public Layer{
    StartLayer();
    ~StartLayer();
private:
    bool init();
    void initBg();
    void initGWSsmall();
    void initGWSBig();
    void initHero();
    
private:
    Sprite* m_spG = NULL;
    Sprite* m_spW = NULL;
    Sprite* m_spS = NULL;
    //Node* m_spGWSNode = NULL;
    
    Sprite* m_spHero = NULL;
    Sprite* m_spGWS = NULL;

private:
    void acGWSSp();
    
    void changeScene();
//    Action* getFallDownAC(Action* ac);
//    void getShakeAction();
    
public:
    virtual void onEnter();
    CREATE_FUNC(StartLayer);

private:  //划线相关
    
    
    
    
};
#endif /* defined(__GWPJUMP__StartLayer__) */
