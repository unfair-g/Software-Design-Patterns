#pragma once

#include"cocos2d.h"
#include"Monster/Monster.h"
#include"MAP/MAP.h"
#include"Tower/Tower.h"

class GameManager {
public:

	static GameManager* getGame();                 //获取当前游戏的信息

	void init();

	void setResult();                             //设置本局游戏的结果

	int getResult(int level) const;                     //获得对应关卡的结果

	GameManager();

	~GameManager();

	cocos2d::Vector<Monster*> currentMonster;            //当前游戏存活的怪物

	int Money;                                    //当前游戏的钱数

	int Life;                                     //当前游戏萝卜的生命值

	int currentLevel;                             //当前关卡数

	int maxLevel;                                 //最大关卡数

public:

	int level[2];                                 //记录关卡是否胜利

};
