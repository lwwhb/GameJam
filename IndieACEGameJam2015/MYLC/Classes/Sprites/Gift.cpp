//
//  Gift.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/11.
//
//

#include "Gift.h"
#include "OutlineEffect3D.h"
USING_NS_CC;
Gift* Gift::create(GiftType type)
{
    auto gift = new (std::nothrow) Gift();
    if (gift)
    {
        bool bRet = false;
        switch (type) {
            case GT_SUN:
                bRet = gift->initWithFile("sun.obj");
                break;
            case GT_CLOUD:
                bRet = gift->initWithFile("cloud.obj");
                break;
            case GT_TREE:
                bRet = gift->initWithFile("tree.obj");
                break;
            case GT_FLOWER:
                bRet = gift->initWithFile("flower.obj");
                break;
            case GT_HOUSE:
                bRet = gift->initWithFile("house.obj");
                break;
            case GT_HEART:
                bRet = gift->initWithFile("heart.obj");
                break;
            default:
                break;
        }
        if(bRet)
        {
            gift->setTexture("IndexColor.png");
            gift->setType(type);
            gift->_contentSize = gift->getBoundingBox().size;
            gift->m_fRadius = gift->_contentSize.width*0.5f;
            
            OutlineEffect3D* outline = OutlineEffect3D::create();
            outline->setOutlineColor(Vec3(1.0f, 1.0f, 1.0f));
            outline->setOutlineWidth(0.05f);
            gift->addEffect(outline, 1);
            
            gift->autorelease();
            return gift;
        }
    }
    CC_SAFE_DELETE(gift);
    return nullptr;
}
Gift::Gift()
{
}