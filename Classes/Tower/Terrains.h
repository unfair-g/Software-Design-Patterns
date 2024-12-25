#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
//Refactored with State Pattern
class Terrains;
class TerrainState {
private:
	Terrains* context;

	CC_SYNTHESIZE(bool, isShow, IsShow);

public:
	virtual ~TerrainState() {}

	Terrains* getContext() {
		return this->context;
	}

	void setContext(Terrains* ct) {
		this->context = ct;
	}

	virtual void showInfo() = 0;
	virtual void hideInfo() = 0;
};

class Terrains : public Sprite {
private:
	TerrainState* state = nullptr;

	void initEvent();

	void initUI();

public:
	virtual bool init();
	static Terrains* createTerrain();
	CREATE_FUNC(Terrains);

	void TransitionTo(TerrainState* st);

	//基座的功能函数
	void showInfo() {
		this->state->showInfo();
	}

	void hideInfo() {
		this->state->hideInfo();
	}

	TerrainState* getState() { return state; }

	//三个炮塔的图标
	cocos2d::ui::Button* bottleIcon;
	cocos2d::ui::Button* sunFlowerIcon;
	cocos2d::ui::Button* icedStarIcon;

	void updateTerrain(char* name);
};

class TerrainUnbuiltState :public TerrainState {
public:
	void showInfo() override;
	void hideInfo() override;
};

class TerrainBuiltState :public TerrainState {
public:
	void showInfo() override { isShow = true; };
	void hideInfo() override { isShow = false; };
};
