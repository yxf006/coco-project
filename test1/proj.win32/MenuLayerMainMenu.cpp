#include "MenuLayerMainMenu.h"




MenuLayerMainMenu::MenuLayerMainMenu( void )
{
	CCLabelBMFont* label_new=CCLabelBMFont::create("New Game","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_new=CCMenuItemLabel::create(label_new,this,menu_selector(MenuLayerMainMenu::menuCallbackConfig));

	CCLabelBMFont* label_load=CCLabelBMFont::create("Load Game","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_load=CCMenuItemLabel::create(label_load,this,menu_selector(MenuLayerMainMenu::menuCallbackConfig));

	CCLabelBMFont* label_config=CCLabelBMFont::create("Config","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_config=CCMenuItemLabel::create(label_config,this,menu_selector(MenuLayerMainMenu::menuCallbackConfig));

	CCLabelBMFont* label_toplist=CCLabelBMFont::create("Top List","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_toplist=CCMenuItemLabel::create(label_toplist,this,menu_selector(MenuLayerMainMenu::menuCallbackConfig));


	CCLabelBMFont* label_help=CCLabelBMFont::create("Help","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_help=CCMenuItemLabel::create(label_help,this,menu_selector(MenuLayerMainMenu::menuCallbackConfig));
	//item_config->setScale(1.2);

	CCLabelBMFont* label_exit=CCLabelBMFont::create("Exit","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_exit=CCMenuItemLabel::create(label_exit,this,menu_selector(MenuLayerMainMenu::menuCallbackConfig));


	CCMenu* mainmenu=CCMenu::create(item_new,item_load,item_config,item_toplist,item_help,item_exit,NULL);
	mainmenu->alignItemsVertically();


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
}


MenuLayerMainMenu::~MenuLayerMainMenu(void)
{
}


void MenuLayerMainMenu::menuCallbackConfig(CCObject* pSender)
{
	CCLOG("menuCallbackConfig called");
}
