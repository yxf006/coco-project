#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "AppMacros.h"

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MenuLayerMainMenu.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,kResolutionNoBorder);
	// turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	//pDirector->setContentScaleFactor(2.0f);
    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
	CCScene *pScene=CCScene::create();
	CCLayer *pLayer=new MenuLayerMainMenu();
	pLayer->autorelease();
	pScene->addChild(pLayer);
    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
