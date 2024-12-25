#include"Tower/Tower.h"
#include"MAP/MAP.h"
#include "cocos2d.h"
#include "Tower.h"
#include"Manager/GameManager.h"
#include"Manager/SoundManager.h"
using namespace cocos2d::ui;
//��������
Terrains* Terrains::createTerrain()
{
	return  Terrains::create();
}

//���г�ʼ������
bool Terrains::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//Refactored with State Pattern
	this->TransitionTo(new TerrainUnbuiltState);

	state->setIsShow(false);

	setTexture("GamePlay/select.png");
	setOpacity(0);

	//��ʼ������ͼ��
	initUI();

	//Ϊ����ͼ����Ӽ���
	initEvent();

	return true;
}

//Refactored with State Pattern
void Terrains::TransitionTo(TerrainState* st) {
	if (this->state != nullptr)
		delete this->state;
	this->state = st;
	this->state->setContext(this);
}

//��������ͼ��
void Terrains::initUI()
{
	bottleIcon = Button::create("Bottle/Bottle01.png", "Bottle/Bottle01.png", "");
	bottleIcon->setPosition(Vec2(-30, 110));
	bottleIcon->setPressedActionEnabled(true);
	bottleIcon->setVisible(false);
	this->addChild(bottleIcon, 2);

	sunFlowerIcon = Button::create("Flower/Flower01.png", "Flower/Flower01.png", "");
	sunFlowerIcon->setPosition(Vec2(40, 110));
	sunFlowerIcon->setPressedActionEnabled(true);
	sunFlowerIcon->setVisible(false);
	this->addChild(sunFlowerIcon, 2);

	icedStarIcon = Button::create("Star/Star01.png", "Star/Star01.png", "");
	icedStarIcon->setPosition(Vec2(110, 110));
	icedStarIcon->setPressedActionEnabled(true);
	icedStarIcon->setVisible(false);
	this->addChild(icedStarIcon, 2);

}

//Ϊ��������¼�����
void Terrains::initEvent()
{
	bottleIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED )
		{
			if (GameManager::getGame()->Money >= 100) {
				//Refactored with State Pattern
				hideInfo();//����ѡ�ڽ���
				TransitionTo(new TerrainBuiltState);//������״̬��Ϊ�ѽ���
				//End
				auto bottle = Bottle::create();
				bottle->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
				addChild(bottle, 0);
				SoundManager::PlayBuildMusic();
				bottle->buildTower("Bottle/Bottle_3.png", "Bottle/Bottle11.png");
			}
		}
		});

	sunFlowerIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (GameManager::getGame()->Money >= 180) {
				//Refactored with State Pattern
				hideInfo();
				TransitionTo(new TerrainBuiltState);//������״̬��Ϊ�ѽ���
				//End
				auto flower = Flower::create();
				flower->setPosition(Vec2(25, 23));
				addChild(flower, -1);
				SoundManager::PlayBuildMusic();
				flower->buildTower("Flower/level1.png", "Flower/level1_bg.png");
			}
		}
		});

	icedStarIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (GameManager::getGame()->Money >= 180) {
				//Refactored with State Pattern
				hideInfo();
				TransitionTo(new TerrainBuiltState);//������״̬��Ϊ�ѽ���
				//End
				auto star = Star::create();
				star->setPosition(Vec2(36, 36));
				addChild(star, 0);
				star->buildTower("Star/level1_base.png", "Star/level1.png");
			}
		}
		});
}

//Refactored with State Pattern
void TerrainUnbuiltState::showInfo()
{
	int money = GameManager::getGame()->Money;
	if (this->getIsShow() == false) {
		setIsShow(true);
		auto context = getContext();
		context->setOpacity(255);//��ͼƬ��Ϊ��ȫ��͸��
		//����Ǯ������ͼƬ��ʽ
		if (money < 100)
			context->bottleIcon->loadTextures("Bottle/bottle00.png", "Bottle/bottle00.png", "");
		else
			context->bottleIcon->loadTextures("Bottle/bottle01.png", "Bottle/bottle01.png", "");
		if (money < 180) {
			context->sunFlowerIcon->loadTextures("Flower/Flower00.png", "Flower/Flower00.png", "");
			context->icedStarIcon->loadTextures("Star/Star02.png", "Star/Star02.png", "");
		}
		else {
			context->sunFlowerIcon->loadTextures("Flower/Flower01.png", "Flower/Flower01.png", "");
			context->icedStarIcon->loadTextures("Star/Star01.png", "Star/Star01.png", "");
		}
		//��������ͼ��ɼ�
		context->bottleIcon->setVisible(true);
		context->sunFlowerIcon->setVisible(true);
		context->icedStarIcon->setVisible(true);
	}
}

////Refactored with State Pattern
void TerrainUnbuiltState::hideInfo()
{
	if (this->getIsShow() == true) {
		setIsShow(false);
		this->getContext()->setOpacity(0);
		this->getContext()->bottleIcon->setVisible(false);
		this->getContext()->sunFlowerIcon->setVisible(false);
		this->getContext()->icedStarIcon->setVisible(false);
	}
}

//�Ի�����ͼ����б任
void Terrains::updateTerrain(char* name) {

	auto attackrange = getChildByName("attackRange");

	setTexture(name);

	attackrange->setPosition(getContentSize().width / 2, getContentSize().height / 2);

}

