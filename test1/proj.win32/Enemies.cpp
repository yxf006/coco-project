#include "Enemies.h"
#include "GamingLayer.h"
#include "Effects.h"
#include "GameOverLayer.h"

Enemies::Enemies(void)
{
	s=CCDirector::sharedDirector()->getWinSize();
}


Enemies::~Enemies(void)
{
	/*CC_SAFE_DELETE_ARRAY(arrayEnenies);
	CC_SAFE_DELETE_ARRAY(m_arrayBullets);*/
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
	arrayEnenies->retain();
	this->schedule(schedule_selector(Enemies::MoveAllEnemies),0.035f);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist","bullet.png");

	m_bulletBatchNode=CCSpriteBatchNode::create("bullet.png");
	ccBlendFunc cb={GL_SRC_ALPHA,GL_ONE};
	m_bulletBatchNode->setBlendFunc(cb);
	this->addChild(m_bulletBatchNode);
	m_arrayBullets=CCArray::create();
	m_arrayBullets->retain();
	//this->schedule(schedule_selector(Enemies::AddNewBullet),0.5f);//不用定时增加，随机时间随机敌人增加
	this->schedule(schedule_selector(Enemies::MoveAllBullets),0.05f);

	Effects::ShareEffects()->PreLoad();
	
	

}


void Enemies::AddEnemy( float t )
{
	int minX=0;
	int maxX=s.width;

	int birthX=rand()%(maxX-minX)+minX;
	
	/*int minY=0;
	int maxY=0;*/
	int birthY=s.height;

	CCSprite* spenemy1=CCSprite::createWithSpriteFrameName("E1.png");
	spenemy1->setPosition(ccp(birthX ,birthY));
	this->addChild(spenemy1);
	arrayEnenies->addObject(spenemy1);

	birthX=rand()%(maxX-minX)+minX;
	CCSprite* spenemy2=CCSprite::createWithSpriteFrameName("E2.png");
	spenemy2->setPosition(ccp(birthX ,birthY));
	this->addChild(spenemy2);
	arrayEnenies->addObject(spenemy2);

	birthX=rand()%(maxX-minX)+minX;
	CCSprite* spenemy3=CCSprite::createWithSpriteFrameName("E3.png");
	spenemy3->setPosition(ccp(birthX ,birthY));
	this->addChild(spenemy3);
	arrayEnenies->addObject(spenemy3);


	birthX=rand()%(maxX-minX)+minX;
	CCSprite* spenemy4=CCSprite::createWithSpriteFrameName("E4.png");
	spenemy4->setPosition(ccp(birthX ,birthY));
	this->addChild(spenemy4);
	arrayEnenies->addObject(spenemy4);

	birthX=rand()%(maxX-minX)+minX;
	CCSprite* spenemy5=CCSprite::createWithSpriteFrameName("E5.png");
	spenemy5->setPosition(ccp(birthX ,birthY));
	this->addChild(spenemy5);
	arrayEnenies->addObject(spenemy5);

}

