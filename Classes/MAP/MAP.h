#pragma once
#include "cocos2d.h"
#include<vector>
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include"Carrot/Carrot.h"
#include "Tower/Terrains.h"
enum {
	white, yellow
};

class MAP :public cocos2d::Scene {
public:
	std::vector<Terrains*>terrain;
	CREATE_FUNC(MAP);

protected:

	int wave;               //当前波数

	int maxWave;            //最大波数

	size_t MonsterNum;

	int currentLife;
	int lastLife;

	bool IsStart;          //游戏开始

	bool IsEnd;            //游戏结束

	std::vector<std::vector<int>> waveMonster;        //存储每波怪物信息的容器

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, corner, Corner);                          //存储改变方向的位置

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, path, Path);

	std::vector<cocos2d::Point> terrains;

	void beginAnimation();

	void Count(int i);

	void InitMap();             //初始化地图

	virtual void loadPath() { }            //读取怪物路径

	virtual void loadWave() { }            //读取怪物信息

	bool InitUI();              //初始化UI界面，包括菜单按键和暂停按键以及怪物出生点

	void InitWave();            //初始化怪物波数和每波的怪物类型

	void InitEvent();           //添加监听器

	void InitNumber();

	virtual void addWaves(float dt);

	virtual void addMonsters(float dt);

	virtual void addTerrains() { }

	void addMoney(int m, cocos2d::Vec2 pos);

	static void setNumber(int num, cocos2d::Sprite* pos, int color = white);

	void update(float dt);

	void updateMoneyandLife(float dt);

	void GameOver(bool win);

	cocos2d::Vector<Monster*> liveMonster;

	cocos2d::TMXTiledMap* tiledmap;
	cocos2d::TMXObjectGroup* Object;
	cocos2d::TMXObjectGroup* Corner;
	cocos2d::TMXObjectGroup* Point;
	cocos2d::TMXObjectGroup* MyTerrain;

	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
	cocos2d::ui::Button* continueButton;

	cocos2d::Sprite* number_1;
	cocos2d::Sprite* number_2;
	cocos2d::Sprite* number_3;
	cocos2d::Sprite* number_4;
	cocos2d::Sprite* number_5;
	cocos2d::Sprite* number_6;

	cocos2d::Sprite* birthPlace;
	Carrot* carrot;
	CC_SYNTHESIZE(cocos2d::Vec2, begin, BirthPlace);
	cocos2d::Layer* chooseMenu;
};