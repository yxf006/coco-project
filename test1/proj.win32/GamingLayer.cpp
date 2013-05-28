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

	GetHero(index_hero);
	
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

bool GamingLayer::GetHero( int index_hero )
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
	m_hero->setPosition(ccp(s.width/2,s.height/2));
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

bool GamingLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//CCPoint touchpoint=convertTouchToNodeSpace(pTouch);
	CCMoveTo* moveaction=CCMoveTo::create(0.3f,pTouch->getLocation());
	//CCMoveTo* moveaction=CCMoveTo::create(0.5f,touchpoint);
	m_hero->runAction(moveaction);
	//m_hero->setAnchorPoint(ccp(m_hero->getContentSize().width/2,m_hero->getContentSize().height/2));
	//m_hero->setPosition(pTouch->getLocation());//不用加这句，否则hero在界面上滑来滑去，无法定位。
	//m_hero->setPosition(touchpoint);
	return false;
}