void Enemies::MoveAllEnemies( float t )
{
	if (arrayEnenies->count()<=0)
	{	
		return;
	}
	CCObject* obj;
	CCARRAY_FOREACH(arrayEnenies,obj)
	{
		//CCString* log=CCString::createWithFormat("arrayEnemy count %d",arrayEnenies->count());
		//CCLOG(log->getCString());

		CCSprite* spEnemy=(CCSprite*)obj;

		CC_BREAK_IF(!spEnemy);
		if (spEnemy->getPositionY() < 0)
		{
			//CCString* log=CCString::createWithFormat("spEnemy->getPositionY %f",spEnemy->getPositionY());
			//CCLOG(log->getCString());

			this->removeChild(spEnemy,true);
			arrayEnenies->removeObject(spEnemy,true);
			break;
			
		}else
		{
			int actualX=spEnemy->getPositionX();
			int durationX=rand()%100;
			int targetX=0;
			if (rand()%2==0){
				targetX=actualX+durationX;	
			}else{
				targetX=actualX-durationX;	
			}
			//防止出屏
			if (targetX<0)
			{
				targetX=0+spEnemy->getContentSize().width/2;
			}
			if (targetX>s.width)
			{
				targetX=s.width-spEnemy->getContentSize().width/2;
			}

			//CCPoint targetpoint=ccp(rand()%(int)(s.width),sp->getPositionY()-5);
			CCPoint targetpoint=ccp(targetX,spEnemy->getPositionY()-10);

			float randduration=CCRANDOM_0_1()*6;
			//CCLOG("randduration:%f",randduration);
			CCMoveTo* moveaction=CCMoveTo::create(randduration,targetpoint);
			spEnemy->runAction(moveaction);
			//sp->setPosition( targetpoint);
			//sp->setPosition(ccp(rand()%(int)(s.width),sp->getPositionY()-5));
			//sp->setPositionY(sp->getPositionY()-5);
			
			//随机增加敌人子弹
			if (rand()%50==0)
			{
				CCSprite* spEnemyBullet =CCSprite::createWithSpriteFrameName("W2.png");
				spEnemyBullet->setPosition(ccp(spEnemy->getPositionX(),spEnemy->getPositionY()+spEnemy->getContentSize().height/2));
				this->m_arrayBullets->addObject(spEnemyBullet);
				//this->addChild(spEnemyBullet);
				m_bulletBatchNode->addChild(spEnemyBullet);
			}


			//判断hero与enemy碰撞
			GamingLayer* gameLayer=(GamingLayer*)this->getParent();
			if (spEnemy->boundingBox().containsPoint(gameLayer->GetHero()->getPosition()))
			{
				CCLOG("hero enemy kiss hero enemy kiss hero enemy kiss");
				this->removeChild(spEnemy);
				//gameLayer->removeChild(gameLayer->GetHero());
			}
		}

	}

}

CCArray* Enemies::GetEnemyArray()
{
	return arrayEnenies;

}

CCArray* Enemies::GetBulletsArray()
{
	return m_arrayBullets;

}

void Enemies::MoveAllBullets( float t )
{
	CCObject* obj;
	CCARRAY_FOREACH(m_arrayBullets,obj){

		CCSprite* spEnemyBullet=(CCSprite*)obj;

		if (spEnemyBullet->getPositionY()<0)
		{
			this->removeChild(spEnemyBullet);
			m_arrayBullets->removeObject(spEnemyBullet);
			break;
		}else
		{
			
			//spEnemyBullet->setPositionY(spEnemyBullet->getPositionY()-50);
			CCPoint targetpoint=ccp(spEnemyBullet->getPositionX(),spEnemyBullet->getPositionY()-30);


			CCMoveTo *moveaction=CCMoveTo::create(1.0f,targetpoint);
			spEnemyBullet->runAction(moveaction);

			//判断敌人子弹与hero碰撞
			GamingLayer* gameLayer=(GamingLayer*)this->getParent();
			if (gameLayer->GetHero()->boundingBox().containsPoint(spEnemyBullet->getPosition())/*spEnemyBullet->boundingBox().containsPoint(gameLayer->GetHero()->getPosition()*/)
			{
				CCLOG("Oh,no,Hero is be attacked");
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Music/shipDestroyEffect.mp3");
				Effects::ShareEffects()->boom_hero(gameLayer,gameLayer->GetHero()->getPosition());
				m_bulletBatchNode->removeChild(spEnemyBullet,true);
				//this->removeChild(spEnemyBullet,true);
				m_arrayBullets->removeObject(spEnemyBullet,true);
				gameLayer->m_HeroBulletManager->unscheduleAllSelectors();
				gameLayer->unschedule(schedule_selector(GamingLayer::Hero_Fire));
				//p->m_HeroBulletManager->GetHeroBulletArray()->removeAllObjects();
				gameLayer->m_HeroBulletManager->removeAllChildrenWithCleanup(true);

				gameLayer->GetHero()->setVisible(false);//看不见了还在发射子弹哟
				//场景切换到gameover
				//gameLayer->stopAllActions();//加了这句，所有动画也不执行了。动画回调也木有了 - -
				
				//this->removeFromParentAndCleanup(true);
				//gameLayer->removeAllChildrenWithCleanup(true);
				CCLOG("before CCDirector::sharedDirector()->replaceScene(GameOverLayer::scene())");
				/*CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				CCScene* pscene=GameOverLayer::scene();
				CCDirector::sharedDirector()->replaceScene(pscene);*/
				CCLOG("after CCDirector::sharedDirector()->replaceScene(GameOverLayer::scene())");
				
				//this->unscheduleAllSelectors();
				break;
				//CCLOG("end CCDirector::sharedDirector()->replaceScene(GameOverLayer::scene())");
				
			}
		
		}

	}
}
