//
//  CubeFace.h
//  MYLC
//
//  Created by wang haibo on 15/7/11.
//
//

#ifndef __MYLC__CubeFace__
#define __MYLC__CubeFace__

#include "EffectSprite3D.h"

class CubeFace : public EffectSprite3D
{
public:
    typedef enum
    {
        FT_FRONT = 1,
        FT_TOP,
        FT_RIGHT,
        FT_BACK,
        FT_LEFT,
        FT_DOWN
    }
    FaceType;
protected:
    CubeFace();
public:
    static CubeFace* create(FaceType type);
    
    float getRadius() const { return m_fRadius; }
    FaceType getType() const { return m_Type; }
    void setType(FaceType type) { m_Type = type; }
protected:
    float           m_fRadius;
    FaceType       m_Type;
};

#endif /* defined(__MYLC__CubeFace__) */
