#include "GameMainScene.h"
#include "helper/GameMainHelper.h"
#include "helper/HPlatformHelper.h"
USING_NS_CC;
GameMainScene::GameMainScene():
m_gamemainLayer(NULL),
m_mianMenuLayer(NULL),
m_bgBfLayer(NULL),
m_bgLayer(NULL)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menus.plist", "menus.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_item.plist", "game_item.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero_anim.plist", "hero_anim.png");
    
}
GameMainScene::~GameMainScene(){
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("loadinglayer.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("menus.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("game_item.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("hero_anim.plist");
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
    addChild(m_gamemainLayer,GAMEMAINLAYER);
    
}
void GameMainScene::initGameAlertLayer(gameStatus gameS){
    m_mianMenuLayer = MainLayer::create(gameS);
    this->addChild(m_mianMenuLayer,GAMEMENULAYER);
   
}
void GameMainScene::initGameBgLayer(){
    m_bgLayer = GameBgLayer::create();
    this->addChild(m_bgLayer,GAMEBGLAYER);
}
void GameMainScene::initGameBgBFLayer(){
    m_bgBfLayer = GameBgBeforeLayer::create();
    addChild(m_bgBfLayer,GAMEBGBEFORELAYER);
}
void GameMainScene::initGameUIlayer(){
    m_gameUILayer = GameUIlayer::create();
    addChild(m_gameUILayer,GAMEUILAYER);
}
GameMainScene* GameMainScene::create(){
    GameMainScene* sc = new GameMainScene();
    if (sc->init()) {
        sc->initHelper();
        sc->initGameBgBFLayer();
        sc->initGameBgLayer();
        sc->initMainLayer();
        sc->initGameAlertLayer(Tag_None);
        sc->initGameUIlayer();
        return sc;
    }
    return NULL;
}
void GameMainScene::initHelper(){
    m_helper = GameMainHelper::getInstance();
    m_helper->atachScene(this);
}
void GameMainScene::startGame(){
    if(m_mianMenuLayer){
        m_mianMenuLayer ->removeFromParentAndCleanup(true);
        m_mianMenuLayer =NULL;
        scheduleUpdate();
    }
    m_bgLayer->changeSprite();
    m_bgBfLayer->changeSprite();
}
void GameMainScene::gameOver(){
    unscheduleUpdate();
    Sequence* seq = Sequence::create(DelayTime::create(2),CallFunc::create(CC_CALLBACK_0(GameMainScene::showAlertView, this)), NULL);
    runAction(seq);
    
}
void GameMainScene::showAlertView(){
    initGameAlertLayer(Tag_GameOver);
}
void GameMainScene::update(float delta){
    float posXBefore = m_gamemainLayer->getPositionX();
    m_gamemainLayer->update(delta);
    float posXAfter = m_gamemainLayer->getPositionX();
    m_bgLayer->update(delta, posXAfter-posXBefore);
    m_bgBfLayer->update(delta, posXAfter-posXBefore);
    m_helper->updateHelper(delta);
    
}
void GameMainScene::changeScore(){
    m_gameUILayer->changeScore(m_helper->getCurScore());
}

void GameMainScene::onEnter(){
    Scene::onEnter();
}
void GameMainScene::onExit(){
    Scene::onExit();
   
}
void GameMainScene::gotoShare(int type){
	cutOff(type);
//    Sequence* seq = Sequence::create(DelayTime::create(0.2f), CallFuncN::create(CC_CALLBACK_1(GameMainScene::share, this,type)),NULL);
//    this->runAction(seq);
}
//void GameMainScene::share(cocos2d::Node *node, int type){
//	CCLOG("去分享---------------%d",GameMainHelper::getInstance()->getGameStaus());
//    if(GameMainHelper::getInstance()->getGameStaus() == Tag_None){
//        HPlatformHelper::getInstance()->share(m_shareType,-1);
//    }else{
//        HPlatformHelper::getInstance()->share(m_shareType,1);
//    }
//
//}
std::string GameMainScene::cutOff(int shareType){
	CCLOG("GameMainHelper========================%d",shareType);
	m_shareType = shareType;

    Size visibleSize = Director::getInstance()->getWinSize();
    //定义一个屏幕大小的渲染纹理
    RenderTexture* renderTexture = RenderTexture::create(visibleSize.width * .5, visibleSize.height * .5, Texture2D::PixelFormat::RGBA8888);
    Point ancPos = this->getAnchorPoint();
    //渲染纹理开始捕捉
    renderTexture->begin();
    // 缩小屏幕截屏区域
    this->setAnchorPoint(cocos2d::Point(0, 0));
    this->setScale(0.5);
    //绘制当前场景
    this->visit();
    //结束
    renderTexture->end();
    //保存png
    __String* fileName_ = __String::create("share_imaged.jpg");
    std::string fullPath = FileUtils::getInstance()->getWritablePath()+fileName_->getCString();
    auto callback = [&](RenderTexture* rt, const std::string& path)
    {
        this->setScale(1);
        this->setAnchorPoint(ancPos);
        if(GameMainHelper::getInstance()->getGameStaus() == Tag_None){
        	        HPlatformHelper::getInstance()->share(m_shareType,-1,path);
         }else{
        	        HPlatformHelper::getInstance()->share(m_shareType,1,path);
        }

//        HPlatformHelper::getInstance()->share(m_shareType,path);
    };
    renderTexture->saveToFile(fileName_->getCString(), Image::Format::JPG, true, callback);
    return fullPath;
}












