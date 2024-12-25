#include "Tower/Tower.h"
#include "cocos2d.h"
#include "MAP/MAP.h"
#include <vector>
#include"Manager/GameManager.h"
#include "BUllet/Bullet.h"
#include "Manager/SoundManager.h"
#include<math.h>
using namespace cocos2d::ui;

void BaseTower::buildTower(char* basename,char* towername) {

	buildAnimation(basename,towername);

	addButton(updateMoney, sellMoney);

	initEvent();

}

bool BaseTower::init() {

	if (!Sprite::init())
		return false;

	chosenEnemy = NULL;

	return true;
}

void BaseTower::buildAnimation(char* basename,char* towername) {

	SoundManager::PlayBuildMusic();
	char namesize[30] = { 0 };
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MAP/smoke_%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}
	animation->addSpriteFrameWithFile(towername);

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	auto build = Animate::create(animation);

	getParent()->addChild(attackRange);
	attackRange->setName("attackRange");

	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Sprite::setOpacity, getParent(), 0))
		, build
		, CallFuncN::create(CC_CALLBACK_0(Sprite::setOpacity, getParent(), 225))
		,CallFuncN::create(CC_CALLBACK_0(Terrains::updateTerrain,static_cast<Terrains*>(getParent()),basename))
		,NULL));
}

void BaseTower::upgradeAnimation() {

	SoundManager::PlayUpdateMusic();
	auto upgrade = Sprite::create("MAP/upgrade1.png");
	auto loop = Sprite::create();
	auto animation = Animation::create();
	char namesize[20] = { 0 };
	for (int i = 2; i <= 5; i++) {
		sprintf(namesize, "MAP/upgrade%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	
	auto animate = Animate::create(animation);

	getParent()->addChild(upgrade);
	getParent()->addChild(loop, -2);
	loop->setPosition(getParent()->getContentSize().width / 2, getParent()->getContentSize().height / 3);
	upgrade->setPosition(getParent()->getContentSize().width / 2, getParent()->getContentSize().height);

	loop->runAction(Sequence::create(animate
		,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent,upgrade))
		,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent,loop))
		,NULL));

}

void BaseTower::removeAnimation() {

	SoundManager::PlayRemoveMusic();
	unscheduleAllCallbacks();

	getParent()->setOpacity(0);
	updateSignal->removeFromParent();
	attackRange->removeFromParent();
	upgrade->removeFromParent();
	remove->removeFromParent();

	auto animation = Animation::create();

	char namesize[20] = { 0 };
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MAP/remove%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto remove = Animate::create(animation);

	runAction(Sequence::create(remove
		,CallFuncN::create(CC_CALLBACK_0(BaseTower::sellTower,this))
		,NULL));

}

//展示攻击范围
void BaseTower::showAttackRange()
{
	// 显示攻击范围的圆形精灵
	attackRange->setVisible(true);
	attackRange->setScale(0.1f);
	attackRange->runAction(ScaleTo::create(0.2f, scope));

}

//展示升级页面
void BaseTower::showUpdateMenu() {

	isUpdateMenuShown = true;
	showAttackRange();
	upgrade->setVisible(true);
	remove->setVisible(true);

}

//隐藏升级页面
void BaseTower::hideUpdateMenu() {

	isUpdateMenuShown = false;
	attackRange->setVisible(false);
	upgrade->setVisible(false);
	remove->setVisible(false);

}

bool BaseTower::InattackRange(Monster* monster) {

	Point monsterPos = monster->getParent()->convertToWorldSpace(monster->getPosition());
	Point Pos = getParent()->convertToWorldSpace(getPosition());

	float distance = Pos.distance(monsterPos);

	if (distance < attackRange->getContentSize().width / 2 * scope
		|| distance < attackRange->getContentSize().height / 2 * scope)
		return true;
	else
		return false;

}

