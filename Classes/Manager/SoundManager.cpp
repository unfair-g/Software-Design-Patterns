#include "Manager/SoundManager.h"
#include <Windows.h>
#include <time.h>

auto audio = SimpleAudioEngine::getInstance();
void SoundManager::PlayBackgroundMusic()
{
	srand(static_cast<unsigned int>(time(NULL)));
	const int a = rand() % 2;
	if (a == 0)
		audio->playBackgroundMusic("Sound/BGMusic1.mp3", true);
	else
		audio->playBackgroundMusic("Sound/BGMusic2.mp3", true);
}

void SoundManager::StopBackgroundMusic()
{
	audio->stopBackgroundMusic();
}

void SoundManager::PlayMapMusic()
{
	audio->playBackgroundMusic("Sound/GameRunning.mp3", true);
}

void SoundManager::PlaySelectMusic()
{
	audio->playEffect("Sound/MainMenu/Select.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayCountMusic()
{
	audio->playEffect("Sound/CountDown.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayGoMusic()
{
	audio->playEffect("Sound/GO.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayBuildMusic()
{
	audio->playEffect("Sound/TowerBulid.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayUpdateMusic()
{
	audio->playEffect("Sound/TowerUpdata.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayRemoveMusic()
{
	audio->playEffect("Sound/TowerSell.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayBottleAttackMusic()
{
	audio->playEffect("Sound/Bottle.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayFlowerAttackMusic()
{
	audio->playEffect("Sound/Sun.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayStarAttackMusic()
{
	audio->playEffect("Sound/Star.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayResultMusic(const int win)
{
	if(!win)
		audio->playEffect("Sound/Lose.mp3", false, 1.0f, 1.0f, 1.0f);
	else
		audio->playEffect("Sound/Perfect.mp3", false, 1.0f, 1.0f, 1.0f);
}

void SoundManager::PlayBiteMusic()
{
	audio->playEffect("Sound/Crash.mp3", false, 1.0f, 1.0f, 1.0f);
}

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

