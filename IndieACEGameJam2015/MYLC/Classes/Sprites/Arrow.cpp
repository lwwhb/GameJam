//
//  Arrow.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "Arrow.h"
#include "OutlineEffect3D.h"
USING_NS_CC;

Arrow* Arrow::create(ArrowType type)
{
    auto arrow = new (std::nothrow) Arrow();
    if (arrow && arrow->initWithFile("arrow.obj"))
    {
        arrow->setTexture("IndexColor.png");
        arrow->setType(type);
        arrow->_contentSize = arrow->getBoundingBox().size;
        arrow->m_fRadius = arrow->_contentSize.width*0.5f;
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.5f, 0.5f, 0.5f));
        outline->setOutlineWidth(0.03f);
        arrow->addEffect(outline, 1);
        
        arrow->autorelease();
        return arrow;
    }
    CC_SAFE_DELETE(arrow);
    return nullptr;
}
Arrow::Arrow()
{
}