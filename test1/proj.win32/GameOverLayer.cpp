#include "GameOverLayer.h"
#include "MenuLayerMainMenu.h"

GameOverLayer::GameOverLayer(void)
{
}


GameOverLayer::~GameOverLayer(void)
{
}

bool GameOverLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0,0,0,0)))
	{
		return false;
	}

	
	initLayer();
	return true;

}



 CCScene* GameOverLayer::scene()
{
	CCScene* scene=NULL;

	do 
	{
		scene=CCScene::create();
		CC_BREAK_IF(!scene);//妹啊，少加一个叹号。折腾我两小时。kao 谨记教训

		GameOverLayer* layer=GameOverLayer::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

		

	} while (0);

	return scene;
	
	

}


void GameOverLayer::initLayer()
{
	CCLabelBMFont* label=CCLabelBMFont::create("You Lose","fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item_gameresult=CCMenuItemLabel::create(label,this,menu_selector(GameOverLayer::menu_Callback)) ;

	//CCLabelBMFont* label_exit=CCLabelBMFont::create("Exit","fonts/bitmapFontTest3.fnt");
	//CCMenuItemLabel* item_exit=CCMenuItemLabel::create(label_exit,this,menu_selector(GameOverLayer::menu_Callback));


	CCMenu* menu=CCMenu::create(item_gameresult,/*item_exit,*/NULL);
	menu->setPosition(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2);
	this->addChild(menu);
	menu->alignItemsVerticallyWithPadding(10);

	


	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/mainMainMusic.mp3");
	this->runAction(CCSequence::create(CCDelayTime::create(5),CCCallFunc::create(this, callfunc_selector(GameOverLayer::GameOverDone)),NULL));


}

void GameOverLayer::menu_Callback(CCObject* pSender)
{
	CCLOG("menu_Callback");
	
}

void GameOverLayer::GameOverDone()
{
	CCLOG("GameOverDone");
	CCScene *pScene=CCScene::create();
	CCLayer *pLayer=new MenuLayerMainMenu();
	pLayer->autorelease();
	pScene->addChild(pLayer);

	 CCDirector::sharedDirector()->replaceScene(pScene);

}


