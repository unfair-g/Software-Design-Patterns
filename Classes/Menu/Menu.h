#pragma once
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"MAP/DesertMap.h"
#include"MAP/SkyMap.h"

/*游戏内菜单*/
class ChooseMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(ChooseMenu);
private:
	bool InitUI();

	void InitEvent();

	cocos2d::ui::Button* restartButton;             //重新开始按钮
	cocos2d::ui::Button* returnButton;              //返回选关界面按钮
};

/*结算菜单*/
class OverMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createMenu(bool IsWin,int max,int current);

	CREATE_FUNC(OverMenu);

private:
	bool Win;                                 //是否胜利

	int maxWave;                              //最大波数

	int wave;                                 //当前波数

	cocos2d::ui::Button* returnButton;        //返回选关界面按钮
	cocos2d::ui::Button* continueButton;      //继续游戏按钮

	bool InitMenu();

	void InitUI();

	void Result();                           //设置游戏结果

	void InitEvent();

};