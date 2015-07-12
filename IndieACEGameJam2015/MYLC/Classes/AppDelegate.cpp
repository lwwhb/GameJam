#include "AppDelegate.h"
#include "LevelSelectScene.h"
#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "FinalScene.h"
USING_NS_CC;
using namespace CocosDenshion;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Make your life colorful!");
        director->setOpenGLView(glview);
    }

    std::vector<std::string> searchPaths;
    searchPaths.push_back("fonts");
    searchPaths.push_back("lang");
    searchPaths.push_back("maps");
    searchPaths.push_back("models");
    searchPaths.push_back("music");
    searchPaths.push_back("particles");
    searchPaths.push_back("sounds");
    searchPaths.push_back("shaders");
    searchPaths.push_back("textures");
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#else
    // turn off display FPS
    director->setDisplayStats(false);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object

    auto scene = LogoScene::createScene();
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Evenflow.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Evenflow.mp3",true);
    SimpleAudioEngine::getInstance()->preloadEffect("life.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("start.mp3");

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Horizon.mp3");
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    SimpleAudioEngine::getInstance()->resumeAllEffects();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
