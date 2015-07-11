//
//  TextDisplayer.cpp
//  MYLC
//
//  Created by 李 旭 on 15/7/11.
//
//

#include "TextDisplayer.h"
USING_NS_CC;
using namespace std;

TextDisplayer::TextDisplayer()
{
    m_label = nullptr;
        
}

TextDisplayer* TextDisplayer::create()
{
    TextDisplayer* td = new TextDisplayer();

    if(td)
    {

        td->autorelease();
        return td;
    }
    
    CC_SAFE_DELETE(td);
    return nullptr;
}

void TextDisplayer::setLabel(cocos2d::Label *label)
{
    m_label = label;
}

void TextDisplayer::setTextToDisplay(std::vector<std::string> strs)
{
    m_textIndex = 0;
    m_totalLength = 0;
    m_strs = strs;
}

void TextDisplayer::startTyping()
{
    m_strIndex = 0;
    m_text = m_strs[0];
    m_pausingCounter =0;
    schedule(CC_SCHEDULE_SELECTOR(TextDisplayer::typing), 0.2f);
}

int TextDisplayer::contentlength(std::string &s)
{
    int i =0;
    int length = 0;
    while(i<s.length()) {
        char ch = s.c_str()[i];
        if (ch>-127&&ch<0) {
            length+=3;
        }else
        {
            length+=1;
        }
        i++;
    }
    return length;
}

void TextDisplayer::typing(float dt)
{
    if (m_pausingCounter<3) {
        m_pausingCounter++;
    }else
    {
        std::string str = m_text.substr(0,m_strIndex);
        m_label->setString(str);
        char ch = m_text.c_str()[m_strIndex+1];
        m_strIndex+=3;
        
        
        if (m_strIndex>m_text.length()) {
            
            m_textIndex++;
            m_strIndex = 0;
            if (m_textIndex<m_strs.size()) {
                m_text = m_strs[m_textIndex];
                m_pausingCounter=0;
                
            }else
            {
                m_label->setString(m_strs[m_strs.size()-1]);
                unschedule(CC_SCHEDULE_SELECTOR(TextDisplayer::typing));
            }
            
        }
    }
    

}


