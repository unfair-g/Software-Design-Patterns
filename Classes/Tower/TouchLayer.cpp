#include "Tower/TouchLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tower/Tower.h"
#include "MAP/MAP.h"
#include <vector>
USING_NS_CC;
using namespace cocos2d::ui;
TouchLayer* TouchLayer::createTouchLayer()
{
	return TouchLayer::create();
}

bool TouchLayer::init()
{
	if (!Layer::init())
		return false;

	initEvent();

	return true;
}

//添加事件监听
void TouchLayer::initEvent()
{
	touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	touchlistener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
}

//对点击错误位置给出提示
void TouchLayer::addWrongPlace(Point location)
{
	auto wrong = Sprite::create("GamePlay/warning.png");
	wrong->setPosition(location);
	wrong->runAction(Sequence::create(FadeOut::create(0.6f)
		, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, wrong))
		, NULL));
	addChild(wrong);
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void TouchLayer::onTouchEnded(Touch* touch, Event* event)
{
	bool isRightPlace = 0;
	auto map = static_cast<MAP*>(Director::getInstance()->getRunningScene());
	Point pos = touch->getLocation();//得到触摸位置

	//点击其他位置，隐藏炮塔信息或选炮界面
	for (size_t i = 0; i < map->terrain.size(); i++) {
		auto element = map->terrain[i];
		//若存在显示信息，则隐藏
		//Refactored with State Pattern
		if (element->getState()->getIsShow() == true) {
			element->hideInfo();
			return;
		}
	}

	//若点击到了基座位置，根据状态信息展示不同面板
	for (size_t i = 0; i < map->terrain.size(); i++) {
		auto element = map->terrain[i];
		Rect rect = element->getBoundingBox();
		if (rect.containsPoint(pos))
		{
			//Refactored with State Pattern
			element->showInfo();
			isRightPlace = 1;
			return;
		}
	}

	//检测是否点到了萝卜区域
	auto carrot = map->getChildByName("carrot");
	Rect rect = carrot->getBoundingBox();

	//给出点击位置错误提示
	if (!isRightPlace && !rect.containsPoint(pos))
		addWrongPlace(pos);

}