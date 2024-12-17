#include"MAP/SkyMap.h"
#include"Manager/GameManager.h"
#include<vector>
#include "Tower/Terrains.h"
#include "Manager/SoundManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

/*装载怪物移动路径*/
void SkyMap::loadPath() {

	float x, y;

	char namesize[10] = { 0 };

	for (int i = 1; i <= 41; i++) {
		sprintf(namesize, "p%d", i);
		ValueMap point = Point->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		path.push_back(Vec2(x, y));
	}

	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "corner%d", i);
		ValueMap point = Corner->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		corner.push_back(Vec2(x, y));
	}

	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();
	corner.push_back(Vec2(x, y + 80));

}

/*装载基座*/
void SkyMap::addTerrains()
{
	float x, y;
	char namesize[10] = { 0 };
	for (int i = 1; i <= towerNum; i++) {
		sprintf(namesize, "tower%d", i);
		ValueMap point = MyTerrain->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		terrains.push_back(Vec2(x, y));
	}
	for (int i = 0; i < towerNum; i++) {
		Terrains* newTerrain = Terrains::createTerrain();
		newTerrain->setPosition(terrains.at(i));
		addChild(newTerrain, 0);
		terrain.push_back(newTerrain);
	}
}

/*装载每波怪物信息*/
void SkyMap::loadWave() {
	std::vector<std::vector<int>> skywave = {
		{normal,normal,normal,normal,normal,normal,normal,normal,normal,normal},
		{normal,normal,normal,normal,normal,normal,fly,fly,fly,fly},
		{normal,normal,normal,normal,normal,fly,fly,fly,fly,fly},
		{fly,normal,normal,normal,big,fly,fly,fly,fly,big},
		{fly,fly,fly,fly,fly,fly,fly,fly,big,big},
		{normal,normal,normal,normal,normal,normal,normal,big,big,big},
		{normal,normal,normal,normal,fly,fly,fly,big,big,big},
		{normal,normal,fly,fly,fly,fly,fly,big,big,big},
		{big,big,normal,normal,fly,fly,fly,normal,normal,big},
		{big,big,fly,fly,fly,fly,fly,big,big,big},
	};

	for (size_t i = 0; i < skywave.size(); i++)
		waveMonster.push_back(skywave.at(i));

	maxWave = skywave.size();
}

SkyMap* SkyMap::createGame() {

	auto skymap = SkyMap::create();
	return skymap;

}

bool SkyMap::init() {
	if (!Scene::init())
		return false;

	GameManager::getGame()->init();                      //初始化GameManager

	tiledmap = TMXTiledMap::create("MAP/SKY/TileMap1.tmx");           //加载瓦片地图

	addChild(tiledmap, -1);
	if (tiledmap == nullptr)
		return false;

	GameManager::getGame()->Money = 1200;                //初始金钱数
	GameManager::getGame()->currentLevel = 1;            //当前关卡数

	loadWave();

	InitMap();

	addTerrains();

	loadPath();

	return true;

}
