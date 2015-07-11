//
//  GroundCell.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__GroundCell__
#define __MYLC__GroundCell__

#include "EffectSprite3D.h"

class GroundCell : public EffectSprite3D
{
public:
    typedef enum
    {
        CT_HIDE = 0,    ///不显示 RED
        CT_NOT,         ///没翻转 ORANGE
        CT_OK,          ///已翻转 GREEN
        CT_UNKNOWN
    }
    CellType;
protected:
    GroundCell();
public:
    static GroundCell* create(const std::string& path);
    
    float getRadius() const { return m_fRadius; }
    CellType getType() const { return m_Type; }
    void setType(CellType type) { m_Type = type; }
    int getIndexX() const { return m_nIndexX; }
    void setIndexX(int indexX) { m_nIndexX = indexX; }
    int getIndexY() const { return m_nIndexY; }
    void setIndexY(int indexY) { m_nIndexY = indexY; }
protected:
    float       m_fRadius;
    CellType    m_Type;
    int         m_nIndexX;
    int         m_nIndexY;
};

#endif /* defined(__MYLC__GroundCell__) */
