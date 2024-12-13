#include"Carrot/Carrot.h"
#include"MAP/MAP.h"
#include"Manager/GameManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

bool Carrot::init() {

	if (!Sprite::init())
		return false;

	count = 0;
	Life = 10;
	isUpdateMenuShown = false;
	this->setTexture("Carrot/hlb1_10.png");
	life = Sprite::create("Carrot/life_10.png");
	this->addChild(life);
	life->setPosition(Vec2(80, -20));

	updateButton = Button::create("Money/update_180.png");
	updateButton->setVisible(false);
	auto size = this->getContentSize();
	updateButton->setPosition(Vec2(size.width / 2, size.height / 2) + Vec2(0, 50));
	this->addChild(updateButton);

	initEvent();

	schedule(schedule_selector(Carrot::shakeAnimation), 5.0f);

	return true;
}

void Carrot::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Carrot::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Carrot::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	updateButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (GameManager::getGame()->Money >= 180 && count++ < 2)
				updateCarrot();
			if (count >= 2) {
				updateButton->setPressedActionEnabled(false);
				updateButton->loadTextures("Money/update_max.png", "Money/update_max.png", "");
			}
		}
		});

}

void Carrot::updateCarrot()
{
	setLife(Life + 1);
	GameManager::getGame()->Money -= 180;
	isUpdateMenuShown = false;
	updateButton->setVisible(false);
}

bool Carrot::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Carrot::onTouchEnded(Touch* touch, Event* event)
{
	//转换坐标系
	Point locationInNode = convertTouchToNodeSpace(touch);
	Size size = getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		if (isUpdateMenuShown) {
			isUpdateMenuShown = false;
			updateButton->setVisible(false);
		}
		else
			showUpdateMenu();
	}
	else {
		isUpdateMenuShown = false;
		updateButton->setVisible(false);
	}
}

void Carrot::showUpdateMenu()
{
	isUpdateMenuShown = true;
	updateButton->setVisible(true);
	if (GameManager::getGame()->Money < 180 && count < 2)
		updateButton->loadTextures("Money/less_180.png", "Money/less_180.png", "");
	else if (GameManager::getGame()->Money > 180 && count < 2)
		updateButton->loadTextures("Money/update_180.png", "Money/update_180.png", "");
}

void Carrot::setLife(int n) {

	Life = n;
	stopAllActions();
	char namesize[20] = { 0 };

	sprintf(namesize, "Carrot/life_%d.png", n);
	life->setTexture(namesize);

	sprintf(namesize, "Carrot/hlb1_%d.png", n);
	setTexture(namesize);


}

void Carrot::BiteCarrot(int n) {

	char namesize[20] = { 0 };
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MAP/smoke_%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	auto bite = Animate::create(animation);
	runAction(Sequence::create(bite, CallFuncN::create(CC_CALLBACK_0(Carrot::setLife, this, n)), NULL));

}

void Carrot::shakeAnimation(float dt) {

	if (Life >= 10) {
		auto animation = Animation::create();

		char namesize[25] = { 0 };
		for (int i = 10; i <= 21; i++) {
			sprintf(namesize, "Carrot/shakehlb1_%d.png", i);
			animation->addSpriteFrameWithFile(namesize);
		}

		animation->addSpriteFrameWithFile("Carrot/hlb1_10.png");
		animation->setLoops(1);
		/*设置两帧间隔时间*/
		animation->setDelayPerUnit(0.1f);

		/*创建动画*/
		auto shake = Animate::create(animation);
		/*对象运行该动画*/

		runAction(shake->clone());

	}
	else
		unschedule(schedule_selector(Carrot::shakeAnimation));

}
