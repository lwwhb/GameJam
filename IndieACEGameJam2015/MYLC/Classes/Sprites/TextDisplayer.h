//
//  TextDisplayer.h
//  MYLC
//
//  Created by 李 旭 on 15/7/11.
//
//

#ifndef __MYLC__TextDisplayer__
#define __MYLC__TextDisplayer__

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "EffectSprite3D.h"
#include <vector>


class TextDisplayer:public cocos2d::Node
{
protected:
    TextDisplayer();
public:
    static TextDisplayer* create();
    void setTextToDisplay(std::vector<std::string> strs);
    void setLabel(cocos2d::Label* label);
    void startTyping();
    void typing(float dt);
    int contentlength(std::string &s);
    
private:
    cocos2d::Label *m_label;
    cocos2d::BillBoard *m_bill;
    std::string m_text;
    std::vector<std::string> m_strs;
    int m_textIndex;
    int m_strIndex;
    int m_totalLength;
    int m_pausingCounter;
};



#endif /* defined(__MYLC__TextDisplayer__) */
