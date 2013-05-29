#pragma once
#include "cocos2d.h"

USING_NS_CC;
class HeroBulletManager :public CCLayer
{
public:
	HeroBulletManager(void);
	~HeroBulletManager(void);

	virtual bool init();

	CREATE_FUNC(HeroBulletManager);

	void initLayer();
private:
	CCSpriteBatchNode* m_bulletBatchNode;
	
public:
	void AddNewBullet(const CCPoint point,const CCSize herosize,int bullettyep=1);
	void MoveAllBullets(float t);

private:
	CCArray* bulletsArray;

	


};

