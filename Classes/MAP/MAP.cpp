#include"MAP/MAP.h"
#include"Manager/GameManager.h"
#include"Monster/Monster.h"
#include"Menu/Menu.h"
#include "Tower/TouchLayer.h"
#include "Manager/SoundManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

/*初始化怪物*/
void MAP::addWaves(float dt) {

	if (wave < maxWave - 1 && IsEnd && GameManager::getGame()->currentMonster.size() == 0) {
		IsStart = true;
		IsEnd = false;
		wave++;
		setNumber((wave + 1) / 10, number_5, yellow);
		setNumber((wave + 1) % 10, number_6, yellow);
		if (wave == 0)
			schedule(schedule_selector(MAP::addMonsters), 1.0f, waveMonster.at(wave).size(), 0);
		else
			schedule(schedule_selector(MAP::addMonsters), 1.0f, waveMonster.at(wave).size(), 3.0f);
	}

}

void MAP::addMonsters(float dt) {
	if (MonsterNum < waveMonster.at(wave).size()) {
		Monster* monster = NULL;
		switch (waveMonster.at(wave).at(MonsterNum)) {
		case(normal):
			monster = NormalMonster::createMonster();
			break;
		case(fly):
			monster = FlyMonster::createMonster();
			break;
		case(big):
			monster = BigMonster::createMonster();
			break;
		default:
			break;
		}
		monster->setPosition(begin);
		monster->setMaxhp(monster->getMaxhp() + 50 * wave);
		monster->setHp(monster->getMaxhp());
		monster->setspeed(monster->getspeed() + 2 * wave);
		addChild(monster);
		GameManager::getGame()->currentMonster.pushBack(monster);
		MonsterNum++;
	}
	else {
		MonsterNum = 0;
		IsEnd = true;
	}
}

void MAP::addMoney(int money, Vec2 pos) {

	char namesize[30] = { 0 };
	sprintf(namesize, "MAP/money_%d.png", money);
	auto add = Sprite::create(namesize);
	add->setPosition(pos);
	addChild(add);

	add->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(0, 50)),
		CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParentAndCleanup, add, true)), NULL));

}

void MAP::setNumber(int num, Sprite* pos, int color) {

	pos->setVisible(true);
	char namesize[40] = { 0 };
	if (color == white)
		sprintf(namesize, "Num/numWhite_%d.png", num);
	else
		sprintf(namesize, "Num/numYellow_%d.png", num);
	pos->setTexture(namesize);

}

void MAP::update(float dt) {

	int money = GameManager::getGame()->Money;
	currentLife = GameManager::getGame()->Life;

	if (currentLife <= 0)
		GameOver(false);
	else if (wave == maxWave - 1 && IsEnd && GameManager::getGame()->currentMonster.empty())
		GameOver(true);

	if (money >= 10000) {
		setNumber(9, number_1);
		setNumber(9, number_2);
		setNumber(9, number_3);
		setNumber(9, number_4);
	}
	else if (money >= 1000) {
		setNumber(money / 1000, number_1);
		setNumber((money % 1000) / 100, number_2);
		setNumber((money % 100) / 10, number_3);
		setNumber(money % 10, number_4);
	}
	else if (money >= 100) {
		setNumber(money / 100, number_1);
		setNumber((money % 100) / 10, number_2);
		setNumber(money % 10, number_3);
		number_4->setVisible(false);
	}
	else if (money >= 10) {
		setNumber(money / 10, number_1);
		setNumber(money % 10, number_2);
		number_3->setVisible(false);
		number_4->setVisible(false);
	}
	else {
		setNumber(money, number_1);
		number_2->setVisible(false);
		number_3->setVisible(false);
		number_4->setVisible(false);
	}

	if (currentLife != lastLife) {
		if (currentLife < lastLife)
			carrot->BiteCarrot(currentLife);
		else
			carrot->setLife(currentLife);
		lastLife = currentLife;
	}

}

