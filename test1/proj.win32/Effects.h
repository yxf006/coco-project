#pragma once
#include "cocos2d.h"
#include "GameOverLayer.h"
#include "GamingLayer.h"


USING_NS_CC;

class Effects
{
public:
	/*Effects(void);
	~Effects(void);*/
	
	//single mode
	static Effects* ShareEffects();
	
	void PreLoad();
	void boom(CCNode* pNode,CCPoint point);
	void boom_callback(CCNode* pNode);

	void boom_hero(CCNode* pNode,CCPoint point);
	void boom_hero_callback(CCNode* pNode);
};

