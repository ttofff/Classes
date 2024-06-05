#include "Boss.h"
#include"ui\CocosGUI.h"
#include "StartScene.h"
#include "AdventureScene.h"
#include "GameScene.h"
#include"HelpScene.h"
#include "LoadingScene.h"

using namespace cocos2d::ui;



int Boss::smallcheck = 1;
Boss* Boss::create()
{
	Boss* ret = new Boss();
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


bool Boss::init()
{
	if (!Scene::init())
	{
		return false;
	}

	int Bloodnum[8] = {2,4,5,6,7,8,11,20};
	

	//背景
	Sprite* mainbg = Sprite::create("Themes\\scene\\stages_bg-hd\\ss_bg.png");
	mainbg->setPosition(Vec2(480, 320));
	this->addChild(mainbg, 0);
	//背景云
	Sprite* ss_cloud = Sprite::create("Themes\\scene\\stages_theme1-hd\\ss_cloud.png");
	ss_cloud->setAnchorPoint(Vec2(0.5,0));
	ss_cloud->setPosition(Vec2(480, 0));
	this->addChild(ss_cloud, 0);
	//
	
	//关卡

	__String* s;
	s = __String::createWithFormat("Themes\\scene\\antiboss1-hd\\boss_%02d_locked.png",smallcheck+8);
	Button* ss_map01 = Button::create(s->getCString());
	ss_map01->setPosition(Vec2(480, 380));
	ss_map01->setScale(1.2f);
	ss_map01->setPressedActionEnabled(true);
	this->addChild(ss_map01,2);
	ss_map01->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		LoadingScene* loadingScene = LoadingScene::create(smallcheck);
		loadingScene->SetBlockSize(blockSize);
		director->replaceScene(loadingScene);
	});
	//血条
	Sprite* Blood_bg = Sprite::create("Themes\\scene\\antiboss1-hd\\blood_bg.png");
	Blood_bg->setPosition(Vec2(480,150));
	this->addChild(Blood_bg);
	//血条数值
	__String* s1;
	s1 = __String::createWithFormat("Themes\\scene\\antiboss1-hd\\blood_%d0000.png",Bloodnum[smallcheck]);
	Sprite* Bloodnumber = Sprite::create(s1->getCString());
	Bloodnumber->setPosition(Vec2(480, 150));
	this->addChild(Bloodnumber);
	
	//限时背景指示精灵
	Sprite* time_bg = Sprite::create("Themes\\scene\\antiboss2-hd\\timelimit_60_CN.png");
	time_bg->setPosition(Vec2(370, 80));
	this->addChild(time_bg);



	//左移按钮
	if ((this->smallcheck) > 1){
		Button* theme_pointleft_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointleft_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointleft_pressed.png");
		theme_pointleft_normal->setPosition(Vec2(100, 320));
		theme_pointleft_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointleft_normal, 3);
		theme_pointleft_normal->addClickEventListener([&](Ref* ref){

			this->smallcheck = this->smallcheck - 1;
			Director* director = Director::getInstance();
			Boss* adventureFirstScene = Boss::create();

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
			Boss* adventureFirstScene = Boss::create();

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
		StartScene* adventureScene = StartScene::create();
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
	Button* ss_begin_normal = Button::create("Themes\\scene\\antiboss2-hd\\theme_play_normal_CN.png");
	ss_begin_normal->setPosition(Vec2(600, 80));
	ss_begin_normal->setPressedActionEnabled(true);
	this->addChild(ss_begin_normal, 3);
	ss_begin_normal->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		LoadingScene* loadingScene = LoadingScene::create(smallcheck);
		loadingScene->SetBlockSize(blockSize);
		director->replaceScene(loadingScene);
	});
	
	return true;
}

void Boss::SetBlockSize(int size)
{
	this->blockSize = size;
}