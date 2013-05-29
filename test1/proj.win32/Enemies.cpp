#include "Enemies.h"


Enemies::Enemies(void)
{
}


Enemies::~Enemies(void)
{
}

bool Enemies::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initLayer();
	return  true;
	

}

void Enemies::initLayer()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Enemy.plist","Enemy.png");
	arrayEnenies=CCArray::create();
	

}

void Enemies::AddEnemy( float t )
{
	CCSprite* spenemy2=CCSprite::createWithSpriteFrameName("E2.png");
	spenemy2->setPosition(ccp(30 ,300));
	this->addChild(spenemy2);
	arrayEnenies->addObject(spenemy2);

	CCSprite* spenemy3=CCSprite::createWithSpriteFrameName("E3.png");
	spenemy3->setPosition(ccp(100 ,200));
	this->addChild(spenemy3);
	arrayEnenies->addObject(spenemy3);

	CCSprite* spenemy4=CCSprite::createWithSpriteFrameName("E4.png");
	spenemy4->setPosition(ccp(200 ,350));
	this->addChild(spenemy4);
	arrayEnenies->addObject(spenemy4);

	CCSprite* spenemy5=CCSprite::createWithSpriteFrameName("E5.png");
	spenemy5->setPosition(ccp(300 ,400));
	this->addChild(spenemy5);
	arrayEnenies->addObject(spenemy5);

}
