//
//  GameMainLogoLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/15/15.
//
//

#include "GameMainLogoLayer.h"
bool GameMainLogoLayer::init(){
    if (Layer::init()) {
        Size size = Director::getInstance()->getWinSize();
        
        Sprite* m_logo = Sprite::create("main_gamename.png");
        m_logo->setAnchorPoint(Vec2(0.5f, 0.5f));
        //    m_logo ->setPosition(size.width/2, size.height+m_logo->getContentSize().height/2);
        m_logo ->setPosition(size.width/2, size.height-m_logo->getContentSize().height*3/4);
        addChild(m_logo);

        return true;
    }
    return false;
}