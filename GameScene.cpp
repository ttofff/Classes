#pragma warning(disable:4996)

#include "GameScene.h"
#include "ui\CocosGUI.h"
#include "AdventureScene.h"
#include "Gamepause.h"
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
	FileUtils::getInstance()->addSearchPath("Themes\\Items\\Items01-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\Items\\Items02-hd");
	
	//暂停菜单
	Gamepause* gamepause = Gamepause::create();
	this->addChild(gamepause, 5);
	gamepause->index = this->index;
	gamepause->setVisible(false);

	// 生成背景图
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

	// 生成关卡图
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

	// 菜单栏背景
	Sprite* menuBG = Sprite::create("MenuBG.png");
	menuBG->setAnchorPoint(Vec2(0.5, 1));
	menuBG->setPosition(Vec2(480, 640));
	this->addChild(menuBG, 1);

	// 金币数量
	__String* str = __String::createWithFormat("%d", money);
	CCLabelAtlas* moneyLabel = CCLabelAtlas::create(str->getCString(), "numwhite-hd.png", 20, 40, '.');
	moneyLabel->setPosition(Vec2(100, 590));
	this->addChild(moneyLabel, 2);

	// 显示当前波数和总波数精灵
	Sprite* menuCenter = Sprite::create("MenuCenter_01_CN.png");
	menuCenter->setPosition(Vec2(463, 45));
	menuBG->addChild(menuCenter, 1);

	//当前波数
	TextAtlas*curWaveText = TextAtlas::create("01", "numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(390, 45));
	menuBG->addChild(curWaveText, 2);

	//总波数
	TextAtlas*totalWaveText = TextAtlas::create("15", "numwhite-hd.png", 20, 40, ".");
	totalWaveText->setPosition(Vec2(480, 45));
	menuBG->addChild(totalWaveText, 2);

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

	//暂停中
	Sprite* btn_stop = Sprite::create("MenuCenter_02_CN.png");
	btn_stop->setPosition(Vec2(480, 320));
	btn_stop->setVisible(false);
	this->addChild(btn_stop, 2);

	// 暂停按钮
	Button* btn_pause = Button::create("pause11.png", "pause12.png");
	btn_pause->setPosition(Vec2(825, 605));
	btn_pause->setVisible(false);
	this->addChild(btn_pause, 2);

	// 开始按钮
	Button* btn_go = Button::create("pause01.png", "pause02.png");
	btn_go->setPosition(Vec2(825, 605));
	btn_go->setVisible(true);
	this->addChild(btn_go, 2);

	

	// 菜单按钮
	Button* btn_menu = Button::create("menu01.png", "menu02.png");
	btn_menu->setPosition(Vec2(890, 605));
	this->addChild(btn_menu, 2);
	btn_menu->addClickEventListener([gamepause](Ref* ref) 
	{
		Director* director = Director::getInstance();
		gamepause->setVisible(true);
		director->stopAnimation();
	});

	// 暂停、开始点击事件
	btn_pause->addClickEventListener([this, btn_go, btn_pause, btn_stop, btn_speed, btn_menu](Ref* ref) {
		btn_go->setVisible(true);
		btn_stop->setVisible(false);
		btn_pause->setVisible(false);
		Director::getInstance()->startAnimation();

		btn_speed->setTouchEnabled(true);
		btn_menu->setTouchEnabled(true);
	});
	btn_go->addClickEventListener([this, btn_go, btn_pause, btn_stop, btn_speed, btn_menu](Ref* ref) {
		btn_go->setVisible(false);
		btn_stop->setVisible(true);
		btn_pause->setVisible(true);
		Director::getInstance()->stopAnimation();

		btn_speed->setTouchEnabled(false);
		btn_menu->setTouchEnabled(false);
	});

	// 萝卜图像
	Sprite* ca = Sprite::create("hlb10.png");
	ca->setPosition(Vec2(830, 480));
	this->addChild(ca, 5);

	// 萝卜抖动动画
	Animation* carrotAnimation = Animation::create();
	carrotAnimation->addSpriteFrameWithFile("hlb11.png");
	carrotAnimation->addSpriteFrameWithFile("hlb12.png");
	carrotAnimation->addSpriteFrameWithFile("hlb13.png");
	carrotAnimation->addSpriteFrameWithFile("hlb14.png");
	carrotAnimation->addSpriteFrameWithFile("hlb15.png");
	carrotAnimation->addSpriteFrameWithFile("hlb16.png");
	carrotAnimation->addSpriteFrameWithFile("hlb17.png");
	carrotAnimation->addSpriteFrameWithFile("hlb18.png");
	carrotAnimation->setLoops(CC_REPEAT_FOREVER);
	carrotAnimation->setDelayPerUnit(0.1f);
	Animate* pAnimate = Animate::create(carrotAnimation);
	ca->runAction(pAnimate);

	return true;
}