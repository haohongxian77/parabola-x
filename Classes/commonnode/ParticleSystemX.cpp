//
//  ParticleSystemX.cpp
//  GwsJump
//
//  Created by 易水流年 on 5/26/15.
//
//

#include "ParticleSystemX.h"
#define acTag 101
ParticleSystemX::ParticleSystemX(){
}
ParticleSystemX::~ParticleSystemX(){
}
bool ParticleSystemX::init(){
    if (Node::init()) {
        showFristParticle();
        return true;
    }else{
        return false;
    }
}
void ParticleSystemX::showFristParticle(){
    auto s = Director::getInstance()->getWinSize();
    spFront = Sprite::createWithSpriteFrameName("new_top.png");
    spFront->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    spFront->setPosition(s.width/2,s.height/1.25);
    addChild(spFront);
    FadeOut * ac = FadeOut::create(2);
    ac->setTag(acTag);
    spFront->runAction(ac);
    
     emitter1 = ParticleSystemQuad::create("game_pa_highestscore.plist");
    emitter2 = ParticleSystemQuad::create("game_pa_highestscore.plist");
 
     emitter3 = ParticleSystemQuad::create("game_pa_highestscore.plist");
 
    
    
    
    emitter1->setPosition(Vec2( s.width/1.25f, s.height/1.25));
    emitter2->setPosition(Vec2( s.width/2, s.height/1.25));
    emitter3->setPosition(Vec2( s.width/4, s.height/1.25));
    
    auto batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    
    batch->addChild(emitter1, 0);
    batch->addChild(emitter2, 0);
    batch->addChild(emitter3, 0);
    
    addChild(batch, 10);

}
void ParticleSystemX::restartParticle(){
    emitter1->resetSystem();
    emitter2->resetSystem();
    emitter3->resetSystem();
    
    spFront->setOpacity(255);
    spFront->stopActionByTag(acTag);
    FadeOut * ac = FadeOut::create(2);
    ac->setTag(acTag);
    spFront->runAction(ac);
}
void ParticleSystemX::showSecParticle(){
}
void ParticleSystemX::showTRParticle(){
}