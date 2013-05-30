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

	//���˷����ӵ�
	void AddNewBullet(float t);

	//�����ӵ��ƶ�
	void MoveAllBullets(float t);

	CCArray* GetEnemyArray();
	CCArray* GetBulletsArray();

private:
	CCArray* arrayEnenies;
	CCSize s;
	CCArray* m_arrayBullets;
	CCSpriteBatchNode* m_bulletBatchNode;
	
};

