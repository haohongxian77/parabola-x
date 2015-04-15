//
//  ShareNode.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#ifndef __GWPJUMP__ShareNode__
#define __GWPJUMP__ShareNode__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class ShareNode :public Node{
    ShareNode();
    ~ShareNode();
public:
    CREATE_FUNC(ShareNode);
private:
    bool init();
    void initMenu();
public:
    void shareQQ(Ref* obj);
    void shareWX(Ref* obj);
    void shareXL(Ref* obj);
    void shareFB(Ref* obj);
    
    
};

#endif /* defined(__GWPJUMP__ShareNode__) */
