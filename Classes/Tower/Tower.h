#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include "Bullet/Bullet.h"
#include"Tower/Terrains.h"
USING_NS_CC;
// Refactored with Bridge Pattern
class BaseTower;
class TowerBehavior {
public:
	virtual ~TowerBehavior() = default;

	virtual void update(float dt) = 0;

	virtual void attack(float dt) = 0;       // 攻击逻辑

	virtual void shootWeapon() {}

	virtual void updateTower() = 0;

	virtual void setTower(BaseTower* tower) { this->tower = tower; }

protected:
	BaseTower* tower = nullptr;  // 行为类持有塔的引用,因为具体的行为需要用到塔的属性
};

// Refactored with Bridge Pattern
class BottleBehavior : public TowerBehavior {
public:
	void update(float dt) override;
	void attack(float dt) override;
	void shootWeapon() override;
	void updateTower()override;
};

// Refactored with Bridge Pattern
class FlowerBehavior : public TowerBehavior {
public:
	void update(float dt) override;
	void attack(float dt) override;
	void updateTower()override;
};

// Refactored with Bridge Pattern
class StarBehavior : public TowerBehavior {
public:
	void update(float dt) override;
	void attack(float dt) override;
	void shootWeapon()override;
	void updateTower()override;
};

class BaseTower : public Sprite
{
public:
	friend class Terrains;

	// Refactored with Bridge Pattern
	void update(float dt) { behavior->update(dt); }

	void shootWeapon() { behavior->shootWeapon(); }

	void buildTower(char* basename, char* towername);

	void buildAnimation(char* basename, char* towername);

	void showUpdateMenu();

	void hideUpdateMenu();

	void showAttackRange();

	void checkMoney(int neddMoney);

	void addButton(int needMoney, int removeMoney);//添加塔的升级和拆除按钮
	virtual void sellTower();//出售防御塔
	virtual bool init();                   //初始化防御塔
	virtual void initEvent() { }

	CC_SYNTHESIZE(int, level, Level);//塔的等级

	CC_SYNTHESIZE(float, scope, Scope);//攻击范围

	CC_SYNTHESIZE(float, rate, Rate);//攻速

	CC_SYNTHESIZE(int, damage, Damage);//攻击力

	CC_SYNTHESIZE(int, speed, Speed);     //子弹速度

	CC_SYNTHESIZE(int, buildMoney, BuildMoney);

	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱

	CC_SYNTHESIZE(int, sellMoney, SellMoney);//售卖金钱

	bool isUpdateMenuShown;

	Monster* chosenEnemy;

	cocos2d::ui::Button* upgrade = NULL;
	cocos2d::ui::Button* remove = NULL;
	Sprite* attackRange;
	Sprite* updateSignal = NULL;

	bool InattackRange(Monster* monster);

	float getAngle(Monster* monster);
protected:
	// Refactored with Bridge Pattern
	// 对具体行为的引用
	TowerBehavior* behavior;

	void attack(float dt) { behavior->attack(dt); }

	void updateTower() { behavior->updateTower(); }

	virtual void initData(){}

	bool onTouchBegan(Touch* touch, Event* event) { return true; };
	void onTouchEnded(Touch* touch, Event* event);

	void upgradeAnimation();

	void removeAnimation();
};

class Bottle : public BaseTower
{
public:
	CREATE_FUNC(Bottle);

private:
	bool init();

	void initEvent();

	void initData()override;

};

class Flower : public BaseTower
{
public:

	CREATE_FUNC(Flower);

private:
	bool init();

	void initEvent();

	void initData()override;

	CC_SYNTHESIZE(bool, isAttack, IsAttack);

};

class Star : public BaseTower
{
public:
	CREATE_FUNC(Star);

	void attackScope();

private:
	bool init();

	void initEvent();

	void initData()override;
};