#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include "Bullet/Bullet.h"
#include"Tower/Terrains.h"
USING_NS_CC;


class BaseTower : public Sprite
{
public:
	friend class Terrains;

	void buildTower(char* basename,char* towername);

	void buildAnimation(char* basename,char* towername);

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

	int speed;      //子弹速度

	CC_SYNTHESIZE(int, buildMoney, BuildMoney);
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
	CC_SYNTHESIZE(int, sellMoney, sellMoney);//售卖金钱

	bool isUpdateMenuShown;

protected:

	bool onTouchBegan(Touch* touch, Event* event) { return true; };
	void onTouchEnded(Touch* touch, Event* event);
	bool InattackRange(Monster* monster);
	virtual void updateTower() { } //升级防御塔
	float getAngle(Monster* monster);

	void upgradeAnimation();

	void removeAnimation();

	Monster* chosenEnemy;
	cocos2d::ui::Button* upgrade = NULL;
	cocos2d::ui::Button* remove = NULL;
	Sprite* attackRange;
	Sprite* updateSignal = NULL;
};

class Bottle : public BaseTower
{
public:
	CREATE_FUNC(Bottle);

	bool init();

	void update(float dt);

	void initEvent();

private:

	void initData();

	void shootWeapon();

	void attack(float dt);
	
	void updateTower();
};

class Flower : public BaseTower
{
public:
	void initEvent();

	CREATE_FUNC(Flower);

protected:

	bool IsAttack;
	
	bool init();

	void update(float dt);

	void attack(float dt);//攻击

	void initData();

	void updateTower();
};

class Star : public BaseTower
{
public:
	void initEvent();

	CREATE_FUNC(Star);

protected:
	bool init();

	void initData();
private:

	void attackScope();

	void update(float dt);

	void attack(float dt);

	void shootWeapon();

	void updateTower();
};