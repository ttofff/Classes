#pragma warning(disable:4996)
#include"Monster.h"
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


// 通过瓦片地图获取怪物行走路径
void GameScene::getWayPoints()
{
	// 获取PATH对象层
	TMXObjectGroup* group = tiledMap->getObjectGroup("PATH");
	// 获取对象层上所有对象
	ValueVector valueVector = group->getObjects();
	// 遍历所有对象
	for (Value value : valueVector)
	{
		// 将Value转换为ValueMap
		ValueMap valueMap = value.asValueMap();
		// 获取对应的x和y属性
		float x = valueMap["x"].asFloat();
		float y = valueMap["y"].asFloat();
		// 将对应的x和y组成的向量添加到vector中
		// 注意:瓦片地图坐标建在左上角，转换到中心点各减格子大小一半
		wayPoints.push_back(Vec2(x + 40, y - 40));
	}
}

void GameScene::update(float dt)
{
	monster->onMonsterUpdate(0.01);
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
	gamepause->setVisible(false);

	

	// 生成关卡图

	__String *str = __String::createWithFormat("Map\\FirstKind\\Environment\\Level%02d\\Level.tmx",index);
	tiledMap = TMXTiledMap::create(str->getCString());
	tiledMap->setPosition(Vec2::ZERO);
	this->addChild(tiledMap, 0);
	
	//怪物
	getWayPoints(); //获取诖误移动路径

	Button* createMonster = Button::create("Themes\\Items\\Items11-hd\\warning_1.png", "Themes\\Items\\Items11-hd\\warning_2.png");
	createMonster->setPosition(Vec2(800,500));
	this->addChild(createMonster,5);
	createMonster->addClickEventListener([&](Ref*){

		monster = Monster::create(MonsterType::fly_yellow);

		monster->onMonsterInit(wayPoints);

		this->addChild(monster);

		scheduleUpdate();
	});


	// 菜单栏背景
	Sprite* menuBG = Sprite::create("MenuBG.png");
	menuBG->setAnchorPoint(Vec2(0.5, 1));
	menuBG->setPosition(Vec2(480, 640));
	this->addChild(menuBG, 1);

	// 金币数量
	__String* s = __String::createWithFormat("%d", money);
	CCLabelAtlas* moneyLabel = CCLabelAtlas::create(s->getCString(), "numwhite-hd.png", 20, 40, '.');
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
	pScheduler->setTimeScale(1.f);

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
	btn_menu->addClickEventListener([this,gamepause, btn_speed,btn_menu](Ref* ref) 
	{
		Director* director = Director::getInstance();
		gamepause->setVisible(true);
		this->scheduleOnce([director](float dt){
			director->stopAnimation();
		}, 0.2f, "delayed_key");
		
	});

	// 暂停、开始点击事件
	btn_pause->addClickEventListener([ btn_go, btn_pause, btn_stop, btn_speed, btn_menu](Ref* ref) {
		btn_go->setVisible(true);
		btn_stop->setVisible(false);
		btn_pause->setVisible(false);
		Director::getInstance()->startAnimation();

		btn_speed->setTouchEnabled(true);
		btn_menu->setTouchEnabled(true);
	});
	btn_go->addClickEventListener([btn_go, btn_pause, btn_stop, btn_speed, btn_menu](Ref* ref) {
		btn_go->setVisible(false);
		btn_stop->setVisible(true);
		btn_pause->setVisible(true);
		Director::getInstance()->stopAnimation();

		btn_speed->setTouchEnabled(false);
		btn_menu->setTouchEnabled(false);
	});

	




	// 萝卜图像
	Sprite* ca = Sprite::create("hlb10.png");
	ca->setPosition(wayPoints.back());
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