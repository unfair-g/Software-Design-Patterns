#pragma once
#include "cocos2d.h"
#include"Monster/Monster.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:

	CREATE_FUNC(Bullet);

protected:

	virtual bool init();

	int speed;

	virtual void shoot() {};//¹¥»÷

};

class BottleBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(BottleBullet);
	void shoot(int level);
};

class StarBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(StarBullet);
	void shoot(int level);

};