float BaseTower::getAngle(Monster* monster) {


	Point to = monster->getParent()->convertToWorldSpace(monster->getPosition());
	Point from = getParent()->convertToWorldSpace(getPosition());

	float y = to.y - from.y;
	float x = to.x - from.x;

	float angle = atan(y / x);
	float degrees = CC_RADIANS_TO_DEGREES(angle);

	if (x > 0 && y > 0)
		return -degrees;
	else if (x > 0 && y < 0)
		return -degrees;
	else if (x < 0 && y>0)
		return -degrees - 180;
	else
		return -degrees - 180;

}

//根据金钱数展示不同图标
void BaseTower::checkMoney(int needMoney)
{
	auto money = GameManager::getGame()->Money;

	char namesize[30] = { 0 };
	if (money < needMoney) {
		sprintf(namesize, "Money/less_%d.png", needMoney);
		upgrade->loadTextures(namesize, namesize, "");
	}
	else {
		sprintf(namesize, "Money/update_%d.png", needMoney);
		upgrade->loadTextures(namesize, namesize, "");
	}
}

//出售防御塔
void BaseTower::sellTower()
{
	auto parent = dynamic_cast<Terrains*>(getParent());
	GameManager::getGame()->Money += sellMoney;
	parent->setTexture("GamePlay/select.png");
	//Refactored with State Pattern
	parent->TransitionTo(new TerrainUnbuiltState);
	removeFromParentAndCleanup(true);
}

void BaseTower::addButton(int needMoney, int removeMoney)
{
	auto nowScene = Director::getInstance()->getRunningScene();
	auto position = getParent()->getPosition();
	//添加升级按钮
	char str1[30] = { 0 };
	sprintf(str1, "Money/update_%d.png", needMoney);
	upgrade = Button::create(str1, str1, "");
	upgrade->setPosition(position + Vec2(0, 70));
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	nowScene->addChild(upgrade, 3);

	//添加拆除按钮
	sprintf(str1, "Money/remove_%d.png", removeMoney);
	remove = Button::create(str1, str1, "");
	remove->setPosition(position + Vec2(0, -70));
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	nowScene->addChild(remove, 3);

	updateSignal = Sprite::create();
	updateSignal->setPosition(this->getParent()->getPosition() + Vec2(0, 50));
	nowScene->addChild(updateSignal);

	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Money/to_update1.png");
	animation->addSpriteFrameWithFile("Money/to_update2.png");

	animation->setLoops(-1);
	animation->setDelayPerUnit(0.4f);

	/*创建动画*/
	auto shake = Animate::create(animation);
	/*对象运行该动画*/
	updateSignal->runAction(shake);
}

//按下炮塔时，显示或关闭升级菜单
void BaseTower::onTouchEnded(Touch* touch, Event* event)
{
	//转换坐标系
	Point locationInNode = convertTouchToNodeSpace(touch);

	Size size = getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		if (isUpdateMenuShown)
			hideUpdateMenu();
		else {
			if (level <= 2)
				checkMoney(updateMoney);
			showUpdateMenu();
		}
	}
	else {
		hideUpdateMenu();
	}
}

/**********************************************************/

bool Bottle::init() {

	if (!BaseTower::init())
		return false;

	behavior = new BottleBehavior();
	behavior->setTower(this);

	initData();

	scheduleUpdate();

	schedule(schedule_selector(Bottle::attack), rate);

	return true;

}

