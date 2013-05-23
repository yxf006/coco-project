#pragma once
#include "cocos2d.h"

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


};

