#pragma once
#include"MAP/MAP.h"
#include "Tower/Terrains.h"

class DesertMap :public MAP {
public:
	static DesertMap* createGame();         //创建地图

	CREATE_FUNC(DesertMap);
private:
	const int towerNum = 9;                 //可以放置的炮塔数量

	void loadPath();                        //装载怪物路径

	void loadWave();                        //装载每波怪物的数量和类型

	virtual bool init();                    //初始化

	void addTerrains() override;            //装载基座

};