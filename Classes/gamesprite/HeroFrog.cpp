//
//  HeroFrog.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/21/15.
//
//

#include "HeroFrog.h"
#include "helper/GameMainHelper.h"
int animationCount[7] = {8,4,2,6,2,3,3};
                   //idel,起跳，上跳，下跳，落地，死亡撞柱子，死亡
std::string animaFrameName[7] = {"hero_static_%d.png","hero_jpstart_%d.png",
                            "hero_jpup_%d.png","hero_jpdown_%d.png",
                            "hero_drop_%d.png","hero_dead2_%d.png",
                            "hero_dead1_%d.png"};
std::string animaName[7] = {"frogStatic","frogTakeoff",
    "frogJumpUp","frogJumpDown",
    "frogFall","frogDead1",
    "frogDead2"};
#define HEROSTATICMUSIC_TIME 5
HeroFrog::HeroFrog():m_heroStatus(FrogNone),drawNode(NULL)
		,m_isLongJump(false),
		m_dStaticMusicTime(0){
}
HeroFrog::~HeroFrog(){
}
bool HeroFrog::init(){
    if (Sprite::init()) {
        this->initWithSpriteFrameName("hero_static_0.png");
        initAnimation();
        initData();
        return true;
    }
    return false;
    
}
void HeroFrog::initData(){
    Size size = Director::getInstance()->getWinSize();
    downSpeed = size.height/10;
    drawNode = DrawNode::create();
    addChild(drawNode,2);
}
void HeroFrog::initAnimation(){
    for (int i=0; i<7; i++) {
        auto animationStatic = Animation::create();
        for( int j=1;j<animationCount[i];j++)
        {
            char szName[100] = {0};
            sprintf(szName, animaFrameName[i].c_str(), j);
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
            animationStatic->addSpriteFrame(frame);
        }
        // should last 2.8 seconds. And there are 14 frames.
        animationStatic->setDelayPerUnit(0.2f);
        animationStatic->setRestoreOriginalFrame(false);
        AnimationCache::getInstance()->addAnimation(animationStatic, animaName[i]);
    }
    
    setHeroStatus(frogStatic);
 
}
void HeroFrog::setCurPosition(Point pos){
    setPosition(pos);
    if (pos.x == downPoint.x && pos.y == downPoint.y) {
        setHeroStatus(frogJumpDown);
    }
}
void HeroFrog::setHeroMoveOver(){
    switch (pathoverStatus) {
        case frogFall:
            setHeroStatus(frogFall);
            GameMainHelper::getInstance()->jumpOver();
            break;
        case frogDead1:
            setHeroStatus(frogDead1);
            GameMainHelper::getInstance()->gameOver();
            break;
        case frogDead2:
            setHeroStatus(frogDead2);
            GameMainHelper::getInstance()->gameOver();
            break;
            
        default:
            break;
    }
}
bool HeroFrog::setHeroFall(){
    if (pathoverStatus == frogFall){
        setHeroStatus(frogFall);
        GameMainHelper::getInstance()->jumpOver();
        return true;
    }
    return false;
}
void HeroFrog::updateMusic(float dt){
	if(m_heroStatus != frogStatic)
		return;
	m_dStaticMusicTime-=dt;
	if(m_dStaticMusicTime <=0){
     GameMainHelper::getInstance()->playSound(HEROSTATIC);
     m_dStaticMusicTime = HEROSTATICMUSIC_TIME;
	}

}
void HeroFrog::setIsLongJump(bool longJump){
	m_isLongJump = longJump;
}
void HeroFrog::setHeroStatus(FrogStatus heroStatus){
    if (m_heroStatus == heroStatus) {
        return;
    }
    m_heroStatus = heroStatus;
   
    Animation* ani;
    Animate* ac;
    this->stopAllActions();
    ani = AnimationCache::getInstance()->getAnimation(animaName[heroStatus].c_str());
    
    
    Sequence* seq;
    float y;
    float dis;
    float time;
    SpriteFrame* deadFrame ;
    Spawn* sp;
    
    MoveTo* mvTo;
    Point targetPoint;
    
    CCLOG("---------设置hero状态-----------");
    switch (heroStatus) {
        case frogStatic:
            GameMainHelper::getInstance()->playSound(JUMPOVER);
            ac= Animate::create(ani) ;
            runAction(RepeatForever::create(ac));
            
            break;
        case frogTakeoff:
            ac= Animate::create(ani) ;
            ani->setDelayPerUnit(0.5);
            runAction(ac);
            break;
        case frogJumpUp:
        	if(m_isLongJump)
               GameMainHelper::getInstance()->playSound(JUMPSTART_1);
        	else
        		GameMainHelper::getInstance()->playSound(JUMPSTART_0);
            ani->setDelayPerUnit(2); //--------待计算
            ac= Animate::create(ani);
            runAction(ac);
            
            break;
        case frogJumpDown:
            ani->setDelayPerUnit(downAnimSpeed); //--------待计算
            ac= Animate::create(ani);
            runAction(ac);
            break;
        case frogFall:
            ani->setDelayPerUnit(downAnimSpeed);
            ac= Animate::create(ani);
            targetPoint = GameMainHelper::getInstance()->getHeroPostPoint();
            time =ani->getDelayPerUnit();
            mvTo = MoveTo::create(downAnimSpeed,targetPoint);
            sp = Spawn::create(ac,mvTo, NULL);
            seq = Sequence::create(sp,CCCallFunc::create(CC_CALLBACK_0(HeroFrog::setHeroStatic, this)) , NULL);
            runAction(seq);
            break;
        case frogDead1:
            GameMainHelper::getInstance()->playSound(HEROOVER);
            deadFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_dead2.png");
            this->setDisplayFrame(deadFrame);
             ac= Animate::create(ani);
            y = MIN(GameMainHelper::getInstance()->getEarthH(),getPositionY());
            dis = getPositionY()-y;
            time = dis/downSpeed;
            targetPoint = Point(getPositionX(),y);
            mvTo = MoveTo::create(time,targetPoint);
            sp = Spawn::create(Repeat::create(ac,10),mvTo, NULL);
            seq = Sequence::create(DelayTime::create(0.5), sp,NULL);
     
            runAction(seq);
            break;
        case frogDead2:
            GameMainHelper::getInstance()->playSound(HEROOVER);
            ac= Animate::create(ani) ;
            runAction(RepeatForever::create(ac));
            break;
            
        default:
            ac= Animate::create(ani);
            runAction(RepeatForever::create(ac));
            break;
    }
}
void HeroFrog::setHeroStatic(){
    setHeroStatus(frogStatic);
}
FrogStatus HeroFrog::getHeroStatus(){
    return m_heroStatus;
}
void HeroFrog::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
    Sprite::draw(renderer,transform,flags);
    if(!drawNode)
        return;
    drawNode->clear();
}
Rect HeroFrog::getFootRect(Point curPoint){
    Size heroSize = this->getContentSize();
    
    return Rect(curPoint.x-heroSize.width/4, curPoint.y, heroSize.width/2, heroSize.height/8);
}
Rect HeroFrog::getBodyRect(Point curPoint){
    Size heroSize = this->getContentSize();
    return Rect(curPoint.x-heroSize.width/4, curPoint.y, heroSize.width*3/8, heroSize.height);
}
void HeroFrog::setHeroMoveParam(Point downPoint, float downAniSpeed, FrogStatus status){
    this->downPoint = downPoint;
    this->downAnimSpeed = downAniSpeed;
    this->pathoverStatus = status;
}
FrogStatus HeroFrog::getPathOverStatus(){
    return pathoverStatus;}
