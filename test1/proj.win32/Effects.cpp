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

//����Ч�ӵ�pnodeָ����pointλ��
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

void Effects::boom_hero( CCNode* pNode,CCPoint point )  //�����pNode��GamingLayerָ��
{
	CCSprite* spBoom=CCSprite::createWithSpriteFrameName("explosion_01.png");
	pNode->addChild(spBoom);//��ը������뵽GamingLayer��
	spBoom->setPosition(point);

	CCAnimation* boom_animation=CCAnimationCache::sharedAnimationCache()->animationByName("boom");
	CCAnimate* boom_animate=CCAnimate::create(boom_animation);
	
	CCCallFuncN* callback=CCCallFuncN::create(spBoom,callfuncN_selector(Effects::boom_hero_callback));

	CCAction* actions=CCSequence::create(boom_animate,callback,NULL);

	spBoom->runAction(actions);
}

void Effects::boom_hero_callback( CCNode* pNode )  //�����PNode�������spBoom
{
	CCLOG("boom_hero_callback");
	//CCMessageBox("test callback","title");
	//CCNode *p, *pp;
	GamingLayer *p;
	p=(GamingLayer*)pNode->getParent();  //GamingLayer
	//pp=p->getParent();		//CCScene
	/*
	//ȡ���ӵ����schedule��ֹͣhero�ӵ��������������Ч�����ԡ�����������֮ǰ���ڷ��䡣������ײ����ʱ��
	p->m_HeroBulletManager->unscheduleAllSelectors();
	p->unschedule(schedule_selector(GamingLayer::Hero_Fire));
	//p->m_HeroBulletManager->GetHeroBulletArray()->removeAllObjects();
	p->m_HeroBulletManager->removeAllChildrenWithCleanup(true);
	*/

	/*
	//ȡ�������л�����Ϊ��ǰ������ʾ��������Ӻ���
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


