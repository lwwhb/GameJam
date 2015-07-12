//
//  Boy.cpp
//  MYLC
//
//  Created by 李 旭 on 15/7/11.
//
//

#include "Boy.h"
#include "OutlineEffect3D.h"

USING_NS_CC;

Boy* Boy::create(int level)
{
    auto boy = new(std::nothrow) Boy();
    bool bRet = false;
    switch (level) {
        case 1:
             bRet = boy->initWithFile("bboy_1.obj");
            break;
        case 2:
            bRet = boy->initWithFile("bboy_2.obj");
            break;
        case 3:
            bRet = boy->initWithFile("bboy_3.obj");
            break;
        case 4:
            bRet = boy->initWithFile("bboy_4.obj");
            break;
            
        default:
            bRet = boy->initWithFile("bboy_nosmile.obj");
            break;
    }
    
    if (bRet) {
        boy->setTexture("IndexColor.png");
//        OutlineEffect3D *outline = OutlineEffect3D::create();
//        outline->setOutlineColor(Vec3(1.0f,1.0f,1.0f));
//        outline->setOutlineWidth(0.03f);
//        boy->addEffect(outline, 1);
        boy->autorelease();
        return boy;
    }
    CC_SAFE_DELETE(boy);
    return nullptr;
}

Boy::Boy()
{
    
}