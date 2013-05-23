#include "MenuLayerPlayerSelect.h"


MenuLayerPlayerSelect::MenuLayerPlayerSelect(void)
{
}


MenuLayerPlayerSelect::~MenuLayerPlayerSelect(void)
{
}

bool MenuLayerPlayerSelect::init()
{
	if (CCLayerColor::initWithColor(ccc4(0,0,0,0)))
	{
		CCSize s=CCDirector::sharedDirector()->getWinSize();

		/*CCSprite* sprite1=CCSprite::create("HelloWorld.png");
		addChild(sprite1);
		sprite1->setPosition(ccp(s.width/2,s.height/2));*/

		CCSprite* leftarrow=CCSprite::create("images/b2.png");
		CCSprite* rightarrow=CCSprite::create("images/f2.png");

		addChild(leftarrow);
		addChild(rightarrow);

		leftarrow->setPosition(ccp(20+leftarrow->getContentSize().width/2,s.height/2));
		rightarrow->setPosition(ccp(s.width-20-rightarrow->getContentSize().width/2,s.height/2));


		CCSprite* play1=CCSprite::create("images/pea.png");
		CCSprite* play2=CCSprite::create("images/icon.png");
		addChild(play1);
		addChild(play2);
		play1->setPosition(ccp(s.width/2-100,s.height/2));
		play2->setPosition(ccp(s.width/2+100,s.height/2));


		/*CCSprite* sp_return=CCSprite::create("images/r1.png");
		
		addChild(sp_return);
		
		sp_return->setPosition(ccp(s.width-sp_return->getContentSize().width/2-20,sp_return->getContentSize().height/2+20));*/
		
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCMenuItemImage *item_home = CCMenuItemImage::create("images/r1.png","images/r2.png",	this,menu_selector(MenuLayerPlayerSelect::menuGoHomeCallback));

		item_home->setPosition(ccp(origin.x + visibleSize.width - item_home->getContentSize().width/2 ,	origin.y + item_home->getContentSize().height/2));

		// create menu, it's an autorelease object
		CCMenu* pMenu = CCMenu::create(item_home, NULL);
		addChild(pMenu, 5);
		pMenu->setPosition(CCPointZero);
		

		return true;
	}
	return false;

}

void MenuLayerPlayerSelect::menuGoHomeCallback( CCObject* pSender )
{
	CCLOG("go home clicked");
	CCDirector::sharedDirector()->popToRootScene();


}
