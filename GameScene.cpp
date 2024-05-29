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

	return true;
}