#pragma once
#include "cocos2d.h"
#include "GamingLayer.h"
USING_NS_CC;

class MenuLayerPlayerSelect :	public CCLayerColor
{
public:
	MenuLayerPlayerSelect(void);
	~MenuLayerPlayerSelect(void);
	bool init();
	CREATE_FUNC(MenuLayerPlayerSelect);

public:
	void menuGoHomeCallback(CCObject* pSender);	
	
	void MenuLeftSlideCallBack(CCObject* pSender);

	void MenuRightSlideCallBack(CCObject* pSender);
	void MenuStartGameCallBack(CCObject* pSender);
	void MenuHeroSelectedCallBack(CCObject* pSender);

	virtual void registerWithTouchDispatcher(void);    
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);    
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
	CCSprite* pHero1;
	CCSprite* pHero6;
	CCSize s;


};

