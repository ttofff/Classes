#pragma warning(disable:4996)

#include "GameScene.h"
#include "ui\CocosGUI.h"
#include "AdventureScene.h"
using namespace cocos2d::ui;

GameScene* GameScene::create(int i)
{
	GameScene* ret = new GameScene();
	ret->money = 300;
	ret->index = i;
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
	FileUtils::getInstance()->addSearchPath("Themes\\Theme1");
	FileUtils::getInstance()->addSearchPath("Themes\\Items");

	if (index == 3 || index == 4 || index == 7)
	{
		Sprite* levelBG = Sprite::create("BG0\\BG2-hd\\BG2.png");
		levelBG->setAnchorPoint(Vec2(0, 0));
		this->addChild(levelBG, 0);
	}
	else
	{
		Sprite* levelBG = Sprite::create("BG0\\BG1-hd\\BG1.png");
		levelBG->setAnchorPoint(Vec2(0, 0));
		this->addChild(levelBG, 0);
	}

	if (index < 4)
	{
		__String* path_str = __String::createWithFormat("BG%d\\BG-hd\\Path.png", index);
		Sprite* levelPath = Sprite::create(path_str->getCString());
		levelPath->setAnchorPoint(Vec2(1, 0));
		levelPath->setPosition(Vec2(960, 0));
		this->addChild(levelPath, 0);
	}
	else
	{
		__String* path_str = __String::createWithFormat("BG%d\\.BG-hd_PList.Dir\\Path.png", index);
		Sprite* levelPath = Sprite::create(path_str->getCString());
		levelPath->setAnchorPoint(Vec2(1, 0));
		levelPath->setPosition(Vec2(960, 0));
		this->addChild(levelPath, 0);
	}

	Sprite* menuBar = Sprite::create("MenuBG.png");
	menuBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	menuBar->setPosition(Vec2(480, 640));
	this->addChild(menuBar, 1);

	// 20 40 .
	// 44 40 .
	__String* str = __String::createWithFormat("%d", money);
	CCLabelAtlas* moneyLabel = CCLabelAtlas::create(str->getCString(), "numwhite-hd.png", 20, 40, '.');
	moneyLabel->setPosition(Vec2(100, 594));
	this->addChild(moneyLabel, 2);

	// 全局速度变量
	CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();

	// 1倍速按钮
	Button* btn_speed = Button::create("speed11.png", "speed12.png");
	btn_speed->setPosition(Vec2(725, 605));
	this->addChild(btn_speed, 2);

	// 2倍速按钮
	Button* btn_speed_two = Button::create("speed21.png", "speed22.png");
	btn_speed_two->setPosition(Vec2(725, 605));
	this->addChild(btn_speed_two, 2);
	btn_speed_two->setVisible(false);

	// 倍速按钮点击事件
	btn_speed->addClickEventListener([pScheduler, btn_speed, btn_speed_two](Ref* ref) {
		pScheduler->setTimeScale(2.f);
		btn_speed->setVisible(false);
		btn_speed_two->setVisible(true);
	});
	btn_speed_two->addClickEventListener([pScheduler, btn_speed, btn_speed_two](Ref* ref) {
		pScheduler->setTimeScale(1.f);
		btn_speed->setVisible(true);
		btn_speed_two->setVisible(false);
	});

	Button* btn_pause = Button::create("pause11.png", "pause12.png");
	btn_pause->setPosition(Vec2(825, 605));
	btn_pause->setVisible(false);
	this->addChild(btn_pause, 2);

	Button* btn_go = Button::create("pause01.png", "pause02.png");
	btn_go->setPosition(Vec2(825, 605));
	btn_go->setVisible(true);
	this->addChild(btn_go, 2);
	btn_go->addClickEventListener([this, btn_go, btn_pause](Ref* ref) {
		
		btn_go->setVisible(false);
		btn_pause->setVisible(true);
		Director::getInstance()->stopAnimation();
	});

	btn_pause->addClickEventListener([this, btn_go, btn_pause](Ref* ref) {
		btn_go->setVisible(true);
		btn_pause->setVisible(false);

		Director::getInstance()->startAnimation();
	});

	Button* btn_menu = Button::create("menu01.png", "menu02.png");
	btn_menu->setPosition(Vec2(890, 605));
	this->addChild(btn_menu, 2);
	btn_menu->addClickEventListener([&](Ref* ref) {});

	return true;
}