#include "MenuLayerPlayerSelect.h"


MenuLayerPlayerSelect::MenuLayerPlayerSelect(void)
{
	s=CCDirector::sharedDirector()->getWinSize();
}


MenuLayerPlayerSelect::~MenuLayerPlayerSelect(void)
{
}

bool MenuLayerPlayerSelect::init()
{
	if (CCLayerColor::initWithColor(ccc4(0,0,0,0)))
	{
		

		/*CCSprite* sprite1=CCSprite::create("HelloWorld.png");
		addChild(sprite1);
		sprite1->setPosition(ccp(s.width/2,s.height/2));*/

		//左右滑屏箭头改用菜单比较好。方便回调
		/*CCSprite* leftarrow=CCSprite::create("images/b2.png");
		CCSprite* rightarrow=CCSprite::create("images/f2.png");

		addChild(leftarrow);
		addChild(rightarrow);

		leftarrow->setPosition(ccp(20+leftarrow->getContentSize().width/2,s.height/2));
		rightarrow->setPosition(ccp(s.width-20-rightarrow->getContentSize().width/2,s.height/2));
		*/

		/*飞机精灵用plist实现
		CCSprite* play1=CCSprite::create("images/pea.png");
		CCSprite* play2=CCSprite::create("	");
		addChild(play1);
		addChild(play2);
		play1->setPosition(ccp(s.width/2-100,s.height/2));
		play2->setPosition(ccp(s.width/2+100,s.height/2));
		*/


		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Monster.plist","Monster.png");


		pHero1=CCSprite::createWithSpriteFrameName("Monster1.png");
		pHero1->setPosition(ccp(s.width/2,s.height/2));
		//pHero1->setScale(1.5f);
		pHero1->setRotation(180);
		this->addChild(pHero1);

		pHero6=CCSprite::createWithSpriteFrameName("Monster6.png");
		pHero6->setPosition(ccp(s.width+pHero6->getContentSize().width,s.height/2));
		//pHero6->setScale(1.5f);
		pHero6->setRotation(180);
		this->addChild(pHero6);

		CCMenuItemImage *pLeftItem = CCMenuItemImage::create("images/b2.png","images/b1.png",this,	menu_selector(MenuLayerPlayerSelect::MenuLeftSlideCallBack) );
		pLeftItem->setPosition(ccp(20+pLeftItem->getContentSize().width/2,s.height/2));

		CCMenuItemImage *pRightItem = CCMenuItemImage::create("images/f2.png","images/f1.png",this,	menu_selector(MenuLayerPlayerSelect::MenuRightSlideCallBack) );
		pRightItem->setPosition(ccp(s.width-20-pRightItem->getContentSize().width/2,s.height/2));
		
		CCLabelBMFont* label_start=CCLabelBMFont::create("Start","fonts/bitmapFontTest3.fnt");
		CCMenuItemLabel* item_start=CCMenuItemLabel::create(label_start,this,menu_selector(MenuLayerPlayerSelect::MenuStartGameCallBack));
		item_start->setPosition(s.width/2,pRightItem->getPositionY()-80);

		//CCMenuItemSprite* phero1_item=CCMenuItemSprite::create(pHero1,pHero1,this,menu_selector(MenuLayerPlayerSelect::MenuHeroSelectedCallBack));

		CCMenu* menu=CCMenu::create(pLeftItem,pRightItem,item_start,NULL);

	

		this->addChild(menu);
		menu->setPosition(CCPointZero);

		/*CCSprite* sp_return=CCSprite::create("images/r1.png");
		
		addChild(sp_return);
		
		sp_return->setPosition(ccp(s.width-sp_return->getContentSize().width/2-20,sp_return->getContentSize().height/2+20));*/
		//返回主界面菜单
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCMenuItemImage *item_home = CCMenuItemImage::create("images/r1.png","images/r2.png",	this,menu_selector(MenuLayerPlayerSelect::menuGoHomeCallback));

		item_home->setPosition(ccp(origin.x + visibleSize.width - item_home->getContentSize().width/2 ,	origin.y + item_home->getContentSize().height/2));

		// create menu, it's an autorelease object
		CCMenu* pMenu = CCMenu::create(item_home, NULL);
		addChild(pMenu, 5);
		pMenu->setPosition(CCPointZero);
		

		this->setTouchEnabled(true);
		
		return true;
	}
	return false;

}

void MenuLayerPlayerSelect::menuGoHomeCallback( CCObject* pSender )
{
	CCLOG("go home clicked");
	CCDirector::sharedDirector()->popToRootScene();


}

void MenuLayerPlayerSelect::MenuLeftSlideCallBack( CCObject* pSender )
{
	CCLOG("MenuLeftSlideCallBack clicked");

	CCMoveTo* pMoveTo6=CCMoveTo::create(0.5f,ccp(s.width+pHero6->getContentSize().width,s.height/2));
	pHero6->runAction(pMoveTo6);

	CCMoveTo* pMoveTo1=CCMoveTo::create(0.5f,ccp(s.width/2,s.height/2));
	pHero1->runAction(pMoveTo1);

	

	//pHero6->setPosition(ccp(s.width+pHero6->getContentSize().width,s.height/2));
	//pHero1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
}

void MenuLayerPlayerSelect::MenuRightSlideCallBack( CCObject* pSender )
{
	CCLOG("MenuRightSlideCallBack clicked");

	CCMoveTo* pMoveTo1=CCMoveTo::create(0.5f,ccp(0-pHero1->getContentSize().width,s.height/2));
	pHero1->runAction(pMoveTo1);
	//pHero1->setPosition(ccp(0-pHero1->getContentSize().width,s.height/2));
	//pHero6->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
	CCMoveTo* pMoveTo6=CCMoveTo::create(0.5f,ccp(s.width/2,s.height/2));
	pHero6->runAction(pMoveTo6);
}

void MenuLayerPlayerSelect::MenuStartGameCallBack( CCObject* pSender )
{
	CCLOG("MenuStartGameCallBack clicked");
}

void MenuLayerPlayerSelect::MenuHeroSelectedCallBack( CCObject* pSender )
{

}

void MenuLayerPlayerSelect::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchpoint=convertTouchToNodeSpace(pTouch);

	if (pHero1->boundingBox().containsPoint(touchpoint))
	{
		//CCMessageBox("Hero1 selected","");
		CCDirector::sharedDirector()->pushScene(GamingLayer::scene(1));

	}else if(pHero6->boundingBox().containsPoint(touchpoint))
	{
		//CCMessageBox("Hero6 selected","");
		CCDirector::sharedDirector()->pushScene(GamingLayer::scene(6));
	}else
	{
		//CCMessageBox("No selected","");
	}

}

void MenuLayerPlayerSelect::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true	);
}

bool MenuLayerPlayerSelect::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;

}