//Refactored with Bridge Pattern
void BottleBehavior::update(float dt) {

	if (tower->getUpdateMoney() <= GameManager::getGame()->Money && !tower->isUpdateMenuShown && tower->getLevel() < 3)
		tower->updateSignal->setOpacity(255);
	else
		tower->updateSignal->setOpacity(0);

	if (GameManager::getGame()->currentMonster.contains(tower->chosenEnemy) == false)
		tower->chosenEnemy = NULL;

	auto monsters = GameManager::getGame()->currentMonster;
	Vector<Monster*>::iterator it = monsters.begin();
	for (; it != monsters.end(); it++) {
		if (tower->InattackRange(*it) && (*it)->getChosen()) {
			tower->chosenEnemy = (*it);
			break;
		}
	}

	/*有攻击目标*/
	if (tower->chosenEnemy) {

		tower->setRotation(tower->getAngle(tower->chosenEnemy));

		if (!tower->InattackRange(tower->chosenEnemy)) {
			tower->chosenEnemy = NULL;
		}

	}
	else {
		if (tower->chosenEnemy == NULL) {
			for (it = monsters.begin(); it != monsters.end(); it++) {
				if (tower->InattackRange(*it)) {
					tower->chosenEnemy = (*it);
				}
			}
		}
	}
}

//Refactored with Bridge Pattern
void BottleBehavior::attack(float dt) {

	if (tower->chosenEnemy != NULL) {

		auto animation = Animation::create();

		char namesize[30] = { 0 };

		sprintf(namesize, "Bottle/Bottle%d1.png", tower->getLevel());
		animation->addSpriteFrameWithFile(namesize);
		sprintf(namesize, "Bottle/Bottle%d2.png", tower->getLevel());
		animation->addSpriteFrameWithFile(namesize);
		sprintf(namesize, "Bottle/Bottle%d3.png", tower->getLevel());
		animation->addSpriteFrameWithFile(namesize);
		sprintf(namesize, "Bottle/Bottle%d1.png", tower->getLevel());
		animation->addSpriteFrameWithFile(namesize);

		animation->setLoops(1);
		animation->setDelayPerUnit(0.1f);

		auto shoot = Animate::create(animation);
		SoundManager::PlayBottleAttackMusic();
		tower->runAction(Sequence::create(shoot
			, CallFuncN::create(CC_CALLBACK_0(Bottle::shootWeapon, dynamic_cast<Bottle*>(this->tower)))
			, NULL));

	}
}

//Refactored with Bridge Pattern
//升级防御塔，更新数据
void BottleBehavior::updateTower()
{
	if (tower->getLevel() == 1) {
		tower->setSellMoney(224);
		GameManager::getGame()->Money -= tower->getUpdateMoney();
		tower->setUpdateMoney(220);
		tower->upgrade->loadTextures("Money/update_220.png", "Money/update_220.png");
		tower->setTexture("Bottle/Bottle21.png");
		tower->remove->loadTextures("Money/remove_224.png", "Money/remove_224.png");
	}
	else if (tower->getLevel() == 2) {
		tower->setSellMoney(432);
		GameManager::getGame()->Money -= tower->getUpdateMoney();
		tower->upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
		tower->setTexture("Bottle/Bottle31.png");
		tower->remove->loadTextures("Money/remove_432.png", "Money/remove_432.png");
		tower->upgrade->setPressedActionEnabled(false);
	}
	if (tower->getLevel() == 1 || tower->getLevel() == 2) {
		tower->setLevel(tower->getLevel() + 1);
		tower->setDamage(tower->getDamage() + 10);
		tower->setRate(tower->getRate() - 0.2f);
		tower->setScope(tower->getScope() + 0.2f);
		tower->setSpeed(tower->getSpeed() + 100);
	}
}

//Refactored with Bridge Pattern
void BottleBehavior::shootWeapon() {

	if (tower->chosenEnemy != NULL) {

		BottleBullet* bullet = BottleBullet::create();

		Point src = tower->chosenEnemy->convertToNodeSpace(tower->getParent()->convertToWorldSpace(tower->getPosition()));

		Point dst = Vec2(tower->chosenEnemy->getContentSize().width / 2, tower->chosenEnemy->getContentSize().height / 2);

		tower->chosenEnemy->addChild(bullet);
		bullet->setPosition(src);
		bullet->setRotation(tower->getAngle(tower->chosenEnemy));

		float dur = src.distance(dst) / tower->getSpeed();

		if (tower->chosenEnemy->IsReverse)
			bullet->setRotation(180 - tower->getRotation());

		bullet->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(BottleBullet::shoot, bullet, tower->getLevel()))
			, MoveTo::create(dur, dst)
			, CallFuncN::create(CC_CALLBACK_0(BottleBullet::removeFromParent, bullet))
			, CallFuncN::create(CC_CALLBACK_0(Monster::getHurt, tower->chosenEnemy, tower->getDamage(), Boom))
			, NULL));

	}

}

