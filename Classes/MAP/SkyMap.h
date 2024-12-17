#pragma once
#include"Tower/Terrains.h"
#include"MAP/MAP.h"
const int towerNum = 8;
class SkyMap :public MAP {
public:
	static SkyMap* createGame();            //创建地图

	CREATE_FUNC(SkyMap);
private:
	 
	void loadPath();                       //装载怪物移动路径

	void loadWave();                       //装载每波怪物信息

	virtual bool init();

	void addTerrains()override;           //装载基座
};
