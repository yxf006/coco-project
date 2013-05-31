#include "MenuLayerMainMenu.h"
#include "MenuLayerPlayerSelect.h"



MenuLayerMainMenu::MenuLayerMainMenu( void )
{
	CCLabelBMFont* label_new=CCLabelBMFont::create("New Game","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_new=CCMenuItemLabel::create(label_new,this,menu_selector(MenuLayerMainMenu::menuCallback));

	CCLabelBMFont* label_load=CCLabelBMFont::create("Load Game","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_load=CCMenuItemLabel::create(label_load,this,menu_selector(MenuLayerMainMenu::menuCallback));

	CCLabelBMFont* label_config=CCLabelBMFont::create("Config","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_config=CCMenuItemLabel::create(label_config,this,menu_selector(MenuLayerMainMenu::menuCallback));

	CCLabelBMFont* label_toplist=CCLabelBMFont::create("Top List","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_toplist=CCMenuItemLabel::create(label_toplist,this,menu_selector(MenuLayerMainMenu::menuCallback));


	CCLabelBMFont* label_help=CCLabelBMFont::create("Help","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_help=CCMenuItemLabel::create(label_help,this,menu_selector(MenuLayerMainMenu::menuCallback));
	//item_config->setScale(1.2);

	CCLabelBMFont* label_exit=CCLabelBMFont::create("Exit","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_exit=CCMenuItemLabel::create(label_exit,this,menu_selector(MenuLayerMainMenu::menuCallback));


	//CCMenu* mainmenu=CCMenu::create(item_new,item_load,item_config,item_toplist,item_help,item_exit,NULL);
	CCMenu* mainmenu=CCMenu::create();
	mainmenu->addChild(item_new,1000+1);
	mainmenu->addChild(item_load,1000+2);
	mainmenu->addChild(item_config,1000+3);
	mainmenu->addChild(item_toplist,1000+4);
	mainmenu->addChild(item_help,1000+5);
	mainmenu->addChild(item_exit,1000+6);


	//mainmenu->alignItemsVertically();
	mainmenu->alignItemsVerticallyWithPadding(10);

	CCSize s=CCDirector::sharedDirector()->getWinSize();
	int i=0;
	CCNode* child;
	CCArray * pArray = mainmenu->getChildren();
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if(pObject == NULL)
			break;

		child = (CCNode*)pObject;

		CCPoint dstPoint = child->getPosition();
		int offset = (int) (s.width/2 + 50);
		if( i % 2 == 0)
			offset = -offset;

		child->setPosition( ccp( dstPoint.x + offset, dstPoint.y) );
		child->runAction( 
			CCEaseElasticOut::create(CCMoveBy::create(2, ccp(dstPoint.x - offset,0)), 0.35f) 
			);
		i++;
	}


	this->addChild(mainmenu);
	mainmenu->setPosition(ccp(s.width/2,s.height/2));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/mainMainMusic.mp3");
	
}


MenuLayerMainMenu::~MenuLayerMainMenu(void)
{
}


void MenuLayerMainMenu::menuCallback(CCObject* pSender)
{
	CCLOG("menuCallback called");

	// get the userdata, it's the index of the menu item clicked
	CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
	int nIdx = pMenuItem->getZOrder() - 1000;

	// create the test scene and run it
	switch (nIdx)
	{
	case 1:
		{
			CCLOG("new game clicked");

			CCScene* scene=CCScene::create();
			CCLayer* layer=MenuLayerPlayerSelect::create();
			scene->addChild(layer,0);
			CCDirector::sharedDirector()->pushScene(CCTransitionSlideInT::create(1,scene));

			break;

		}
		
	case 2:
		CCLOG("load game clicked");
		break;

	case 6:
		CCDirector::sharedDirector()->end();
	default:
		break;
	}
}
