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

	virtual void attack(float dt) = 0;       // �����߼�

	virtual void shootWeapon() {}

	virtual void updateTower() = 0;

	virtual void setTower(BaseTower* tower) { this->tower = tower; }

protected:
	BaseTower* tower = nullptr;  // ��Ϊ�������������,��Ϊ�������Ϊ��Ҫ�õ���������
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

	void addButton(int needMoney, int removeMoney);//������������Ͳ����ť
	virtual void sellTower();//���۷�����
	virtual bool init();                   //��ʼ��������
	virtual void initEvent() { }

	CC_SYNTHESIZE(int, level, Level);//���ĵȼ�

	CC_SYNTHESIZE(float, scope, Scope);//������Χ

	CC_SYNTHESIZE(float, rate, Rate);//����

	CC_SYNTHESIZE(int, damage, Damage);//������

	CC_SYNTHESIZE(int, speed, Speed);     //�ӵ��ٶ�

	CC_SYNTHESIZE(int, buildMoney, BuildMoney);

	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ

	CC_SYNTHESIZE(int, sellMoney, SellMoney);//������Ǯ

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
	// �Ծ�����Ϊ������
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