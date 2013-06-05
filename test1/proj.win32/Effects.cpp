#include "Effects.h"

//
//Effects::Effects(void)
//{
//}
//
//
//Effects::~Effects(void)
//{
//}
static Effects* instance=NULL;

Effects* Effects::ShareEffects()
{
	if (!instance)
	{
		instance=new Effects();

	}
	return instance;


}

void Effects::PreLoad()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("explosion.plist","explosion.png");

	CCAnimation* boom_animation=CCAnimation::create();
	boom_animation->setDelayPerUnit(0.05f);
	boom_animation->setLoops(1);

	for (int i=1 ; i<=35; i++)
	{
		CCString* picname=CCString::createWithFormat("explosion_%02d.png",i);
		CCSpriteFrame* pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picname->getCString());
		boom_animation->addSpriteFrame(pFrame);

	}

	CCAnimationCache::sharedAnimationCache()->addAnimation(boom_animation,"boom");
}

//把特效加到pnode指向层的point位置
void Effects::boom( CCNode* pNode,CCPoint point )
{
	CCSprite* spBoom=CCSprite::createWithSpriteFrameName("explosion_01.png");
	pNode->addChild(spBoom);
	spBoom->setPosition(point);

	CCAnimation* boom_animation=CCAnimationCache::sharedAnimationCache()->animationByName("boom");
	CCAnimate* boom_animate=CCAnimate::create(boom_animation);

	CCCallFuncN* callback=CCCallFuncN::create(spBoom,callfuncN_selector(Effects::boom_callback));

	CCAction* actions=CCSequence::create(boom_animate,callback,NULL);

	spBoom->runAction(actions);
}

void Effects::boom_callback( CCNode* pNode )
{
	pNode->removeFromParentAndCleanup(true);
}

void Effects::boom_hero( CCNode* pNode,CCPoint point )  //这里的pNode是GamingLayer指针
{
	CCSprite* spBoom=CCSprite::createWithSpriteFrameName("explosion_01.png");
	pNode->addChild(spBoom);//爆炸精灵加入到GamingLayer中
	spBoom->setPosition(point);

	CCAnimation* boom_animation=CCAnimationCache::sharedAnimationCache()->animationByName("boom");
	CCAnimate* boom_animate=CCAnimate::create(boom_animation);
	
	CCCallFuncN* callback=CCCallFuncN::create(spBoom,callfuncN_selector(Effects::boom_hero_callback));

	CCAction* actions=CCSequence::create(boom_animate,callback,NULL);

	spBoom->runAction(actions);
}

void Effects::boom_hero_callback( CCNode* pNode )  //这里的PNode是上面的spBoom
{
	CCLOG("boom_hero_callback");
	//CCMessageBox("test callback","title");
	//CCNode *p, *pp;
	GamingLayer *p;
	p=(GamingLayer*)pNode->getParent();  //GamingLayer
	//pp=p->getParent();		//CCScene
	/*
	//取消子弹添加schedule，停止hero子弹射击，加在这里效果不对。动画播放完之前还在发射。改在碰撞发生时候
	p->m_HeroBulletManager->unscheduleAllSelectors();
	p->unschedule(schedule_selector(GamingLayer::Hero_Fire));
	//p->m_HeroBulletManager->GetHeroBulletArray()->removeAllObjects();
	p->m_HeroBulletManager->removeAllChildrenWithCleanup(true);
	*/

	/*
	//取消场景切换，改为当前场景提示结果。更加合理
	pNode->removeFromParentAndCleanup(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCScene* pscene=GameOverLayer::scene();
	CCDirector::sharedDirector()->replaceScene(pscene);*/

	// add Gameover layer
	GameOverLayer* pGameover=GameOverLayer::create();
	pGameover->setVisible(true);
	pGameover->setPosition(CCPointZero);
	pNode->getParent()->addChild(pGameover,99,99);
}


