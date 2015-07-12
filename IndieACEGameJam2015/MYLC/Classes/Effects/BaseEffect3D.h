//
//  BaseEffect3D.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __Geometry_Wars__BaseEffect3D__
#define __Geometry_Wars__BaseEffect3D__

#include "cocos2d.h"

class EffectSprite3D;
class BaseEffect3D : public cocos2d::Ref
{
public:
    cocos2d::GLProgramState* getGLProgramState() const { return m_pGLprogramstate; }
protected:
    bool initGLProgramState(const std::string& vertFilename, const std::string& fragFilename);
    BaseEffect3D();
    virtual ~BaseEffect3D();
public:
    virtual void drawWithSprite3D(EffectSprite3D* sprite, const cocos2d::Mat4 &transform) = 0;
protected:
    cocos2d::GLProgramState*    m_pGLprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string     m_strVertSource;
    std::string     m_strFragSource;
    cocos2d::EventListenerCustom* m_pBackgroundListener;
#endif
};

#endif /* defined(__Geometry_Wars__BaseEffect3D__) */
