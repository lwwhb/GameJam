//
//  Arrow.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__Arrow__
#define __MYLC__Arrow__

#include "EffectSprite3D.h"

class Arrow : public EffectSprite3D
{
public:
    typedef enum
    {
        AT_UP,
        AT_DOWN,
        AT_LEFT,
        AT_RIGHT,
        AT_UNKNOWN
    }
    ArrowType;
protected:
    Arrow();
public:
    static Arrow* create(ArrowType type);
    
    float getRadius() const { return m_fRadius; }
    ArrowType getType() const { return m_Type; }
    void setType(ArrowType type) { m_Type = type; }
    
    int getIndexX() const { return m_nIndexX; }
    void setIndexX(int indexX) { m_nIndexX = indexX; }
    int getIndexY() const { return m_nIndexY; }
    void setIndexY(int indexY) { m_nIndexY = indexY; }
protected:
    float           m_fRadius;
    ArrowType       m_Type;
    int         m_nIndexX;
    int         m_nIndexY;
};

#endif /* defined(__MYLC__Arrow__) */
