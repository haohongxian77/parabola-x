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
#include "helper/CommomData.h"
#include "helper/GameMainHelper.h"
#include "helper/HPlatformHelper.h"
#define menuStartTag 1
#define layerEndAcTag  1001
MainLayer::MainLayer(){
   

}
MainLayer::~MainLayer(){

}
MainLayer* MainLayer::create(gameStatus status){
    MainLayer* layer = new MainLayer();
    if (layer->init()) {
        layer->initOtherMenu(status);
        return layer;
    }
    
    return NULL;
}
bool MainLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
    return  true;
}
void MainLayer::initOtherMenu(gameStatus status){
    if (status == Tag_GameStart||status == Tag_None) {
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
        return true;
    }
    return false;
}
void MainLayer::onEnter(){
    Layer::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority  (listener,this );
    
    Size winSize = Director::getInstance()->getWinSize();
    this->setPositionY(winSize.height);
    MoveTo* moveTo = MoveTo::create(0.5f,
                                    Point(
                                          this->getPositionX(),
                                          this->getPositionY() -winSize.height-70));
    MoveTo* moveTo2 = MoveTo::create(0.2f,
                                    Point(
                                          this->getPositionX(),
                                          0));
    EaseSineIn* easeBack = EaseSineIn::create(moveTo);
    Sequence* seq = Sequence::create(easeBack,moveTo2, NULL);
    this->runAction(seq);
}
void MainLayer::onExit(){
    
}

void MainLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
//    LayerColor* layerCol = LayerColor::create(Color4B(0,0,0,125));
//    layerCol->setContentSize(Size(size.width,size.height+70));
//    layerCol->setTag(101);
//    this->addChild(layerCol);
    
}
void MainLayer::initMenu(){
    Size size = Director::getInstance()->getWinSize();
 
    auto item1 = HMenu::create("main_rank.png", "main_rank1.png", CC_CALLBACK_1(MainLayer::menuRank, this) );
    item1->getNormalImage()->setAnchorPoint(Vec2(0.5f, 0.5f));
    item1->setPosition(Vec2(size.width/4+item1->getContentSize().width, size.height/5+item1->getContentSize().height/4));
    auto item2 = HMenu::create("main_setting.png", "main_setting1.png", CC_CALLBACK_1(MainLayer::menuSet, this) );
    item2->setPosition(Vec2(size.width/2, size.height/5+item2->getContentSize().height/4));
    auto item3 = HMenu::create("main_share.png", "main_share1.png", CC_CALLBACK_1(MainLayer::menuShare, this) );
    item3->setPosition(Vec2(size.width*3/4-item3->getContentSize().width, size.height/5+item3->getContentSize().height/4));
    auto item4 = HMenu::create("main_start.png", "main_start1.png", CC_CALLBACK_1(MainLayer::menuStart, this) );
    if (GameMainHelper::getInstance()->getGameStaus() == Tag_GameOver) {
        item4 = HMenu::create("main_restart.png", "main_restart1.png", CC_CALLBACK_1(MainLayer::menuStart, this) );
        item4->setPosition(Vec2(size.width/2, size.height/2));
    }else{
        item4 = HMenu::create("main_start.png", "main_start1.png", CC_CALLBACK_1(MainLayer::menuStart, this) );
        item4->setPosition(Vec2(size.width/2, size.height/2+item4->getContentSize().height/4));
    }
    item4->setTag(menuStartTag);
    
    
    
    m_menu = Menu::create(item1, item2, item3,item4, nullptr);
    addChild(m_menu);
    m_menu->setAnchorPoint(Vec2(0, 0));
//    m_menu->setPosition(Vec2(0, -m_menu->getContentSize().height));
    m_menu->setPosition(Vec2(0,0));
    
}

void MainLayer::menuStart(Ref* sender){
    if (isClickStart) {
        return;
    }
    HMenu* menu = (HMenu*) sender;
    menu->setEnabled(false);
    isClickStart = true;
    GameMainHelper::getInstance()->playSound(BTNCLICK);
    auto action1 = FadeIn::create(1.0f);
    Sequence* seq = Sequence::create(action1,CallFunc::create(CC_CALLBACK_0(MainLayer::callback, this)), NULL);
    seq->setTag(layerEndAcTag);
    this->runAction(seq);
}
void MainLayer::removeThisCallBack(){
    
    this->removeFromParentAndCleanup(true);
}
void MainLayer::update(float dt){
    Size winSize = Director::getInstance()->getWinSize();
    if (this->getPositionY()>winSize.height/3) {
        _eventDispatcher->removeEventListenersForTarget(this);
        unscheduleUpdate();
    }
}
void MainLayer::callback(){
    
    GameMainHelper::getInstance()->startGame();
    this->stopAllActions();
    
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo* moveTo2 = MoveTo::create(0.2f,
                                     Point(
                                           this->getPositionX(),
                                           -70));
    MoveTo* moveTo = MoveTo::create(0.4f,
                                    Point(
                                          this->getPositionX(),
                                          winSize.height*7/8));
    EaseSineOut* easeBack = EaseSineOut::create(moveTo);
    
    Sequence* seq = Sequence::create(moveTo2,easeBack,DelayTime::create(0.01f),CallFunc::create(CC_CALLBACK_0(MainLayer::removeThisCallBack, this)), NULL);
    this->runAction(seq);
    scheduleUpdate();

    
}
void MainLayer::menuShare(cocos2d::Ref *sender){
    GameMainHelper::getInstance()->playSound(BTNCLICK);
    if (!this->getChildByTag(101) ) {
        m_shareNode = ShareNode::create();
        m_shareNode->setTag(101);
        addChild(m_shareNode);
    }else{
        this->removeChildByTag(101);
    }
    
}
void MainLayer::menuRank(cocos2d::Ref *sender){

    GameMainHelper::getInstance()->playSound(BTNCLICK);
    if(GameMainHelper::getInstance()->getGoogleServer())
	   HPlatformHelper::getInstance()->showRank();
    else{
    	HPlatformHelper::getInstance()->showToast("请在设置中打开排行榜！");
    }
}
void MainLayer::menuSet(cocos2d::Ref *sender){
    GameMainHelper::getInstance()->playSound(BTNCLICK);
    SettingNode* node = SettingNode::create();
    this->getParent()->addChild(node);
    this->setVisible(false);
}













