//
//  GroundLayer.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__GroundLayer__
#define __MYLC__GroundLayer__

#include "cocos2d.h"
#include "GroundCell.h"
#include "Arrow.h"
#include "GameScene.h"
class GroundLayer : public cocos2d::Layer
{
    GroundLayer();
public:
    typedef enum {
        MS_IDLE = 0,
        MS_MOVE_LEFT,
        MS_MOVE_RIGHT,
        MS_MOVE_UP,
        MS_MOVE_DOWN,
        MS_CHECK_NEXT_CELL,
        MS_UNKNOWN
    } MoveState;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static GroundLayer* create(const std::string& tmxFile);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(const std::string& tmxFile);
    
    MoveState getMoveState() const { return m_curState; }
    void setMoveState(MoveState state);
    
    cocos2d::Vec3 getOffset() const { return m_Offset; }
    float getGroundRadius() { return MAX(m_fCellRadius*m_MapSize.width, m_fCellRadius*m_MapSize.height); }
    cocos2d::Size  getMapSize() const { return m_MapSize; }
    
    void setCamera(cocos2d::Camera* camera) { m_pCamera = camera; }
    
    cocos2d::Vector<GroundCell*> getNeighborCells(GroundCell* currentCell);
    
    float getCellRadius() const { return m_fCellRadius; }
    
    GroundCell* getNextCell(int nextIndexX, int nextIndexY);
    
    void flipIndexCell(int indexX, int indexY);
    void setCurrentCellTypeOK();
    void showArrow();
    void checkWinOrLose();
    void setGameScene(GameScene* scene) { m_pGameScene = scene; };
protected:
    // 处理输入
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
private:
    void onEnterIdle();
    void onEnterMoveLeft();
    void onEnterMoveRight();
    void onEnterMoveUp();
    void onEnterMoveDown();
    void onEnterCheckNextCell();
    
    void onExitIdle();
    void onExitMoveLeft();
    void onExitMoveRight();
    void onExitMoveUp();
    void onExitMoveDown();
    void onExitCheckNextCell();
private:
    GameScene*      m_pGameScene;
    cocos2d::Vector<GroundCell*>   m_GroundCellList;
    GroundCell*     m_pCurrentCell;
    Arrow*          m_pArrowUp;
    Arrow*          m_pArrowDown;
    Arrow*          m_pArrowLeft;
    Arrow*          m_pArrowRight;
    
    int             m_nNextIndexX;
    int             m_nNextIndexY;
    
    cocos2d::Size   m_MapSize;
    float           m_fCellRadius;
    cocos2d::Vec3   m_Offset;
    
    cocos2d::Camera*    m_pCamera;
    
    MoveState     m_curState;
};

#endif /* defined(__MYLC__GroundLayer__) */
