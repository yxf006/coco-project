#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
class GameOverLayer :	public CCLayerColor
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);
	
	virtual bool init();

	//virtual bool initWithColor(const ccColor4B& color);

	void initLayer();

	static CCScene* scene();

	CREATE_FUNC(GameOverLayer);

	void menu_Callback(CCObject* pSender);

	void GameOverDone();

};

