//
//  ShareNode.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#include "ShareNode.h"
#include "helper/GameMainHelper.h"
#include "commonnode/HMenu.h"
ShareNode::ShareNode(){
}
ShareNode::~ShareNode(){
}
bool ShareNode::init(){
    if (Node::init()) {
        initMenu();
        return true;
    }
    return false;
}
void ShareNode::initMenu(){
    Size size = Director::getInstance()->getWinSize();
    auto item1 = HMenu::create("share_qq.png", "share_qq1.png", CC_CALLBACK_1(ShareNode::shareQQ, this) );
    item1->setAnchorPoint(Vec2(0.5f, 0.5f));
    item1->setPosition(Vec2(size.width*3/4, size.height*3/8+item1->getContentSize().height*5/2));
    auto item2 = HMenu::create("share_wx.png", "share_wx1.png", CC_CALLBACK_1(ShareNode::shareWX, this) );
    item2->setAnchorPoint(Vec2(0.5f, 0.5f));
    item2->setPosition(Vec2(size.width*3/4, size.height*3/8+item2->getContentSize().height));
    auto item3 = HMenu::create("share_xl.png", "share_xl1.png", CC_CALLBACK_1(ShareNode::shareXL, this) );
    item3->setAnchorPoint(Vec2(0.5f, 0.5f));
    item3->setPosition(Vec2(size.width*3/4, size.height*3/8-item3->getContentSize().height/2));
    auto item4 = HMenu::create("share_fb.png", "share_fb1.png", CC_CALLBACK_1(ShareNode::shareFB, this) );
    item4->setAnchorPoint(Vec2(0.5f, 0.5f));
    item4->setPosition(Vec2(size.width*3/4, size.height*3/8-item4->getContentSize().height*2));
    
    
    Menu* m_menu = Menu::create(item1, item2, item3,item4, nullptr);
    addChild(m_menu);
    m_menu->setAnchorPoint(Vec2(0, 0));
    //    m_menu->setPosition(Vec2(0, -m_menu->getContentSize().height));
    m_menu->setPosition(Vec2(0,0));


}
void ShareNode::shareQQ(cocos2d::Ref *obj){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    GameMainHelper::getInstance()->share(Share_QQ);

#endif
     }
void ShareNode::shareWX(cocos2d::Ref *obj){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     GameMainHelper::getInstance()->share(Share_WX);
    
#endif
    
}
void ShareNode::shareXL(cocos2d::Ref *obj){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
   GameMainHelper::getInstance()->share(Share_SINA);
    
#endif
    
}
void ShareNode::shareFB(cocos2d::Ref *obj){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    GameMainHelper::getInstance()->share(Share_FB);
    
#endif
    
}
