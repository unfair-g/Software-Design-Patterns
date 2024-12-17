#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

/*怪物的多种状态*/
typedef enum {
	None,Death,Bite,Burn,Ice,Boom,IceBoom
} state;

/*怪物的类型*/
typedef enum {
	normal, fly, big
} monsterName;

/*怪物基类*/
class Monster:public cocos2d::Sprite {
public:
	CREATE_FUNC(Monster);
	
	Monster* createMonster();

	Monster();

	virtual bool init() override;

	void loadPoint();

	void update(float dt) override;

	void getHurt(int hurt, state effect = None);          //接受伤害

	CC_SYNTHESIZE(bool, chosen, Chosen);                  //是否被选中

	bool IsReverse;                                       //是否转身

protected:

	CC_SYNTHESIZE(float, maxHp, Maxhp);                  //最大血量
	CC_SYNTHESIZE(float, Hp, Hp);                        //当前血量
	CC_SYNTHESIZE(int,speed,speed);                      //当前移动速度
	int normalspeed;                                     //正常移动速度
	int slowspeed;                                       //减速后移动速度
	CC_SYNTHESIZE(int, money, Money);                    //返回金币数
	float walklong;                                      //一次移动的距离
	float width;                                         //怪物宽度，方便设置血条位置
	int height;                                          //怪物高度，方便设置血条位置
	size_t pointCounter;                                 //记录怪物当前走到的位置
	CC_SYNTHESIZE(cocos2d::ProgressTimer*, hpbar, Hpbar);     //血条
	cocos2d::Sprite* hpbar_bg;                                //血条背景
	std::vector<cocos2d::Point> next;                         //下一步移动到的位置
	cocos2d::Vec2 nextPoint();                                //获取下一步位置
	cocos2d::Vec2 tmp;                                        //暂存下一步位置
	CC_SYNTHESIZE(cocos2d::Vec2,current,Current);             //当前位置
	CC_SYNTHESIZE(state, State, nextState);                   //将要改变的状态
	CC_SYNTHESIZE(bool, IsEffect, Effect);                    //是否受到攻击影响
	 
	void InitHpbar();                       //初始化血条

	void runNextPoint();                    //移动到下一个位置

	void birthAnimation();                  //出生动画

	void killAnimation();                   //死亡动画

	void attackAnimation();                 //被攻击的动画

	void reverseHpbar();                    //翻转血条

	void InitEvent();                 

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event); 

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

class NormalMonster :public Monster {
public:
	static NormalMonster* createMonster();

	virtual bool init();

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
