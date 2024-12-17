#include"Manager/GameManager.h"
#include"MAP/SkyMap.h"
#include"MAP/DesertMap.h"
USING_NS_CC;
using namespace cocos2d::ui;

static GameManager* instance;

/*构造函数*/
GameManager::GameManager() {

	level[0] = 0;

	level[1] = 0;

}

/*初始化*/
void GameManager::init() {

	currentMonster.clear();

	Money = 0;

	Life = 10;

}

/*取当前游戏*/
GameManager* GameManager::getGame() {

	if (instance == NULL)                   //无实例时创建一个示例
		instance = new GameManager();

	return instance;

}

/*设置当前游戏的结果*/
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

/*获取对应关卡的结果*/
int GameManager::getResult(int currentlevel) const{

	return level[currentlevel - 1];

}

/*回收内存*/
GameManager::~GameManager() {
	delete instance;
}