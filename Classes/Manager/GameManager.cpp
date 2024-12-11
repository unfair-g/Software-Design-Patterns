#include"Manager/GameManager.h"
#include"MAP/SkyMap.h"
#include"MAP/DesertMap.h"
USING_NS_CC;
using namespace cocos2d::ui;

static GameManager* instance;

GameManager::GameManager() {

	level[0] = 0;

	level[1] = 0;

}

void GameManager::init() {

	currentMonster.clear();

	currentTower.clear();

	Money = 0;

	Life = 10;

}

GameManager* GameManager::getGame() {

	if (instance == NULL)
		instance = new GameManager();

	return instance;

}

void GameManager::setResult() {
	if (Life == 10)
		level[currentLevel - 1] = 3;
	else if (Life >= 4) {
		if (level[currentLevel - 1] < 2)
			level[currentLevel - 1] = 2;
	}
	else if (Life > 0) {
		if (level[currentLevel - 1] < 1)
			level[currentLevel - 1] = 1;
	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_1", level[currentLevel - 1]);
}

int GameManager::getResult(int currentlevel) {

	return level[currentlevel - 1];

}

GameManager::~GameManager() {
	delete instance;
}