#pragma warning(disable:4996)

#include "GameScene.h"
#include "ui\CocosGUI.h"
#include "AdventureScene.h"
using namespace cocos2d::ui;

GameScene* GameScene::create()
{
	GameScene* ret = new GameScene();
	(*ret).money = 300;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}

	return ret;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	FileUtils::getInstance()->addSearchPath("Themes\\Items\\touming-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\Items");

	LayerColor* layerColor = LayerColor::create(Color4B::BLACK);
	this->addChild(layerColor, 0);

	Sprite* menuBar = Sprite::create("MenuBG.png");
	menuBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	menuBar->setPosition(Vec2(480, 640));
	this->addChild(menuBar, 1);

	__String* str = __String::createWithFormat("%d", money);
	CCLabelAtlas* moneyLabel = CCLabelAtlas::create(str->getCString(), "numText.png", 24, 32, '0');
	moneyLabel->setPosition(Vec2(100, 594));
	this->addChild(moneyLabel, 2);

	Button* btn_speed = Button::create("speed11.png", "speed12.png");
	btn_speed->setPosition(Vec2(725, 605));
	btn_speed->setPressedActionEnabled(true);
	this->addChild(btn_speed, 2);
	btn_speed->addClickEventListener([&](Ref* ref) {});

	Button* btn_pause = Button::create("pause01.png", "pause02.png");
	btn_pause->setPosition(Vec2(825, 605));
	btn_pause->setPressedActionEnabled(true);
	this->addChild(btn_pause, 2);
	btn_pause->addClickEventListener([&](Ref* ref) {});

	Button* btn_menu = Button::create("menu01.png", "menu02.png");
	btn_menu->setPosition(Vec2(890, 605));
	btn_menu->setPressedActionEnabled(true);
	this->addChild(btn_menu, 2);
	btn_menu->addClickEventListener([&](Ref* ref) {});

	return true;
}