void Bottle::initData()
{
	//初始化数据
	level = 1;
	rate = 0.8f;
	scope = 0.8f;
	speed = 300;
	damage = 10;
	buildMoney = 100;
	sellMoney = 80;
	updateMoney = 180;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	attackRange->setPosition(40, 40);
	attackRange->setScale(scope);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;
	GameManager::getGame()->Money -= buildMoney;
}

//添加事件监听器
void Bottle::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Bottle::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Bottle::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (GameManager::getGame()->Money >= updateMoney) {
				upgradeAnimation();
				updateTower();
				hideUpdateMenu();
				unschedule(schedule_selector(Bottle::attack));
				schedule(schedule_selector(Bottle::attack), rate);
				attackRange->setScale(scope);
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			removeAnimation();
		}
		});

}

/**********************************************************/

//Refactored with Bridge Pattern
void FlowerBehavior::update(float dt) {

	if (tower->getUpdateMoney() <= GameManager::getGame()->Money && !tower->isUpdateMenuShown && tower->getLevel() < 3)
		tower->updateSignal->setOpacity(255);
	else
		tower->updateSignal->setOpacity(0);

	if (GameManager::getGame()->currentMonster.contains(tower->chosenEnemy) == false)
		tower->chosenEnemy = NULL;

	/*有攻击目标*/
	if (tower->chosenEnemy) {

		dynamic_cast<Flower*>(tower)->setIsAttack(true);

		if (!tower->InattackRange(tower->chosenEnemy)) {
			tower->chosenEnemy = NULL;
		}

	}
	else {

		auto monsters = GameManager::getGame()->currentMonster;
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			if (tower->InattackRange((*it))) {
				tower->chosenEnemy = (*it);
				break;
			}
		}
		if (it == monsters.end())
			dynamic_cast<Flower*>(tower)->setIsAttack(false);

	}

}

//Refactored with Bridge Pattern
void FlowerBehavior::attack(float dt) {
	auto flower = dynamic_cast<Flower*>(tower);
	if (flower->getIsAttack()) {

		if (flower->getRotation() == 0)
			flower->setRotation(25);
		else
			flower->setRotation(0);

		char namesize[30] = { 0 };
		sprintf(namesize, "Flower/PFlower%d.png", flower->getLevel());

		auto bullet = Sprite::create("Flower/PFlower1.png");
		flower->getParent()->addChild(bullet);
		bullet->setPosition(flower->getParent()->getContentSize().width / 2, flower->getParent()->getContentSize().height / 2);
		SoundManager::PlayFlowerAttackMusic();
		bullet->runAction(Sequence::create(ScaleTo::create(0.3f, flower->getScope() + 1.0f)       //调整攻击动画范围
			, DelayTime::create(0.2f)
			, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet))
			, NULL));

		auto monsters = GameManager::getGame()->currentMonster;
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			if (flower->InattackRange(*it))
				(*it)->getHurt(flower->getDamage(), Burn);
		}
	}
}

