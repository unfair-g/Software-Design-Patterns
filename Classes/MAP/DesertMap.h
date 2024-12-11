#pragma once
#include"MAP/MAP.h"
#include "Tower/Terrains.h"
class DesertMap :public MAP {
public:
	static DesertMap* createGame();

	CREATE_FUNC(DesertMap);
private:
	const int towerNum = 9;

	void loadPath();

	void loadWave();

	virtual bool init();

	void addTerrains() override;

};