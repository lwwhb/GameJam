//
//  Gift.h
//  MYLC
//
//  Created by wang haibo on 15/7/11.
//
//

#ifndef __MYLC__Gift__
#define __MYLC__Gift__

#include "EffectSprite3D.h"
class Gift : public EffectSprite3D
{
public:
    typedef enum
    {
        GT_SUN = 1,
        GT_CLOUD,
        GT_TREE,
        GT_FLOWER,
        GT_HOUSE,
        GT_HEART
    }
    GiftType;
protected:
    Gift();
public:
    static Gift* create(GiftType type);
    
    float getRadius() const { return m_fRadius; }
    GiftType getType() const { return m_Type; }
    void setType(GiftType type) { m_Type = type; }
protected:
    float           m_fRadius;
    GiftType        m_Type;
};

#endif /* defined(__MYLC__Gift__) */
