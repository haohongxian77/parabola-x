//
//  SettingLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/5/15.
//
//

#include "SettingNode.h"
SettingNode::SettingNode(){
}
SettingNode::~SettingNode(){
}
bool SettingNode::init(){
    if (Node::init()) {
        initBg();
        initMenu();
        acNode();
        return true;
    }
    return false;
}
void SettingNode::initBg(){
    Size size = Director::getInstance()->getWinSize();
    bg = Sprite::create("set_bg.png");
    bg->setAnchorPoint(Vec2(0.5,0.5f));
    bg->setPosition(Vec2(size.width/2,size.height/2));
    addChild(bg);
    
}
void SettingNode::initMenu(){
    Size size = bg->getContentSize();
    
    auto item1 = MenuItemImage::create("menu/menu_open.png", "menu/menu_open.png", CC_CALLBACK_1(SettingNode::menuMusic, this) );
    item1->setAnchorPoint(Vec2(1,0.5));
    item1->setPosition(Vec2(size.width*3/4-5, size.height*3/4-10));
    auto item2 = MenuItemImage::create("menu/menu_open.png", "menu/menu_open.png", CC_CALLBACK_1(SettingNode::menuSound, this) );
    item2->setAnchorPoint(Vec2(1,0.5));
    item2->setPosition(Vec2(size.width*3/4-5, size.height/4+10));
    
    Menu* m_menu = Menu::create(item1, item2, nullptr);
    bg->addChild(m_menu);
    m_menu->setAnchorPoint(Vec2(0, 0));
    m_menu->setPosition(Vec2(0,0));
}
void SettingNode::acNode(){
    bg->setScale(0);
    ScaleTo* scaleTo1 = ScaleTo::create(0.3, 1.2);
    ScaleTo* scaleTo2 = ScaleTo::create(0.1, 1);
    Sequence* seq = Sequence::create(scaleTo1,scaleTo2, NULL);
    bg->runAction(seq);
}
void SettingNode::menuSound(cocos2d::Ref *obj){
}
void SettingNode::menuMusic(cocos2d::Ref *obj){
}











