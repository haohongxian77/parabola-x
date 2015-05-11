//
//  HeroFrog.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/21/15.
//
//

#include "HeroFrog.h"
#include "helper/GameMainHelper.h"
int animationCount[7] = {8,4,4,4,2,3,3};
                   //idel,起跳，上跳，下跳，落地，死亡撞柱子，死亡
std::string animaFrameName[7] = {"hero_static_%d.png","hero_jpstart_%d.png",
                            "hero_jpup_%d.png","hero_jpdown_%d.png",
                            "hero_drop_%d.png","hero_dead2_%d.png",
                            "hero_dead1_%d.png"};
std::string animaName[7] = {"frogStatic","frogTakeoff",
    "frogJumpUp","frogJumpDown",
    "frogFall","frogDead1",
    "frogDead2"};
HeroFrog::HeroFrog():m_heroStatus(frogStatic),drawNode(NULL){
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
void HeroFrog::setPos(Point pos){

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
    CCLOG("---------设置hero状态-----------");
    switch (heroStatus) {
        case frogStatic:
            ac= Animate::create(ani) ;
            runAction(RepeatForever::create(ac));
            
            break;
        case frogTakeoff:
            ac= Animate::create(ani) ;
            runAction(ac);
            break;
        case frogJumpUp:
            ani->setDelayPerUnit(2); //--------待计算
            ac= Animate::create(ani);
            runAction(ac);
            
            break;
        case frogJumpDown:
            ani->setDelayPerUnit(2); //--------待计算
            ac= Animate::create(ani);
            runAction(ac);
            break;
        case frogFall:
            ac= Animate::create(ani);
            seq = Sequence::create(ac,CCCallFunc::create(CC_CALLBACK_0(HeroFrog::setHeroStatic, this)) , NULL);
            runAction(seq);
            break;
        case frogDead1:
            deadFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_dead2.png");
            this->setDisplayFrame(deadFrame);
             ac= Animate::create(ani);
            y = GameMainHelper::getInstance()->getEarthH();
            dis = getPositionY()-y;
            time = dis/downSpeed;
            mvTo = MoveTo::create(time,Point(getPositionX(),y));
            sp = Spawn::create(RepeatForever::create(ac),mvTo, NULL);
            seq = Sequence::create(DelayTime::create(0.5), mvTo,NULL);
     
            runAction(seq);
            break;
        case frogDead2:
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
     Size heroSize = this->getContentSize();
    drawNode->drawRect(Vec2(heroSize.width/4,0),Vec2(heroSize.width*3/4, heroSize.height/8), Color4F(186, 186, 186, 1));
    drawNode->drawRect(Vec2(heroSize.width/4,0),Vec2(heroSize.width*7/8, heroSize.height), Color4F(255, 255, 0, 1));
}
Rect HeroFrog::getFootRect(){
    Size heroSize = this->getContentSize();
    
    return Rect(getPositionX()-heroSize.width/4, getPositionY(), heroSize.width/2, heroSize.height/8);
}
Rect HeroFrog::getBodyRect(){
    Size heroSize = this->getContentSize();
    return Rect(getPositionX()-heroSize.width/4, getPositionY(), heroSize.width*5/8, heroSize.height);
}

