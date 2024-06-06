#include "AdventureFirstScene.h"
#include"ui\CocosGUI.h"
#include "StartScene.h"
#include "AdventureScene.h"
#include "GameScene.h"
#include"HelpScene.h"
#include "LoadingScene.h"

using namespace cocos2d::ui;

int AdventureFirstScene::smallcheck = 1;
int AdventureFirstScene::bigcheck = 1;
AdventureFirstScene* AdventureFirstScene::create(int i)
{
	AdventureFirstScene* ret = new AdventureFirstScene();
	ret->bigcheck = i;
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


bool AdventureFirstScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//背景
	Sprite* mainbg = Sprite::create("Themes\\scene\\stages_bg-hd\\ss_bg.png");
	mainbg->setPosition(Vec2(480, 320));
	this->addChild(mainbg, 0);
	//背景云
	Sprite* ss_cloud = Sprite::create("Themes\\scene\\stages_theme1-hd\\ss_cloud.png");
	ss_cloud->setAnchorPoint(Vec2(0.5,0));
	ss_cloud->setPosition(Vec2(480, 0));
	this->addChild(ss_cloud, 0);

	//关卡
	float size = 0.f;
	__String* s;
	if (bigcheck == 1)
	{
		s = __String::createWithFormat("Map\\FirstKind\\Environment\\Level%02d\\Level.png", smallcheck);
		size = 0.6f;
		blockSize = 80;
		monsterKind = 1;
	}
	else if (bigcheck == 2)
	{
		s = __String::createWithFormat("Map\\SecondKind\\Environment\\Level%02d\\Level.png", smallcheck);
		size = 0.9f;
		blockSize = 64;
		monsterKind = 2;
	}
	else if (bigcheck == 3)
	{
		s = __String::createWithFormat("Map\\ThirdKind\\Environment\\Level%02d\\Level.png", smallcheck);
		size = 0.7f;
		blockSize = 80;
		monsterKind = 1;
	}
	Button* ss_map01 = Button::create(s->getCString());
	ss_map01->setPosition(Vec2(480, 320));
	ss_map01->setScale(size);
	ss_map01->setPressedActionEnabled(true);
	this->addChild(ss_map01,2);
	ss_map01->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		LoadingScene* loadingScene = LoadingScene::create(smallcheck);
		loadingScene->SetBlockSize(blockSize);
		loadingScene->SetMonsterKind(monsterKind);
		director->replaceScene(loadingScene);
	});

	//关卡可用的炮塔
	__String* s1 = __String::createWithFormat("Themes\\scene\\stages_theme1-hd\\ss_towers_%02d.png", smallcheck);
	Sprite* ss_towers_01 = Sprite::create(s1->getCString());
	ss_towers_01->setAnchorPoint(Vec2(0.5, 0));
	ss_towers_01->setPosition(Vec2(480, 90));
	this->addChild(ss_towers_01, 2);
	
	//左移按钮
	if ((this->smallcheck) > 1){
		Button* theme_pointleft_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointleft_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointleft_pressed.png");
		theme_pointleft_normal->setPosition(Vec2(100, 320));
		theme_pointleft_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointleft_normal, 3);
		theme_pointleft_normal->addClickEventListener([&](Ref* ref){

			this->smallcheck = this->smallcheck - 1;
			Director* director = Director::getInstance();
			AdventureFirstScene* adventureFirstScene = AdventureFirstScene::create(bigcheck);

			TransitionCrossFade* cross = TransitionCrossFade::create(1.f, adventureFirstScene);
			director->replaceScene(cross);
		});
	}

	//右移按钮
	if ((this->smallcheck) < MAX){
		Button* theme_pointright_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointright_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointright_pressed.png");
		theme_pointright_normal->setPosition(Vec2(860, 320));
		theme_pointright_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointright_normal, 3);
		theme_pointright_normal->addClickEventListener([&](Ref* ref){

			this->smallcheck = this->smallcheck + 1;
			Director* director = Director::getInstance();
			AdventureFirstScene* adventureFirstScene = AdventureFirstScene::create(bigcheck);

			TransitionCrossFade* cross = TransitionCrossFade::create(1.f, adventureFirstScene);
			director->replaceScene(cross);
		});	
	}
	
	//返回上一级按钮
	Button* theme_home_normal = Button::create("Themes\\scene\\stages_bg-hd\\ss_back_normal.png", "Themes\\scene\\stages_bg-hd\\ss_back_pressed.png");
	theme_home_normal->setPosition(Vec2(30, 610));
	theme_home_normal->setPressedActionEnabled(true);
	this->addChild(theme_home_normal, 3);
	theme_home_normal->setScale(1.2f);
	theme_home_normal->addClickEventListener([&](Ref* ref)
	{
		Director* director = Director::getInstance();
		AdventureScene* adventureScene = AdventureScene::create();
		director->replaceScene(adventureScene);
	});

	//帮助按钮
	Button* ss_help_normal = Button::create("Themes\\scene\\themescene1-hd\\ss_help_normal.png", "Themes\\scene\\themescene1-hd\\ss_help_pressed.png");
	ss_help_normal->setPosition(Vec2(930, 610));
	ss_help_normal->setPressedActionEnabled(true);
	this->addChild(ss_help_normal, 3);
	ss_help_normal->addClickEventListener([&](Ref* ref) {
		Director* director = Director::getInstance();
		HelpScene* heleScene = HelpScene::create();
		director->replaceScene(heleScene); });


	

	//选择关卡标题
	Sprite* theme_bg_CN = Sprite::create("Themes\\scene\\themescene1-hd\\theme_bg_CN.png");
	//theme_bg_CN->setAnchorPoint(Vec2(0.5, 0));
	theme_bg_CN->setPosition(Vec2(480, 610));
	this->addChild(theme_bg_CN, 1);
	
	//开始游戏按钮
	Button* ss_begin_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_play_pressed.png");
	ss_begin_normal->setPosition(Vec2(480, 60));
	ss_begin_normal->setPressedActionEnabled(true);
	this->addChild(ss_begin_normal, 3);
	ss_begin_normal->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		LoadingScene* loadingScene = LoadingScene::create(smallcheck);
		loadingScene->SetBlockSize(blockSize);
		loadingScene->SetMonsterKind(monsterKind);
		director->replaceScene(loadingScene);
	});

	return true;
}