//
//  HMenu.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#ifndef __GWPJUMP__HMenu__
#define __GWPJUMP__HMenu__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class CC_DLL HMenu : public MenuItemSprite
{
public:
    /** Creates an MenuItemImage. */
    static HMenu* create();
    /** creates a menu item with a normal and selected image*/
    static HMenu* create(const std::string& normalImage, const std::string& selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static HMenu* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static HMenu* create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal and selected image with a callable object */
    static HMenu* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);
    
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static HMenu* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with a callable object */
    static HMenu* create(const std::string&normalImage, const std::string&selectedImage, const std::string&disabledImage, const ccMenuCallback& callback);
    bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
    
    void setNormalSpriteFrame(SpriteFrame* frame);
  
    void setSelectedSpriteFrame(SpriteFrame* frame);
 
    void setDisabledSpriteFrame(SpriteFrame* frame);
    void setNormalImage(Node* image);
    void setSelectedImage(Node* image);
    void setDisabledImage(Node* image);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    HMenu(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~HMenu(){}
    
    bool init();
    
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    /** initializes a menu item with a normal, selected  and disabled image with a callable object */
    bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(HMenu);
};

#endif /* defined(__GWPJUMP__HMenu__) */
