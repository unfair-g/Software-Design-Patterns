#include"Manager/GameManager.h"
#include"MAP/SkyMap.h"
#include"MAP/DesertMap.h"
USING_NS_CC;
using namespace cocos2d::ui;
//Refactored with Bridge Pattern
GameManager* GameManager::gameManager = nullptr;

/*���캯��*/
GameManager::GameManager() {

	level[0] = 0;

	level[1] = 0;

}

/*��ʼ��*/
void GameManager::init() {

	currentMonster.clear();

	Money = 0;

	Life = 10;

}

/*ȡ��ǰ��Ϸ*/
// Refactored with Singleton Pattern
GameManager* GameManager::getGame() {

	if (gameManager == nullptr)                   //��ʵ��ʱ����һ��ʾ��
		gameManager = new GameManager();

	return gameManager;

}

/*���õ�ǰ��Ϸ�Ľ��*/
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

/*��ȡ��Ӧ�ؿ��Ľ��*/
int GameManager::getResult(int currentlevel) const{

	return level[currentlevel - 1];

}

/*�����ڴ�*/
GameManager::~GameManager() {
	delete gameManager;
}