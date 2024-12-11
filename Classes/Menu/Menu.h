#pragma once
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"MAP/DesertMap.h"
#include"MAP/SkyMap.h"

class ChooseMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(ChooseMenu);
private:
	bool InitUI();

	void InitEvent();

	cocos2d::ui::Button* restartButton;
	//cocos2d::ui::Button* continueButton;
	cocos2d::ui::Button* returnButton;
};

class OverMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createMenu(bool IsWin,int max,int current);

	CREATE_FUNC(OverMenu);

private:
	bool Win;

	int maxWave;

	int wave;

	cocos2d::ui::Button* returnButton;
	cocos2d::ui::Button* continueButton;

	bool InitMenu();

	void InitUI();

	void Result();

	void InitEvent();
};