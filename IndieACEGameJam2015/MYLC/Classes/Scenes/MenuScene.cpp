//
//  MenuScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "MenuScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MenuScene::MenuScene()
{
    m_pMainCamera = nullptr;
}
// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    m_nCurrentLevel = UserDefault::getInstance()->getIntegerForKey("CurrentLevel", 1);
    if(m_nCurrentLevel > 6)
    {
        m_nCurrentLevel = 1;
        UserDefault::getInstance()->setIntegerForKey("CurrentLevel", m_nCurrentLevel);
    }
    return true;
}