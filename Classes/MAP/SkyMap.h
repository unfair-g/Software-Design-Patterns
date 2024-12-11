#pragma once
#include"Tower/Terrains.h"
#include"MAP/MAP.h"
const int towerNum = 8;
class SkyMap :public MAP {
public:
	static SkyMap* createGame();

	CREATE_FUNC(SkyMap);
private:

	void loadPath();

	void loadWave();

	virtual bool init();

	void addTerrains()override;
};
