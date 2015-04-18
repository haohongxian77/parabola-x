//
//  MainLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#include "MainLayer.h"
#include "commonnode/SettingNode.h"
#include "commonnode/ShareNode.h"
#include "commonnode/HMenu.h"
#define menuStartTag 1
MainLayer::MainLayer(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menus.plist", "menus.png");

}
MainLayer::~MainLayer(){

    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("loadinglayer.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("menus.plist");
}
MainLayer* MainLayer::create(gameStatus status){
    MainLayer* layer = new MainLayer();
    if (layer->init()) {
        layer->initOtherMenu(status);
        return layer;
    }
    
    return NULL;
}
void MainLayer::initOtherMenu(gameStatus status){
    if (status == Tag_GameStart) {
        m_logoLayer = GameMainLogoLayer::create();
        this->addChild(m_logoLayer,1);
        
    }else if (status == Tag_GameOver){
        m_gameOverLayer = GameOverLayer::create();
        this->addChild(m_gameOverLayer,1);
    }
}
bool MainLayer::init(){
    if (Layer::init()) {
        
        initBg();
        initMenu();
//        initHero();
//        initLogo();
        
//        acHero();
//        acLogo();
        
        return true;
    }
    return false;
}
void MainLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    LayerColor* layerCol = LayerColor::create(Color4B(169,169,169,125));
    this->addChild(layerCol);
    
}
//void MainLayer::initHero(){
//    Size size = Director::getInstance()->getWinSize();
//    
//    m_hero = Sprite::createWithSpriteFrameName("loading_hero.png");
////    m_hero ->setPosition(size.width/2, size.height+m_hero->getContentSize().height/2);
//    Node* startMenu = m_menu->getChildByTag(menuStartTag);
//    m_hero ->setPosition(size.width/2,startMenu->getPositionY()+ m_hero->getContentSize().height/2/0.8);
//        m_hero->setScale(0.7f);
//    addChild(m_hero);
//}
void MainLayer::initMenu(){
    Size size = Director::getInstance()->getWinSize();
 
    auto item1 = HMenu::create("main_rank.png", "main_rank1.png", CC_CALLBACK_1(MainLayer::menuRank, this) );
    item1->getNormalImage()->setAnchorPoint(Vec2(0.5f, 0.5f));
    item1->setPosition(Vec2(size.width/4+item1->getContentSize().width, size.height/4+item1->getContentSize().height/4));
    auto item2 = HMenu::create("main_setting.png", "main_setting1.png", CC_CALLBACK_1(MainLayer::menuSet, this) );
    item2->setPosition(Vec2(size.width/2, size.height/4+item2->getContentSize().height/4));
    auto item3 = HMenu::create("main_share.png", "main_share1.png", CC_CALLBACK_1(MainLayer::menuShare, this) );
    item3->setPosition(Vec2(size.width*3/4-item3->getContentSize().width, size.height/4+item3->getContentSize().height/4));
    auto item4 = HMenu::create("main_start.png", "main_start1.png", CC_CALLBACK_1(MainLayer::menuStart, this) );
    item4->setTag(menuStartTag);
    item4->setPosition(Vec2(size.width/2, size.height/2+item4->getContentSize().height/4));
    
    
    m_menu = Menu::create(item1, item2, item3,item4, nullptr);
    addChild(m_menu);
    m_menu->setAnchorPoint(Vec2(0, 0));
//    m_menu->setPosition(Vec2(0, -m_menu->getContentSize().height));
    m_menu->setPosition(Vec2(0,0));
    
}
//void MainLayer::acHero(){
//    Size winSize = Director::getInstance()->getWinSize();
//    MoveTo* moveTo = MoveTo::create(0.4, Point(m_hero->getPositionX(), m_hero->getContentSize().height/2));
//    Sequence* seq = Sequence::create(DelayTime::create(0.5),moveTo,CallFunc::create(CC_CALLBACK_0(MainLayer::acMenu, this)), NULL);
//    m_hero->runAction(seq);
//    
//    
//}
//void MainLayer::acLogo(){
//    Size winSize = Director::getInstance()->getWinSize();
//    MoveTo* moveTo = MoveTo::create(0.1, Point(m_logo->getPositionX(),winSize.height-m_logo->getContentSize().height*3/4));
//    Sequence* seq = Sequence::create(DelayTime::create(0.8), moveTo, NULL);
//    m_logo->runAction(seq);
//}
//void MainLayer::acMenu(){
//    Node* startMenu = m_menu->getChildByTag(menuStartTag);
//    MoveTo* moveTo = MoveTo::create(0.4, Point(m_hero->getPositionX(),startMenu->getPositionY()+ m_hero->getContentSize().height/2/0.7));
//    m_hero->runAction(moveTo);
//    
//    MoveTo* moveTo2 = MoveTo::create(0.4, Point(0,0));
//    m_menu->runAction(moveTo2);
//    
//    
//}
void MainLayer::menuStart(Ref* sender){
    log("开始");
}
void MainLayer::menuShare(cocos2d::Ref *sender){
    if (m_shareNode) {
        m_shareNode ->removeFromParentAndCleanup(true);
        m_shareNode = NULL;
    }else{
        m_shareNode = ShareNode::create();
        addChild(m_shareNode);
    }
}
void MainLayer::menuRank(cocos2d::Ref *sender){
}
void MainLayer::menuSet(cocos2d::Ref *sender){
    SettingNode* node = SettingNode::create();
    addChild(node);
}













