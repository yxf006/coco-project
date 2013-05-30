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


