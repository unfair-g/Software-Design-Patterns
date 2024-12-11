#include "Bullet/Bullet.h"
#include "MAP/MAP.h"
#include"Manager/GameManager.h"
bool Bullet::init()
{
	if (!Sprite::init())
		return false;

	return true;
}

bool BottleBullet::init() {

	if (!Sprite::init())
		return false;

	return true;

}

void BottleBullet::shoot(int level) {
	
	auto animation = Animation::create();

	char namesize[30] = { 0 };
	for (int i = 1; i <= 3; i++) {
		sprintf(namesize, "Bottle/PBottle%d%d.png", level, i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto shoot = Animate::create(animation);

	runAction(shoot);

}

bool StarBullet::init() {
	if (!Sprite::init())
		return false;

	return true;
}

void StarBullet::shoot(int level) {

	char namesize[30] = { 0 };
	sprintf(namesize, "Star/PStar%d.png", level);
	setTexture(namesize);
	runAction(RepeatForever::create(RotateBy::create(0.5f, 360)));

}


