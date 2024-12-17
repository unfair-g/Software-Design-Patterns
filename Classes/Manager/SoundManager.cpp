#include "Manager/SoundManager.h"
#include <Windows.h>
#include <time.h>
auto audio = SimpleAudioEngine::getInstance();
//播放背景音乐
void SoundManager::PlayBackgroundMusic()
{
	srand(static_cast<unsigned int>(time(NULL)));
	const int a = rand() % 2;
	if (a == 0)
		audio->playBackgroundMusic("Sound/BGMusic1.mp3", true);
	else
		audio->playBackgroundMusic("Sound/BGMusic2.mp3", true);
}

//停止背景音乐
void SoundManager::StopBackgroundMusic()
{
	audio->stopBackgroundMusic();
}

//播放关卡音乐
void SoundManager::PlayMapMusic()
{
	audio->playBackgroundMusic("Sound/GameRunning.mp3", true);
}

//播放按钮音效
void SoundManager::PlaySelectMusic()
{
	audio->playEffect("Sound/MainMenu/Select.mp3", false, 1.0f, 1.0f, 1.0f);
}

//播放倒计时音效
void SoundManager::PlayCountMusic()
{
	audio->playEffect("Sound/CountDown.mp3", false, 1.0f, 1.0f, 1.0f);
}

//播放GO音效
void SoundManager::PlayGoMusic()
{
	audio->playEffect("Sound/GO.mp3", false, 1.0f, 1.0f, 1.0f);
}

//建造音效
void SoundManager::PlayBuildMusic()
{
	audio->playEffect("Sound/TowerBulid.mp3", false, 1.0f, 1.0f, 1.0f);
}

//升级音效
void SoundManager::PlayUpdateMusic()
{
	audio->playEffect("Sound/TowerUpdata.mp3", false, 1.0f, 1.0f, 1.0f);
}

//拆除音效
void SoundManager::PlayRemoveMusic()
{
	audio->playEffect("Sound/TowerSell.mp3", false, 1.0f, 1.0f, 1.0f);
}

//瓶子炮攻击音效
void SoundManager::PlayBottleAttackMusic()
{
	audio->playEffect("Sound/Bottle.mp3", false, 1.0f, 1.0f, 1.0f);
}

//太阳花攻击音效
void SoundManager::PlayFlowerAttackMusic()
{
	audio->playEffect("Sound/Sun.mp3", false, 1.0f, 1.0f, 1.0f);
}

//星星攻击音效
void SoundManager::PlayStarAttackMusic()
{
	audio->playEffect("Sound/Star.mp3", false, 1.0f, 1.0f, 1.0f);
}

//播放结果音效
void SoundManager::PlayResultMusic(const int win)
{
	if(!win)
		audio->playEffect("Sound/Lose.mp3", false, 1.0f, 1.0f, 1.0f);
	else
		audio->playEffect("Sound/Perfect.mp3", false, 1.0f, 1.0f, 1.0f);
}

//萝卜被咬音效
void SoundManager::PlayBiteMusic()
{
	audio->playEffect("Sound/Crash.mp3", false, 1.0f, 1.0f, 1.0f);
}

//怪物死亡音效
void SoundManager::PlayMonsterMusic()
{
	srand(static_cast<unsigned int>(time(NULL)));
	const int a = rand() % 6;
	if (a == 0)
		audio->playEffect("Sound/MonsterSound/Fly162.mp3", false, 1.0f, 1.0f, 1.0f);
	else if (a == 1)
		audio->playEffect("Sound/MonsterSound/Fly163.mp3", false, 1.0f, 1.0f, 1.0f);
	else if (a == 2)
		audio->playEffect("Sound/MonsterSound/Fly361.mp3", false, 1.0f, 1.0f, 1.0f);
	else if (a == 3)
		audio->playEffect("Sound/MonsterSound/Land113.mp3", false, 1.0f, 1.0f, 1.0f);
	else if (a == 4)
		audio->playEffect("Sound/MonsterSound/Land222.mp3", false, 1.0f, 1.0f, 1.0f);
	else if (a == 5)
		audio->playEffect("Sound/MonsterSound/Land232.mp3", false, 1.0f, 1.0f, 1.0f);
}

