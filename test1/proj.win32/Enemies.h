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

	//�����������
	void AddEnemy(float t);


	//���������Hero�ƶ�
	void MoveAllEnemies(float t);


private:
	CCArray* arrayEnenies;
	
};

