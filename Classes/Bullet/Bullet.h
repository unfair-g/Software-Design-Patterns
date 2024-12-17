#pragma once
#include "cocos2d.h"
#include"Monster/Monster.h"
USING_NS_CC;

/*子弹的基类*/
class Bullet : public Sprite
{
public:

	CREATE_FUNC(Bullet);

protected:

	virtual bool init();

	int speed;              //子弹飞行速度

	virtual void shoot() {};//子弹攻击动画

};

/*瓶子炮的子弹类*/
class BottleBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(BottleBullet);
	void shoot(int level);
};

/*冰星星的子弹类*/
class StarBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(StarBullet);
	void shoot(int level);

};