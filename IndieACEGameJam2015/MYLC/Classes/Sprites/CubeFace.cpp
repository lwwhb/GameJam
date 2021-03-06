//
//  CubeFace.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/11.
//
//

#include "CubeFace.h"
#include "OutlineEffect3D.h"
USING_NS_CC;

CubeFace* CubeFace::create(FaceType type)
{
    auto cubeFace = new (std::nothrow) CubeFace();
    if (cubeFace)
    {
        bool bRet = false;
        switch (type) {
            case FT_FRONT:
                bRet = cubeFace->initWithFile("1.obj");
                break;
            case FT_TOP:
                bRet = cubeFace->initWithFile("2.obj");
                break;
            case FT_RIGHT:
                bRet = cubeFace->initWithFile("3.obj");
                break;
            case FT_BACK:
                bRet = cubeFace->initWithFile("4.obj");
                break;
            case FT_LEFT:
                bRet = cubeFace->initWithFile("5.obj");
                break;
            case FT_DOWN:
                bRet = cubeFace->initWithFile("6.obj");
                break;
            default:
                break;
        }
        if(bRet)
        {
            int currentLevel = UserDefault::getInstance()->getIntegerForKey("CurrentLevel", 1);
            cubeFace->setTexture("IndexColor.png");
            cubeFace->setType(type);
            cubeFace->_contentSize = cubeFace->getBoundingBox().size;
            cubeFace->m_fRadius = cubeFace->_contentSize.width*0.5f;
        
            OutlineEffect3D* outline = OutlineEffect3D::create();
            switch (currentLevel) {
                case 1:
                    outline->setOutlineColor(Vec3(1.0f, 153.0f/255.0f, 0.0f));
                    break;
                case 2:
                    outline->setOutlineColor(Vec3(102.0f/255.0f, 1.0f, 1.0f));
                    break;
                case 3:
                    outline->setOutlineColor(Vec3(1.0f, 204.0f/255.0f, 0.0f));
                    break;
                case 4:
                    outline->setOutlineColor(Vec3(204.0f/255.0f, 204.0f/255.0f, 1.0f));
                    break;
                case 5:
                    outline->setOutlineColor(Vec3(1.0f, 1.0f, 204.0f/255.0f));
                    break;
                case 6:
                    outline->setOutlineColor(Vec3(1.0f, 204.0f/255.0f, 1.0f));
                    break;
                default:
                    break;
            }
            outline->setOutlineWidth(0.1f);
            cubeFace->addEffect(outline, 1);
        
            cubeFace->autorelease();
            return cubeFace;
        }
    }
    CC_SAFE_DELETE(cubeFace);
    return nullptr;
}
CubeFace::CubeFace()
{
}