void MAP::InitMap() {

	MonsterNum = 0;

	currentLife = lastLife = 10;

	wave = -1;

	IsStart = false;
	IsEnd = true;

	Corner = tiledmap->getObjectGroup("Corner");
	Object = tiledmap->getObjectGroup("Object");
	Point = tiledmap->getObjectGroup("Point");
	MyTerrain = tiledmap->getObjectGroup("Tower");

	InitNumber();

	InitUI();

	InitEvent();

	scheduleUpdate();

	beginAnimation();

	auto touchLayer = TouchLayer::createTouchLayer();
	addChild(touchLayer);

	SoundManager::StopBackgroundMusic();
}

void MAP::Count(int i) {

	auto fadein = FadeIn::create(0);
	auto fadeout = FadeOut::create(0);
	auto growBig = ScaleBy::create(0.5f, 1.5);
	auto growSmall = growBig->reverse();
	auto oneCount = Sequence::create(fadein, growBig, growSmall, fadeout, NULL);

	if (i >= 0) {
		if (i > 0)
			SoundManager::PlayCountMusic();
		else
			SoundManager::PlayGoMusic();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Vec2 middle = Vec2(origin.x + 568, origin.y + 320);

		char namesize[50] = { 0 };
		sprintf(namesize, "MAP/Begin/count%d.png", i);
		auto number = Sprite::create(namesize);
		number->setPosition(middle);
		addChild(number);
		number->runAction(Sequence::create(oneCount, CallFuncN::create(CC_CALLBACK_0(MAP::Count, this, --i)), NULL));
	}
	else {
		schedule(schedule_selector(MAP::addWaves), 1.0f);
		getChildByName("BG")->removeFromParent();
		SoundManager::PlayMapMusic();
	}
}

void MAP::beginAnimation() {

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 middle = Vec2(origin.x + 568, origin.y + 320);

	auto BG = Sprite::create("MAP/Begin/BG.png");
	BG->setPosition(middle);
	addChild(BG);
	BG->setName("BG");

	Count(3);

}

bool MAP::InitUI() {

	/*添加菜单按钮*/
	ValueMap menu = Object->getObject("menuButton");               //通过对象名字读取一个object
	float x = menu["x"].asFloat();                                 //获取该对象在地图上的x坐标
	float y = menu["y"].asFloat();                                 //获取该对象在地图上的y坐标

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png", "");             //创建按钮
	menuButton->setPosition(Vec2(x, y));                           //放到对象位置
	menuButton->setPressedActionEnabled(true);
	addChild(menuButton, 1);
	if (menuButton == nullptr)
		return false;


	/*添加暂停按钮*/
	ValueMap stop = Object->getObject("stopButton");
	x = stop["x"].asFloat();
	y = stop["y"].asFloat();

	stopButton = Button::create("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
	stopButton->setPosition(Vec2(x, y));
	stopButton->setPressedActionEnabled(true);
	addChild(stopButton, 1);
	if (stopButton == nullptr)
		return false;

	/*添加继续游戏按钮*/
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	continueButton = Button::create("MAP/continueBUtton_normal.png", "MAP/continueButton_pressed.png");
	continueButton->setPosition(Vec2(origin.x + 565, origin.y + 395));
	continueButton->setVisible(false);//初始设置为不可见
	this->addChild(continueButton, 2);
	if (continueButton == nullptr)
		return false;

	/*添加怪物波数*/
	ValueMap text = Object->getObject("text");
	x = text["x"].asFloat();
	y = text["y"].asFloat();
	auto TEXT = Sprite::create("MAP/TEXT.png");
	TEXT->setPosition(Vec2(x, y));
	addChild(TEXT, 0);

	/*添加怪物出生点*/
	ValueMap birth = Object->getObject("birth");
	x = birth["x"].asFloat();
	y = birth["y"].asFloat();
	begin = Vec2(x, y);

	birthPlace = Sprite::create("MAP/SKY/birth.png");
	birthPlace->setPosition(x, y);
	addChild(birthPlace);
	if (birthPlace == nullptr)
		return false;

	/*添加萝卜*/
	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();

	carrot = Carrot::create();
	carrot->setPosition(x, y + 80);
	addChild(carrot, 1);
	carrot->setName("carrot");
	if (carrot == nullptr)
		return false;

	return true;
}

void MAP::InitEvent() {
	static int count = 0;//检测按下暂停按钮时的状态
	/*初始化菜单按钮*/
	menuButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			chooseMenu = ChooseMenu::createLayer();
			Director::getInstance()->pause();
			addChild(chooseMenu);
			continueButton->setVisible(true);
		}
		});

	/*设置继续游戏按钮*/
	continueButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			chooseMenu->removeFromParent();
			continueButton->setVisible(false);//重新设置为不可见
		}
		});

	//设置暂停按钮
	stopButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			//若为偶数次按下，则暂停动画
			if (count % 2 == 0) {
				stopButton->loadTextures("MAP/pause.png", "MAP/pause.png", "");
				director->stopAnimation();
			}
			//否则，使动画重新开始
			else {
				stopButton->loadTextures("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
				director->startAnimation();
			}
			count++;
		}
		});
}