//Refactored with Bridge Pattern
//太阳花的升级
void FlowerBehavior::updateTower()
{

	auto parent = dynamic_cast<Terrains*>(tower->getParent());

	if (tower->getLevel() == 1) {
		tower->setSellMoney(336);
		GameManager::getGame()->Money -= tower->getUpdateMoney();
		tower->setUpdateMoney(260);
		tower->upgrade->loadTextures("Money/update_260.png", "Money/update_260.png");
		tower->setTexture("Flower/level2_bg.png");
		tower->remove->loadTextures("Money/remove_336.png", "Money/remove_336.png");
		parent->updateTerrain("Flower/level2.png");
	}
	else if (tower->getLevel() == 2) {
		tower->setSellMoney(560);
		GameManager::getGame()->Money -= tower->getUpdateMoney();
		tower->upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
		tower->setTexture("Flower/level3_bg.png");
		tower->remove->loadTextures("Money/remove_560.png", "Money/remove_560.png");
		tower->upgrade->setPressedActionEnabled(false);
		parent->updateTerrain("Flower/level3.png");
	}

	tower->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);

	if (tower->getLevel() == 1 || tower->getLevel() == 2) {
		tower->setLevel(tower->getLevel() + 1);
		tower->setDamage(tower->getDamage() + 10);
		tower->setRate(tower->getRate() - 0.3f);
		tower->setScope(tower->getScope() + 0.2f);
		tower->setSpeed(tower->getSpeed() + 100);
	}
}

bool Flower::init() {

	if (!BaseTower::init())
		return false;
	
	behavior = new FlowerBehavior();
	behavior->setTower(this);

	initData();

	scheduleUpdate();

	schedule(schedule_selector(Flower::attack), rate);

	return true;
}

void Flower::initData()
{
	//初始化数据
	isAttack = false;
	level = 1;
	rate = 1.5f;
	scope = 0.8f;
	speed = 300;
	damage = 10;
	buildMoney = 180;
	sellMoney = 144;
	updateMoney = 220;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	attackRange->setPosition(40, 40);
	attackRange->setScale(scope);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;
	GameManager::getGame()->Money -= buildMoney;
}

//添加事件监听器
void Flower::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Flower::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Flower::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (GameManager::getGame()->Money >= updateMoney) {
				upgradeAnimation();
				updateTower();
				hideUpdateMenu();
				unschedule(schedule_selector(Flower::attack));
				schedule(schedule_selector(Flower::attack), rate);
				attackRange->setScale(scope);
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			removeAnimation();
		}
		});

}

/****************************************************/

bool Star::init() {

	if (!BaseTower::init())
		return false;

	behavior = new FlowerBehavior();
	behavior->setTower(this);

	initData();

	scheduleUpdate();

	schedule(schedule_selector(Star::attack), rate);

	return true;

}

//Refactored with Bridge Pattern
void StarBehavior::update(float dt) {

	if (tower->getUpdateMoney() <= GameManager::getGame()->Money && !tower->isUpdateMenuShown && tower->getLevel() < 3)
		tower->updateSignal->setOpacity(255);
	else
		tower->updateSignal->setOpacity(0);

	if (GameManager::getGame()->currentMonster.contains(tower->chosenEnemy) == false)
		tower->chosenEnemy = NULL;

	auto monsters = GameManager::getGame()->currentMonster;
	Vector<Monster*>::iterator it = monsters.begin();
	for (; it != monsters.end(); it++) {
		if (tower->InattackRange(*it) && (*it)->getChosen()) {
			tower->chosenEnemy = (*it);
			break;
		}
	}

	/*有攻击目标*/
	if (tower->chosenEnemy) {

		if (!tower->InattackRange(tower->chosenEnemy)) {
			tower->chosenEnemy = NULL;
		}

	}
	else {
		for (it = monsters.begin(); it != monsters.end(); it++) {
			if (tower->InattackRange((*it))) {
				tower->chosenEnemy = (*it);
				break;
			}
		}
	}

}

//Refactored with Bridge Pattern
void StarBehavior::attack(float dt) {

	if (tower->chosenEnemy != NULL) {

		auto rotate = RotateTo::create(0.05f, tower->getAngle(tower->chosenEnemy));
		auto rerotate = RotateTo::create(0.05f, 0);

		tower->runAction(Sequence::create(rotate
			, rerotate
			, CallFuncN::create(CC_CALLBACK_0(Star::shootWeapon, dynamic_cast<Star*>(tower)))
			, NULL));
	}
}

