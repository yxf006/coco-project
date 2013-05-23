#pragma once
#include "cocos2d.h"


USING_NS_CC;

class MenuLayerMainMenu :public CCLayer
{
public:
	MenuLayerMainMenu(void);
	~MenuLayerMainMenu(void);
public:
	void menuCallback(CCObject* pSender);
};

