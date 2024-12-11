#pragma once

#include"cocos2d.h"
#include"Monster/Monster.h"
#include"MAP/MAP.h"
#include"Tower/Tower.h"

class GameManager {
public:

	static GameManager* getGame();

	void init();

	void setResult();

	int getResult(int level);

	GameManager();

	~GameManager();

	cocos2d::Vector<Monster*> currentMonster;

	cocos2d::Vector<BaseTower*> currentTower;

	int Money;

	int Life;

	int currentLevel;

	int maxLevel;

public:

	int level[2];       //记录关卡是否胜利

};
