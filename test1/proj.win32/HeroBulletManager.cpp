#include "HeroBulletManager.h"
#include "GamingLayer.h"
#include "Effects.h"

#define OFFSIDE_HEIGHT 1200

HeroBulletManager::HeroBulletManager(void)
{
}


HeroBulletManager::~HeroBulletManager(void)
{
}

bool HeroBulletManager::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initLayer();
	return true;
}

void HeroBulletManager::initLayer()
{
	do 
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist","bullet.png");

		m_bulletBatchNode=CCSpriteBatchNode::create("bullet.png");

		ccBlendFunc cb={GL_SRC_ALPHA,GL_ONE};

		m_bulletBatchNode->setBlendFunc(cb);

		this->addChild(m_bulletBatchNode);

		bulletsArray=CCArray::create();

		bulletsArray->retain();

		this->schedule(schedule_selector(HeroBulletManager::MoveAllBullets),0.015f);

		Effects::ShareEffects()->PreLoad();

	} while (0);
	


}

void HeroBulletManager::AddNewBullet( const CCPoint point,const CCSize herosize,int bullettype /*=1*/ )
{
	
	CCString* bulletname=CCString::createWithFormat("W%d.png",bullettype);


	//CCSprite* bullet1=CCSprite::createWithSpriteFrameName("W1.png");
	CCSprite* bullet1=CCSprite::createWithSpriteFrameName(bulletname->getCString());

	bullet1->setPosition(ccp(point.x-herosize.width/4,point.y+herosize.height/2));

	//this->addChild(bullet1);

	//CCSprite* bullet2=CCSprite::createWithSpriteFrameName("W1.png");
	CCSprite* bullet2=CCSprite::createWithSpriteFrameName(bulletname->getCString());
	bullet2->setPosition(ccp(point.x+herosize.width/4,point.y+herosize.height/2));

	//this->addChild(bullet2);

	bulletsArray->addObject(bullet1);
	bulletsArray->addObject(bullet2);

	m_bulletBatchNode->addChild(bullet1);
	m_bulletBatchNode->addChild(bullet2);



}

void HeroBulletManager::MoveAllBullets(float t)
{
	CCSize s=CCDirector::sharedDirector()->getWinSize();

	CCObject* obj;

	CCARRAY_FOREACH(bulletsArray,obj){

		CCSprite* spBullet=(CCSprite*)obj;

		if (spBullet->getPositionY() > OFFSIDE_HEIGHT)
		{
			m_bulletBatchNode->removeChild(spBullet,true);
			bulletsArray->removeObject(spBullet,true);

		}else
		{
			spBullet->setPositionY(spBullet->getPositionY()+10);

			GamingLayer* gameLayer=(GamingLayer*)this->getParent();
			CCObject* obj;
			CCARRAY_FOREACH(gameLayer->m_Enemies->GetEnemyArray(),obj){

				CCSprite* spEnemy=(CCSprite*)obj;

				if (spEnemy->boundingBox().containsPoint(spBullet->getPosition()))
				{
					CCLOG("Yeah,Attack enemy ");
					
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Music/explodeEffect.mp3");
					Effects::ShareEffects()->boom(gameLayer,spEnemy->getPosition());
					
					gameLayer->m_Enemies->removeChild(spEnemy);
					gameLayer->m_Enemies->GetEnemyArray()->removeObject(spEnemy);
					break;
				} 
				else
				{

				}


			}

		}

	}

}
