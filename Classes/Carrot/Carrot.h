#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Carrot :public cocos2d::Sprite {
public:
	CREATE_FUNC(Carrot);

	void setLife(int n);          //根据萝卜生命值改变萝卜形态，n为当前生命值

	void BiteCarrot(int n);       //萝卜被咬后的动画

private:
	int Life;                     //萝卜的生命
	int count;                    //升级次数
	cocos2d::Sprite* life;        //生命条
	cocos2d::ui::Button* updateButton;    //升级按钮
	bool isUpdateMenuShown;               //是否隐藏升级菜单
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void updateCarrot();                  //升级萝卜
	void shakeAnimation(float dt);        //萝卜的抖动动画
	void showUpdateMenu();                //显示升级菜单
	void initEvent();
};