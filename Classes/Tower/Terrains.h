#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
class Terrains : public Sprite {

public:
	virtual bool init();
	static Terrains* createTerrain();
	CREATE_FUNC(Terrains);

	//基座的功能函数
	void showTowerPanleLayer();
	void hideTowerPanleLayer();
	void showTowerInfo() {}
	void hideTowerInfo() {}

	CC_SYNTHESIZE(bool, isShow, IsShow);
	CC_SYNTHESIZE(bool, isBuilt, IsBuilt);
	void updateTerrain(char* name);

private:
	void initEvent();
	void initUI();

	//三个炮塔的图标
	cocos2d::ui::Button* bottleIcon;
	cocos2d::ui::Button* sunFlowerIcon;
	cocos2d::ui::Button* icedStarIcon;
};