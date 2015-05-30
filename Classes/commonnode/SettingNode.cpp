//
//  SettingLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/5/15.
//
//

#include "SettingNode.h"
#include "commonnode/HMenu.h"
#include "gamescene/GameMainScene.h"
#include "helper/GameMainHelper.h"

SettingNode::SettingNode():
musicVisible(NULL),
SoundVisible(NULL),
rankVisible(NULL)
{
}
SettingNode::~SettingNode(){
}
bool SettingNode::init(){
    if (Node::init()) {
        initBg();
        initMenu();
        initSprite();
        acNode();
        return true;
    }
    return false;
}
void SettingNode::initBg(){
    Size size = Director::getInstance()->getWinSize();
    bg = Sprite::create("setting_bg.png");
    bg->setAnchorPoint(Vec2(0.5,0.5f));
    bg->setPosition(Vec2(size.width/2,size.height*2/5));
    addChild(bg);
    
    Sprite* m_logo = Sprite::create("main_gamename.png");
    m_logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    m_logo ->setPosition(size.width/2, size.height-m_logo->getContentSize().height*3/4);
    addChild(m_logo);
    
}
void SettingNode::initSprite(){
    
    musicVisible->setVisible(GameMainHelper::getInstance()->getMusic());
    SoundVisible->setVisible(GameMainHelper::getInstance()->getSound());
    rankVisible->setVisible(GameMainHelper::getInstance()->getGoogleServer());
   
}
void SettingNode::initMenu(){
    Size size = bg->getContentSize();
    musicVisible = Sprite::createWithSpriteFrameName("music_1.png");
    musicVisible->setAnchorPoint(Vec2(0.49,0.8));
    musicVisible ->setPosition(size.width/2, size.height*3/4);
    bg->addChild(musicVisible,1);
    auto item1 = HMenu::create("music_2.png", "music_1.png", CC_CALLBACK_1(SettingNode::menuMusic, this) );
    
    item1->setAnchorPoint(Vec2(0.49,0.8));
    item1->setPosition(Vec2(size.width/2, size.height*3/4));
    auto item2 = HMenu::create("sound_2.png","sound_1.png", CC_CALLBACK_1(SettingNode::menuSound, this));

    
    SoundVisible = Sprite::createWithSpriteFrameName("sound_1.png");
    SoundVisible->setAnchorPoint(Vec2(0.49,0.79));
    SoundVisible ->setPosition(size.width/2, size.height/2);
    bg->addChild(SoundVisible,1);
    item2->setAnchorPoint(Vec2(0.49,0.79));
    item2->setPosition(Vec2(size.width/2, size.height/2));
    
    
    rankVisible = Sprite::createWithSpriteFrameName("rank_1.png");
    rankVisible->setAnchorPoint(Vec2(0.49,0.7));
    rankVisible ->setPosition(size.width/2, size.height/4);
    bg->addChild(rankVisible,1);
    
    auto item3 = HMenu::create("rank_2.png","rank_1.png", CC_CALLBACK_1(SettingNode::menuRank, this));
    
    item3->setAnchorPoint(Vec2(0.49,0.7));
    item3->setPosition(Vec2(size.width/2, size.height/4));
    
    auto item4 = HMenu::create("home_1.png","home_2.png", CC_CALLBACK_1(SettingNode::menuHome, this));
    Size winSize = Director::getInstance()->getWinSize();
    item4->setAnchorPoint(Vec2(1,0));
    item4->setPosition(Vec2(0, size.height));
    
    Menu* m_menu = Menu::create(item1, item2,item3,item4, nullptr);
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
    SoundVisible->setVisible(!SoundVisible->isVisible());
    GameMainHelper::getInstance()->setSound(SoundVisible->isVisible());
    UserDefault::getInstance()->setBoolForKey(SOUNDKEY, SoundVisible->isVisible());
   
}
void SettingNode::menuMusic(cocos2d::Ref *obj){
    musicVisible->setVisible(!musicVisible->isVisible());
    GameMainHelper::getInstance()->setMusic(musicVisible->isVisible());
    UserDefault::getInstance()->setBoolForKey(MUSICKEY, musicVisible->isVisible());
}
void SettingNode::menuRank(Ref* obj){
    rankVisible->setVisible(!rankVisible->isVisible());
    GameMainHelper::getInstance()->setGoogleServer(rankVisible->isVisible());
    UserDefault::getInstance()->setBoolForKey(RANKKEY, rankVisible->isVisible());
}
void SettingNode::menuHome(cocos2d::Ref *obj){
    
    GameMainScene* scene = (GameMainScene*) this->getParent();
    scene->showMenu();
    this->removeFromParentAndCleanup(true);
}











