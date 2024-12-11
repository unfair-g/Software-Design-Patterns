#include"Menu/Menu.h"
#include"MAP/MAP.h"
#include"Manager/GameManager.h"
#include "Manager/SoundManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

Layer* ChooseMenu::createLayer() {
	return ChooseMenu::create();
}

bool ChooseMenu::init() {
	if (!Layer::init())
		return false;

	InitUI();

	InitEvent();

	return true;
}

bool ChooseMenu::InitUI() {

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*添加菜单背景*/
	Sprite* choosemenu = Sprite::create("MAP/Menu.png");
	choosemenu->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(choosemenu, 1);
	if (choosemenu == nullptr)
		return false;

	/*添加重新开始按钮*/
	restartButton = Button::create("MAP/restartButton_normal.png", "MAP/restartButton_pressed.png");
	restartButton->setPosition(Vec2(origin.x + 560, origin.y + 325));
	this->addChild(restartButton, 2);
	if (restartButton == nullptr)
		return false;

	/*添加选择关卡按钮*/
	returnButton = Button::create("MAP/returnButton_normal.png", "MAP/returnButton_pressed.png");
	returnButton->setPosition(Vec2(origin.x + 558, origin.y + 255));
	this->addChild(returnButton, 2);
	if (returnButton == nullptr)
		return false;

	return true;
}

void ChooseMenu::InitEvent() {
	/*设置重新开始按钮*/
	restartButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			SoundManager::StopBackgroundMusic();
			SoundManager::PlayMapMusic();
			Director::getInstance()->popScene();
			if (GameManager::getGame()->currentLevel == 1)
				Director::getInstance()->pushScene(SkyMap::createGame());
			else
				Director::getInstance()->pushScene(DesertMap::createGame());

		}
		});

	/*设置返回按钮*/
	returnButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			SoundManager::StopBackgroundMusic();
			SoundManager::PlayBackgroundMusic();
			Director::getInstance()->popScene();

		}
		});

}

Layer* OverMenu::createMenu(bool IsWin, int max,int current) {

	OverMenu* menu = OverMenu::create();

	menu->Win = IsWin;

	menu->maxWave = max;

	if (IsWin)
		menu->wave = current + 1;
	else
		menu->wave = current;

	menu->InitMenu();

	return menu;

}

bool OverMenu::InitMenu() {

	if (!Layer::init())
		return false;

	char namesize[15] = { 0 };
	if (Win)
		sprintf(namesize, "MAP/win.png");
	else
		sprintf(namesize, "MAP/lose.png");

	auto bg = Sprite::create(namesize);

	addChild(bg, -1);
	bg->setName("bg");

	InitUI();

	InitEvent();

	GameManager::getGame()->setResult();

	return true;

}

void OverMenu::Result() {

	Size size = getChildByName("bg")->getContentSize();

	int life = GameManager::getGame()->Life;

	auto bg = getChildByName("bg");

	auto result = Sprite::create();

	result->setPosition(size.width / 2 - 5, size.height);

	bg->addChild(result);

	if (life >= 10)
		result->setTexture("MAP/carrot3.png");
	else if (life >= 4)
		result->setTexture("MAP/carrot2.png");
	else
		result->setTexture("MAP/carrot1.png");

}

void OverMenu::InitUI() {

	Vec2 adjust;

	if (Win) {         //调整差距
		adjust = Vec2(12, 10);
		Result();
	}
	else
		adjust = Vec2(0, 0);

	/*添加选择关卡按钮*/
	returnButton = Button::create("MAP/returnButton_normal.png", "MAP/returnButton_pressed.png");
	returnButton->setScale(0.8f);
	returnButton->setPosition(Vec2(-100, -80) + adjust);
	addChild(returnButton);

	/*添加继续游戏按钮或重新开始按钮*/
	if (Win)
		continueButton = Button::create("MAP/continueButton_normal.png", "MAP/continueButton_pressed.png");
	else
		continueButton = Button::create("MAP/restartButton_normal.png", "MAP/restartButton_pressed.png");
	continueButton->setScale(0.8f);
	continueButton->setPosition(Vec2(70, -80) + adjust);
	addChild(continueButton);

	/*添加怪物总波数*/
	auto number_1 = Sprite::create();
	number_1->setPosition(Vec2(40, 15) + adjust);
	addChild(number_1);
	MAP::setNumber(maxWave / 10, number_1);
	auto number_2 = Sprite::create();
	number_2->setPosition(Vec2(60, 15) + adjust);
	addChild(number_2);
	MAP::setNumber(maxWave % 10, number_2);

	/*添加当前怪物波数*/
	auto number_3 = Sprite::create();
	number_3->setPosition(Vec2(-30, 15) + adjust);
	addChild(number_3);
	MAP::setNumber(wave / 10, number_3, yellow);
	auto number_4 = Sprite::create();
	number_4->setPosition(Vec2(0, 15) + adjust);
	addChild(number_4);
	MAP::setNumber(wave % 10, number_4, yellow);

}

void OverMenu::InitEvent() {

	/*设置选择关卡按钮*/
	returnButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			SoundManager::StopBackgroundMusic();
			SoundManager::PlayBackgroundMusic();
			Director::getInstance()->popScene();

		}
		});

	/*设置继续游戏按钮*/
	continueButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			Director::getInstance()->popScene();
			if (GameManager::getGame()->currentLevel < GameManager::getGame()->maxLevel) {

				if (Win)
					Director::getInstance()->pushScene(DesertMap::createGame());
				else
					Director::getInstance()->pushScene(SkyMap::createGame());
			}
			else
				SoundManager::PlayBackgroundMusic();
		}
		});

}