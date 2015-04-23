#include "GameMainScene.h"
#include "helper/GameMainHelper.h"
#include "helper/HPlatformHelper.h"
USING_NS_CC;

GameMainScene::GameMainScene():
m_gamemainLayer(NULL),
m_mianMenuLayer(NULL)
{
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
    addChild(m_gamemainLayer,0);
    
}
void GameMainScene::initGameAlertLayer(gameStatus gameS){
    m_mianMenuLayer = MainLayer::create(gameS);
    this->addChild(m_mianMenuLayer,1);
   
}
GameMainScene* GameMainScene::createWithTag(gameStatus gameS){
    GameMainScene* sc = new GameMainScene();
    if (sc->init()) {
        GameMainHelper::getInstance()->atachScene(sc);
        sc->initMainLayer();
        sc->initGameAlertLayer(gameS);
        return sc;
    }
    return NULL;
}
void GameMainScene::startGame(){
    if(m_mianMenuLayer){
        m_mianMenuLayer ->removeFromParentAndCleanup(true);
        m_mianMenuLayer =NULL;
    }
}
void GameMainScene::gameOver(){
}
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
//        ssize_t pSize_ = 0;
//        unsigned char* data_ = FileUtils::getInstance()->getFileData(path.c_str(), "rb", &pSize_);
        CCLOG("GameMainHelper========================%s",m_shareType);
        HPlatformHelper::getInstance()->share(m_shareType,path);

    };
    renderTexture->saveToFile(fileName_->getCString(), Image::Format::JPG, true, callback);
    
    
    // 恢复屏幕尺寸
    
    return fullPath;
}













