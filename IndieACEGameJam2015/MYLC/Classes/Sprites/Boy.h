//
//  Boy.h
//  MYLC
//
//  Created by 李 旭 on 15/7/11.
//
//

#ifndef __MYLC__Boy__
#define __MYLC__Boy__

#include <stdio.h>
#include "EffectSprite3D.h"

class Boy : public EffectSprite3D
{

protected:
    Boy();
public:
    static Boy* create(int level);
    
};

#endif /* defined(__MYLC__Boy__) */
