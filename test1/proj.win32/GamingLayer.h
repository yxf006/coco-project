#pragma once
#include "cocos2d.h"
#include "HeroBulletManager.h"
#include "Enemies.h"


USING_NS_CC;

class GamingLayer :	public CCLayer
{
public:
	GamingLayer(void);
	~GamingLayer(void);


public:
	bool init(int index_hero);
	void initLayer();

	static CCScene* scene(int index_hero);

	/*virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();*/
	//virtual bool init();
	//CREATE_FUNC(GamingLayer);

	static GamingLayer* create(int index_hero=0);


	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	/*virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
*/
	/*virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);*/


	virtual void registerWithTouchDispatcher(void);

	bool GetHero(int index_hero);

	void Background_Scroll(float t);

	void Hero_Fire(float t);

	void Enemy_Add(float t);


private:
	CCSize s;
	int m_index_hero;
	CCSprite* m_hero;
	HeroBulletManager* m_HeroBulletManager;

	Enemies* m_Enemies;

};