void MAP::InitNumber() {

	int x, y;

	auto Number = tiledmap->getObjectGroup("Number");
	ValueMap num1 = Number->getObject("number_1");
	x = num1["x"].asFloat();
	y = num1["y"].asFloat();
	number_1 = Sprite::create();
	number_1->setPosition(x, y);
	addChild(number_1);

	ValueMap num2 = Number->getObject("number_2");
	x = num2["x"].asFloat();
	y = num2["y"].asFloat();
	number_2 = Sprite::create();
	number_2->setPosition(x, y);
	addChild(number_2);

	ValueMap num3 = Number->getObject("number_3");
	x = num3["x"].asFloat();
	y = num3["y"].asFloat();
	number_3 = Sprite::create();
	number_3->setPosition(x, y);
	addChild(number_3);

	ValueMap num4 = Number->getObject("number_4");
	x = num4["x"].asFloat();
	y = num4["y"].asFloat();
	number_4 = Sprite::create();
	number_4->setPosition(x, y);
	addChild(number_4);

	ValueMap num5 = Number->getObject("number_5");
	x = num5["x"].asFloat();
	y = num5["y"].asFloat();
	number_5 = Sprite::create();
	number_5->setPosition(x, y);
	setNumber(0, number_5, yellow);
	addChild(number_5, 1);

	ValueMap num6 = Number->getObject("number_6");
	x = num6["x"].asFloat();
	y = num6["y"].asFloat();
	number_6 = Sprite::create();
	number_6->setPosition(x, y);
	setNumber(0, number_6, yellow);
	addChild(number_6, 1);

	ValueMap num7 = Number->getObject("number_7");
	x = num7["x"].asFloat();
	y = num7["y"].asFloat();
	auto number_7 = Sprite::create();
	number_7->setPosition(x, y);
	addChild(number_7);
	setNumber(maxWave / 10, number_7);

	ValueMap num8 = Number->getObject("number_8");
	x = num8["x"].asFloat();
	y = num8["y"].asFloat();
	auto number_8 = Sprite::create();
	number_8->setPosition(x, y);
	addChild(number_8);
	setNumber(maxWave % 10, number_8);
}

void::MAP::GameOver(bool win) {

	unscheduleAllCallbacks();

	auto monsters = GameManager::getGame()->currentMonster;
	if (!monsters.empty()) {
		for (Vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); it++)
			(*it)->stopAllActions();
	}

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SoundManager::PlayResultMusic(win);
	auto menu = OverMenu::createMenu(win, maxWave, wave);

	addChild(menu, 5);

	menu->setPosition(Vec2(origin.x + 568, origin.y + 320));


}