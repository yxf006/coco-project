#pragma once
#include "cocos2d.h"


USING_NS_CC;
class Enemies :	public CCLayer
{
public:
	Enemies(void);
	~Enemies(void);

	virtual bool init();

	CREATE_FUNC(Enemies);

	void initLayer();

	//敌人随机出现
	void AddEnemy(float t);


	//敌人随机向Hero移动
	void MoveAllEnemies(float t);


private:
	CCArray* arrayEnenies;
	
};

