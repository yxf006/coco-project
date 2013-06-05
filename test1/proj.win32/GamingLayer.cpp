#include "GamingLayer.h"


GamingLayer::GamingLayer(void)
{
	s=CCDirector::sharedDirector()->getWinSize();
}


GamingLayer::~GamingLayer(void)
{
}

bool GamingLayer::init( int index_hero )
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_index_hero=index_hero;
	initLayer();
	setTouchEnabled(true);
	return true;

}



GamingLayer* GamingLayer::create( int index_hero/*=0*/ )
{
	GamingLayer *pRet = new GamingLayer();
	if (pRet && pRet->init(index_hero))
	{
		pRet->autorelease();
		return pRet;
	} 
	else
	{
		delete pRet;
		pRet=NULL;
		return NULL;

	}
}

bool GamingLayer::BornHero( int index_hero )
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Monster.plist","Monster.png");
	CCString* HeroFrameName=CCString::createWithFormat("Monster%d.png",index_hero);
	
	//switch (index_hero){
	//case 0:
	//	//sprintf_s(HeroFrameName.getCString(),"Monster%d.png",index_hero);
	//	
	//	
	//	break;
	//case 1:
	//	break;
	//case 2:
	//	break;
	//default:
	//	break;
	//}

	m_hero=CCSprite::createWithSpriteFrameName(HeroFrameName->getCString());
	m_hero->setPosition(ccp(s.width/2,m_hero->getContentSize().height+5));
	//m_hero->setPosition(ccp(s.width/2,s.height/2));
	//m_hero->setScale(1.0f);
	m_hero->setRotation(180);
	this->addChild(m_hero);

	return true;
	
}

CCScene* GamingLayer::scene(int index_hero)
{
	CCScene* sc=NULL;
	do 
	{
		sc=CCScene::create();
		CC_BREAK_IF(!sc);
		GamingLayer* layer=GamingLayer::create(index_hero);
		CC_BREAK_IF(!layer);
		sc->addChild(layer);
	} while (0);

	return sc;
}

void GamingLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true	);

}



void GamingLayer::Hero_Fire( float t )
{
	int bullettype;
	switch (m_index_hero){
	case 1:
		bullettype=1;
		break;
	case 6:
		bullettype=2;
		break;
	default:
		bullettype=1;
		break;
	}
	m_HeroBulletManager->AddNewBullet(m_hero->getPosition(),m_hero->getContentSize(),bullettype);
}


void GamingLayer::initLayer()
{
	do 
	{

		//set background

		CCSprite* bg1=CCSprite::create("bg01.png");
		CCSprite* bg2=CCSprite::create("bg01.png");

		CC_BREAK_IF(!bg1);
		CC_BREAK_IF(!bg2);

		bg1->setAnchorPoint(CCPointZero);
		bg2->setAnchorPoint(CCPointZero);

		bg1->setPosition(CCPointZero);
		bg2->setPosition(ccp(0,bg1->getContentSize().height));

		addChild(bg1,0,11);
		addChild(bg2,0,12);

		this->schedule(schedule_selector(GamingLayer::Background_Scroll),0.05f);

		//get hero
		BornHero(m_index_hero);

		m_HeroBulletManager=HeroBulletManager::create();

		this->addChild(m_HeroBulletManager);

		this->schedule(schedule_selector(GamingLayer::Hero_Fire),0.08f);


		//add enemy
		m_Enemies=Enemies::create();
		this->addChild(m_Enemies);
		this->schedule(schedule_selector(GamingLayer::Enemy_Add),2.0f);
		//this->Enemy_Add(1);

		//add brackground music
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/bgMusic.mp3");

	} while (0);
	

}



bool GamingLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//CCPoint touchpoint=convertTouchToNodeSpace(pTouch);
	CCMoveTo* moveaction=CCMoveTo::create(0.3f,pTouch->getLocation());
	//CCMoveTo* moveaction=CCMoveTo::create(0.5f,touchpoint);
	m_hero->runAction(moveaction);
	//m_hero->setAnchorPoint(ccp(m_hero->getContentSize().width/2,m_hero->getContentSize().height/2));
	//m_hero->setPosition(pTouch->getLocation());//不用加这句，否则hero在界面上滑来滑去，无法定位。
	//m_hero->setPosition(touchpoint);
	return true;
}


void GamingLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchpoint=pTouch->getLocation();
	CCPoint oldtouchpoint=pTouch->getPreviousLocation();

	//防止hero滑出屏幕
	if (touchpoint.x<0 )
	{
		touchpoint.x=0;
		return;
	}
	if (touchpoint.x>s.width)
	{
		CCLOG("touchpoint.x>s.width touch x %f",touchpoint.x);
		touchpoint.x=s.width;
		return;
	}
	CCPoint translateion=ccpSub(touchpoint,oldtouchpoint);
	CCPoint newpoint=ccpAdd(m_hero->getPosition(),translateion);
	//m_hero->setPosition(newpoint);//也可以的
	CCMoveTo* moveaction=CCMoveTo::create(0.02f,newpoint);
	m_hero->runAction(moveaction);
	

}

void GamingLayer::Enemy_Add( float t )
{
	m_Enemies->AddEnemy(1);

}

void GamingLayer::Background_Scroll( float t )
{
	CCSprite* bg1=(CCSprite*)getChildByTag(11);
	CCSprite* bg2=(CCSprite*)getChildByTag(12);

	/*bg1->setPosition(ccp(bg1->getPositionX(),bg1->getPositionY()-10));
	bg2->setPosition(ccp(bg2->getPositionX(),bg1->getPositionY()+bg1->getContentSize().height));

	if (bg2->getPositionY()<=0)
	{
		bg1->setPosition(CCPointZero);
	}*/
	bg1->setPositionY(bg1->getPositionY()-10);
	bg2->setPositionY(bg1->getPositionY()+bg1->getContentSize().height);

	if (bg2->getPositionY()<=0)
	{
		bg1->setPositionY(0);
	}
}

CCSprite* GamingLayer::GetHero()
{
	return m_hero;
}




