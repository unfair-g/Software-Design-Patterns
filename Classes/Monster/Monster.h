#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

typedef enum {
	None,Death,Bite,Burn,Ice,Boom,IceBoom
} state;

typedef enum {
	normal, fly, big
} monsterName;

class Monster:public cocos2d::Sprite {
public:
	CREATE_FUNC(Monster);
	
	Monster* createMonster();

	Monster();

	virtual bool init() override;

	void loadPoint();

	void update(float dt) override;

	void getHurt(int hurt, state effect = None);

	CC_SYNTHESIZE(bool, chosen, Chosen);

	bool IsReverse;

protected:

	CC_SYNTHESIZE(float, maxHp, Maxhp);                  //最大血量
	CC_SYNTHESIZE(float, Hp, Hp);                      //当前血量
	CC_SYNTHESIZE(int,speed,speed);                                         //速度
	int normalspeed;
	int slowspeed;                                     //减速后速度
	CC_SYNTHESIZE(int, money, Money);                  //金币数
	float walklong;             //一次移动的距离
	int width;
	int height;                 //高度，方便设置血条高度
	size_t pointCounter;
	CC_SYNTHESIZE(cocos2d::ProgressTimer*, hpbar, Hpbar);     //血条
	cocos2d::Sprite* hpbar_bg;         //血条背景
	std::vector<cocos2d::Point> next;
	cocos2d::Vec2 nextPoint();
	cocos2d::Vec2 tmp;         //下一步坐标
	CC_SYNTHESIZE(cocos2d::Vec2,current,Current);      //当前坐标
	bool isReverse;
	CC_SYNTHESIZE(state, State, nextState);

	CC_SYNTHESIZE(bool, IsEffect, Effect);

	void InitHpbar();

	void runNextPoint();

	void birthAnimation();

	void killAnimation();

	void attackAnimation();

	void reverseHpbar();

	void InitEvent();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

class NormalMonster :public Monster {
public:
	static NormalMonster* createMonster();

	virtual bool init();

	//void update(float dt);

	void InitAnimation();

	CREATE_FUNC(NormalMonster);
};

class FlyMonster :public Monster {
public:
	static FlyMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(FlyMonster);
};

class BigMonster :public Monster {
public:
	static BigMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(BigMonster);
};
