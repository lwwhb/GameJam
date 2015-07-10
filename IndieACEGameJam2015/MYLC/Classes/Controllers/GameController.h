//
//  GameController.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__GameController__
#define __MYLC__GameController__

#include "cocos2d.h"
#include "GroundLayer.h"
class GameController : public cocos2d::Ref
{
    GameController();
    ~GameController();
public:
    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void update(float delta);
    void destroy();
private:
    cocos2d::Layer*     m_pMainLayer;
    GroundLayer*        m_pGroundLayer;
    cocos2d::Camera*    m_pMainCamera;
};

#endif /* defined(__MYLC__GameController__) */
