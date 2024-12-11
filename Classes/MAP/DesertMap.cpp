#include"MAP/DesertMap.h"
#include"Manager/GameManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

void DesertMap::loadPath() {

	float x, y;

	char namesize[10] = { 0 };
	for (int i = 1; i <= 29; i++) {
		sprintf(namesize, "p%d", i);
		ValueMap point = Point->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		path.push_back(Vec2(x, y));
	}
	for (int i = 1; i <= 2; i++) {
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

DesertMap* DesertMap::createGame() {

	auto desertmap = DesertMap::create();

	return desertmap;

}

void DesertMap::loadWave() {

	std::vector<std::vector<int>> wave = {
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

	for (size_t i = 0; i < wave.size(); i++)
		waveMonster.push_back(wave.at(i));

	maxWave = wave.size();
}

void DesertMap::addTerrains() {
	float x, y;
	char namesize[10] = { 0 };
	for (int i = 1; i <= towerNum; i++) {
		sprintf(namesize, "Tower%d", i);
		ValueMap point = MyTerrain->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		terrains.push_back(Vec2(x, y));
	}
	for (int i = 0; i < towerNum; i++) {
		Terrains* newTerrain = Terrains::createTerrain();
		newTerrain->setPosition(terrains.at(i));
		newTerrain->setTag(i + 999);
		addChild(newTerrain, 0);
		terrain.push_back(newTerrain);
	}
}

bool DesertMap::init() {

	if (!Scene::init())
		return false;

	GameManager::getGame()->init();

	tiledmap = TMXTiledMap::create("MAP/DESERT/TileMap2.tmx");

	addChild(tiledmap, -1);
	if (tiledmap == nullptr)
		return false;

	GameManager::getGame()->Money = 1500;
	GameManager::getGame()->currentLevel = 2;

	loadWave();

	InitMap();

	addTerrains();

	loadPath();

	return true;

}