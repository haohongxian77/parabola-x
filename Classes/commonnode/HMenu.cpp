//
//  HMenu.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#include "HMenu.h"
const unsigned int    kNormalTag = 0x1;
const unsigned int    kSelectedTag = 0x2;
const unsigned int    kDisableTag = 0x3;
HMenu* HMenu::create()
{
    HMenu *ret = new (std::nothrow) HMenu();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool HMenu::init(void)
{
    return initWithNormalImage("", "", "", (const ccMenuCallback&)nullptr);
}

HMenu * HMenu::create(const std::string& normalImage, const std::string& selectedImage)
{
    return HMenu::create(normalImage, selectedImage, "", (const ccMenuCallback&)nullptr);
}

// FIXME: deprecated
HMenu * HMenu::create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector)
{
    return HMenu::create(normalImage, selectedImage, "", target, selector);
}

HMenu * HMenu::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
{
    return HMenu::create(normalImage, selectedImage, "", callback);
}

// FIXME: deprecated
HMenu * HMenu::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector)
{
    HMenu *ret = new (std::nothrow) HMenu();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, target, selector))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

HMenu * HMenu::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
    HMenu *ret = new (std::nothrow) HMenu();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

HMenu * HMenu::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage)
{
    HMenu *ret = new (std::nothrow) HMenu();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, (const ccMenuCallback&)nullptr))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// FIXME:: deprecated
bool HMenu::initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector)
{
    _target = target;
    CC_SAFE_RETAIN(_target);
    return initWithNormalImage(normalImage, selectedImage, disabledImage, std::bind(selector,target, std::placeholders::_1) );
}
bool HMenu::initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
    Node *normalSprite = nullptr;
    Node *selectedSprite = nullptr;
    Node *disabledSprite = nullptr;
    
    if (normalImage.size() >0)
    {
        normalSprite = Sprite::createWithSpriteFrameName(normalImage);
    }
    
    if (selectedImage.size() >0)
    {
        selectedSprite = Sprite::createWithSpriteFrameName(selectedImage);
    }
    
    if(disabledImage.size() >0)
    {
        disabledSprite = Sprite::createWithSpriteFrameName(disabledImage);
    }
    return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
}
bool HMenu::initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback)
{
    MenuItem::initWithCallback(callback);
    setNormalImage(normalSprite);
    setSelectedImage(selectedSprite);
    setDisabledImage(disabledSprite);
    
    if(_normalImage)
    {
        this->setContentSize(_normalImage->getContentSize());
    }
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    return true;
}


//
// Setter of sprite frames
//
void HMenu::setNormalSpriteFrame(SpriteFrame * frame)
{
    setNormalImage(Sprite::createWithSpriteFrame(frame));
}

void HMenu::setSelectedSpriteFrame(SpriteFrame * frame)
{
    setSelectedImage(Sprite::createWithSpriteFrame(frame));
}

void HMenu::setDisabledSpriteFrame(SpriteFrame * frame)
{
    setDisabledImage(Sprite::createWithSpriteFrame(frame));
}
void HMenu::setNormalImage(Node* image)
{
    if (image != _normalImage)
    {
        if (image)
        {
            addChild(image, 0, kNormalTag);
            image->setAnchorPoint(Vec2(0.5, 0.5));
            image->setPosition(image->getContentSize().width/2,image->getContentSize().height/2);
        }
        
        if (_normalImage)
        {
            removeChild(_normalImage, true);
        }
        
        _normalImage = image;
        this->setContentSize(_normalImage->getContentSize());
        this->updateImagesVisibility();
    }
}

void HMenu::setSelectedImage(Node* image)
{
    if (image != _normalImage)
    {
        if (image)
        {
            addChild(image, 0, kSelectedTag);
            image->setAnchorPoint(Vec2(0.5, 0.5));
            image->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
        }
        
        if (_selectedImage)
        {
            removeChild(_selectedImage, true);
        }
        
        _selectedImage = image;
        this->updateImagesVisibility();
    }
}

void HMenu::setDisabledImage(Node* image)
{
    if (image != _normalImage)
    {
        if (image)
        {
            addChild(image, 0, kDisableTag);
            image->setAnchorPoint(Vec2(0.5, 0.5));
        }
        
        if (_disabledImage)
        {
            removeChild(_disabledImage, true);
        }
        
        _disabledImage = image;
        this->updateImagesVisibility();
    }
}


