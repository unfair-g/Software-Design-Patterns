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

//����¼�����
void TouchLayer::initEvent()
{
	touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	touchlistener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
}

//�Ե������λ�ø�����ʾ
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
	Point pos = touch->getLocation();//�õ�����λ��

	//�������λ�ã�����������Ϣ��ѡ�ڽ���
	for (size_t i = 0; i < map->terrain.size(); i++) {
		auto element = map->terrain[i];
		//��������ʾ��Ϣ��������
		//Refactored with State Pattern
		if (element->getState()->getIsShow() == true) {
			element->hideInfo();
			return;
		}
	}

	//��������˻���λ�ã�����״̬��Ϣչʾ��ͬ���
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

	//����Ƿ�㵽���ܲ�����
	auto carrot = map->getChildByName("carrot");
	Rect rect = carrot->getBoundingBox();

	//�������λ�ô�����ʾ
	if (!isRightPlace && !rect.containsPoint(pos))
		addWrongPlace(pos);

}