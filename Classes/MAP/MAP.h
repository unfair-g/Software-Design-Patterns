#pragma once
#include "cocos2d.h"
#include<vector>
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include"Carrot/Carrot.h"
#include "Tower/Terrains.h"

/*两种数字的颜色*/
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

	size_t MonsterNum;      //当前怪物数量

	int currentLife;        //当前萝卜生命值
	int lastLife;           //萝卜变化前的生命值

	bool IsEnd;             //记录每波是否结束

	std::vector<std::vector<int>> waveMonster;                          //存储每波怪物的信息

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, corner, Corner);         //存储改变方向的位置

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, path, Path);             //存储怪物移动路径

	std::vector<cocos2d::Point> terrains;                               //存储基座位置

	void beginAnimation();       //开始动画
	 
	void Count(int i);          //倒计时动画

	void InitMap();             //初始化地图

	virtual void loadPath() { }            //读取怪物路径

	virtual void loadWave() { }            //读取怪物信息

	bool InitUI();              //初始化UI界面，包括菜单按键和暂停按键以及怪物出生点

	void InitWave();            //初始化怪物波数和每波的怪物类型

	void InitEvent();           //添加监听器

	void InitNumber();          //初始化数字

	virtual void addWaves(float dt);              //加载一波怪物

	virtual void addMonsters(float dt);           //加载每个怪物

	virtual void addTerrains() { }

	void addMoney(int m, cocos2d::Vec2 pos);      //怪物死后在对应位置显示返回钱数

	static void setNumber(int num, cocos2d::Sprite* pos, int color = white);           //设置在对应位置显示的数字

	void update(float dt);                        //刷新钱数和萝卜生命值

	void GameOver(bool win);                      //游戏结束后根据结果调用不同的OverMenu

	cocos2d::TMXTiledMap* tiledmap;               //瓦片地图
	cocos2d::TMXObjectGroup* Object;              //数字位置、怪物出生点位置、萝卜位置、按钮位置
	cocos2d::TMXObjectGroup* Corner;              //路径拐角的位置
	cocos2d::TMXObjectGroup* Point;               //路径每点的位置
	cocos2d::TMXObjectGroup* MyTerrain;           //基座的位置

	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
	cocos2d::ui::Button* continueButton;

	cocos2d::Sprite* number_1;                    //金钱千位
	cocos2d::Sprite* number_2;                    //金钱百位
	cocos2d::Sprite* number_3;                    //金钱十位
	cocos2d::Sprite* number_4;                    //金钱个位
	cocos2d::Sprite* number_5;                    //当前波数十位
	cocos2d::Sprite* number_6;                    //当前波数个位

	cocos2d::Sprite* birthPlace;                  //怪物出生点
	Carrot* carrot;                               //萝卜

	CC_SYNTHESIZE(cocos2d::Vec2, begin, BirthPlace);    //出生点位置
	cocos2d::Layer* chooseMenu;                         //菜单界面
};