#include "Scene/MainScene.h"
#include "Manager/SoundManager.h"
#include "Scene/SelectLevelScene.h"
#include "Manager/GameManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene* MainScene::createScene()
{
	SoundManager::PlayBackgroundMusic();
	return MainScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}


void MainScene::InitSprite(cocos2d::Sprite*& outSprite, cocos2d::Node* parentNode, const std::string& fileName, float x, float y, int localZOrder)
{
	if (fileName == "MainMenu/front_front.png" || fileName == "MainMenu/front_smoke_3.png" || fileName == "MainMenu/front_smoke_1.png")
		outSprite = Sprite::create(fileName);
	else
	{
		auto pinfo = AutoPolygon::generatePolygon(fileName);
		outSprite = Sprite::create(pinfo);
	}
	if (nullptr == outSprite)
	{
		outSprite = nullptr;
		problemLoading(fileName.c_str());
		return;
	}
	outSprite->setPosition(Vec2(x, y));
	parentNode->addChild(outSprite, localZOrder);
}

bool MainScene::InitUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	ValueMap a;
	//背景
	Sprite* rootNode = nullptr;
	InitSprite(rootNode, this, "MainMenu/zh/front_bg1152.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, -1);
	if (nullptr == rootNode)
		return false;

	//前置背景
	Sprite* frontNode = nullptr;
	InitSprite(frontNode, this, "MainMenu/front_front.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 3);
	if (nullptr == frontNode)
		return false;

	//开始冒险按钮
	click_start_game_button = Button::create("MainMenu/zh/front_btn_start_normal.png", "MainMenu/zh/front_btn_start_pressed.png", "null.png");
	if (nullptr == click_start_game_button)
		problemLoading("MainMenu/zh/front_btn_start_normal.png||MainMenu/zh/front_btn_start_pressed.png");
	else
	{
		click_start_game_button->setPosition(Vec2(origin.x + 570, origin.y + 384));
		this->addChild(click_start_game_button, 1);
	}

	//退出游戏按钮
	exit_button = Button::create("MainMenu/zh/exitButton_normal.png", "MainMenu/zh/exitButton_pressed.png");
	exit_button->setPosition(Vec2(origin.x + 575, origin.y + 270));
	addChild(exit_button, 1);

	//Monster4
	Sprite* monster4 = nullptr;
	InitSprite(monster4, this, "MainMenu/front_monster_4.png", origin.x + 227, origin.y + 475, 1);
	if (nullptr == monster4)
		return false;
	monster4->setScale(0.75);

	//保卫的萝卜
	Sprite* carrot = nullptr;
	InitSprite(carrot, this, "MainMenu/front_carrot.png", origin.x + 620, origin.y + 14, 2);
	if (nullptr == carrot)
		return false;
	carrot->setScale(0.75);

	//Monster6
	Sprite* monster6 = nullptr;
	InitSprite(monster6, this, "MainMenu/front_monster_6.png", origin.x + 995, origin.y + 248, 1);
	if (nullptr == monster6)
		return false;
	monster6->setScale(0.75);
	//Monster6Hand
	Sprite* monster6Hand = nullptr;
	InitSprite(monster6Hand, this, "MainMenu/front_monster_6_hand.png", origin.x + 894, origin.y + 256, -1);
	if (nullptr == monster6Hand)
		return false;
	monster6Hand->setScale(0.75);

	//Monster5
	Sprite* monster5 = nullptr;
	InitSprite(monster5, this, "MainMenu/front_monster_5.png", origin.x + 882, origin.y + 155, 1);
	if (nullptr == monster5)
		return false;
	monster5->setScale(0.75);


	//烟雾2
	Sprite* smoke2 = nullptr;
	InitSprite(smoke2, this, "MainMenu/front_smoke_3.png", origin.x + 1020, origin.y + 165, 1);
	if (nullptr == smoke2)
		return false;


	//Monster3
	Sprite* monster3 = nullptr;
	InitSprite(monster3, this, "MainMenu/front_monster_3.png", origin.x + 160, origin.y + 190, 1);
	if (nullptr == monster3)
		return false;
	monster3->setScale(0.75);


	//Monste1
	Sprite* monster1 = nullptr;
	InitSprite(monster1, this, "MainMenu/front_monster_1.png", origin.x + 230, origin.y + 155, 1);
	if (nullptr == monster1)
		return false;
	monster1->setScale(0.75);


	//烟雾1
	Sprite* smoke1 = nullptr;
	InitSprite(smoke1, this, "MainMenu/front_smoke_1.png", origin.x + 120, origin.y + 170, 1);
	if (nullptr == smoke1)
		return false;

	//Monster2
	Sprite* monster2 = nullptr;
	InitSprite(monster2, this, "MainMenu/front_monster_2.png", origin.x + 342, origin.y + 140, 1);
	if (nullptr == monster2)
		return false;
	monster2->setScale(0.75);
	return true;
}

void MainScene::InitEvent()
{
	click_start_game_button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			SoundManager::PlaySelectMusic();
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			//跳转场景
			auto chooseLevel = SelectLevelScene::createScene();
			Director::getInstance()->replaceScene(chooseLevel);
			break;
		}
		default:
			break;
		}
		});


	exit_button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {

		if( type==ui::Widget::TouchEventType::ENDED){
			//退出游戏

			Director::getInstance()->popScene();
		
		}
		});

}

bool MainScene::init()
{
	if (!Scene::init())
		return false;

	if (!InitUI())
		return false;

	//CCUserDefault::sharedUserDefault()->deleteValueForKey("level_1");
	GameManager::getGame()->level[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("level_1");

	//初始化事件
	InitEvent();

	return true;
}