//Refactored with Bridge Pattern
void StarBehavior::updateTower()
{
	auto parent = dynamic_cast<Terrains*>(tower->getParent());

	if (tower->getLevel() == 1) {
		tower->setSellMoney(336);
		GameManager::getGame()->Money -= tower->getUpdateMoney();
		tower->setUpdateMoney(260);
		tower->upgrade->loadTextures("Money/update_260.png", "Money/update_260.png");
		tower->setTexture("Star/level2.png");
		tower->remove->loadTextures("Money/remove_336.png", "Money/remove_336.png");
		parent->updateTerrain("Star/level2_base.png");
	}
	else if (tower->getLevel() == 2) {
		tower->setSellMoney(560);
		GameManager::getGame()->Money -= tower->getUpdateMoney();
		tower->upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
		tower->setTexture("Star/level3.png");
		tower->remove->loadTextures("Money/remove_560.png", "Money/remove_560.png");
		tower->upgrade->setPressedActionEnabled(false);
		parent->updateTerrain("Star/level3_base.png");
	}

	tower->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);

	if (tower->getLevel() == 1 || tower->getLevel() == 2) {
		tower->setLevel(tower->getLevel() + 1);
		tower->setDamage(tower->getDamage() + 10);
		tower->setRate(tower->getRate() - 0.2f);
		tower->setScope(tower->getScope() + 0.2f);
		tower->setSpeed(tower->getSpeed() + 100);
	}
}

//Refactored with Bridge Pattern
void StarBehavior::shootWeapon() {

	if (tower->chosenEnemy != NULL) {

		StarBullet* bullet = StarBullet::create();

		Point src = tower->chosenEnemy->convertToNodeSpace(tower->getParent()->convertToWorldSpace(tower->getPosition()));

		Point dst = Vec2(tower->chosenEnemy->getContentSize().width / 2, tower->chosenEnemy->getContentSize().height / 2);

		tower->chosenEnemy->addChild(bullet);
		bullet->setPosition(src);
		bullet->setRotation(tower->getAngle(tower->chosenEnemy));

		float dur = src.distance(dst) / tower->getSpeed();
		SoundManager::PlayStarAttackMusic();
		bullet->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(StarBullet::shoot, bullet, tower->getLevel()))
			, MoveTo::create(dur, dst)
			, CallFuncN::create(CC_CALLBACK_0(BottleBullet::removeFromParent, bullet))
			, CallFuncN::create(CC_CALLBACK_0(Star::attackScope, dynamic_cast<Star*>(tower)))
			, NULL));
	}
}

void Star::initData()
{
	//初始化数据
	level = 1;
	rate = 1.2f;
	scope = 0.8f;
	speed = 300;
	damage = 10;
	sellMoney = 144;
	buildMoney = 180;
	updateMoney = 220;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	this->setAnchorPoint(Vec2(0.5, 0.5));
	attackRange->setPosition(40, 40);
	attackRange->setScale(scope);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;
	GameManager::getGame()->Money -= buildMoney;
}

//添加事件监听器
void Star::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Star::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Star::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (GameManager::getGame()->Money >= updateMoney) {
				upgradeAnimation();
				updateTower();
				hideUpdateMenu();
				unschedule(schedule_selector(Star::attack));
				schedule(schedule_selector(Star::attack), rate);
				attackRange->setScale(scope);
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			removeAnimation();
		}
		});

}

void Star::attackScope() {

	if (chosenEnemy != NULL) {

		auto monsters = GameManager::getGame()->currentMonster;

		Vector<Monster*>::iterator it = monsters.begin();

		for (; it != monsters.end(); it++) {

			if ((*it) == chosenEnemy)
				chosenEnemy->getHurt(damage, IceBoom);
			else if ((*it)->getPosition().distance(chosenEnemy->getPosition()) <= 100)
				(*it)->getHurt(damage, Ice);

		}
	}

}