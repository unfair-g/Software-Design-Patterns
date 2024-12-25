#pragma once

#include"cocos2d.h"
#include"Monster/Monster.h"
#include"MAP/MAP.h"
#include"Tower/Tower.h"

// Refactored with Singleton Pattern
class GameManager {
private:
	GameManager();									// Make the constructor private, allowing only static methods of the class to invoke it.

	static GameManager* gameManager;				// Private static member variable, used to save the singleton instance.

public:
	GameManager(GameManager& other) = delete;		// GameManager should not be cloneable.

	void operator=(const GameManager&) = delete;		// GameManager should not be assignable.

	static GameManager* getGame();                 // ��ȡ��ǰ��Ϸ����Ϣ

	void init();

	void setResult();                             //���ñ�����Ϸ�Ľ��

	int getResult(int level) const;                     //��ö�Ӧ�ؿ��Ľ��

	~GameManager();

	cocos2d::Vector<Monster*> currentMonster;            //��ǰ��Ϸ���Ĺ���

	int Money;                                    //��ǰ��Ϸ��Ǯ��

	int Life;                                     //��ǰ��Ϸ�ܲ�������ֵ

	int currentLevel;                             //��ǰ�ؿ���

	int maxLevel;                                 //���ؿ���

	int level[2];                                 //��¼�ؿ��Ƿ�ʤ��

};