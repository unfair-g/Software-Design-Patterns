#pragma once
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class SoundManager {
public:
	static void PlayBackgroundMusic();
	static void StopBackgroundMusic();
	static void PlayMapMusic();
	static void StopMapMusic();
	static void PlaySelectMusic();
	static void PlayCountMusic();
	static void PlayGoMusic();
	static void PlayBuildMusic();
	static void PlayUpdateMusic();
	static void PlayRemoveMusic();
	static void PlayBottleAttackMusic();
	static void PlayFlowerAttackMusic();
	static void PlayStarAttackMusic();
	static void PlayResultMusic(const int win);
	static void PlayBiteMusic();
	static void PlayMonsterMusic();
};