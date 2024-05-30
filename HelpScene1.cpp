#include"HelpScene1.h"
#include "ui\CocosGUI.h"
#include "StartScene.h"
#include"HelpScene.h"
#include"HelpScene2.h"

using namespace cocos2d::ui;
HelpScene1* HelpScene1::create()
{
	HelpScene1* ret = new HelpScene1();
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


bool HelpScene1::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//ËÑË÷Â·¾¶
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\help_1-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\help_2-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\help_3-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\themescene1-hd");
	//±³¾°¾«Áé
	Sprite* mainbg = Sprite::create("help_bg.png");
	mainbg->setPosition(Vec2(480, 320));
	this->addChild(mainbg, 0);
	//°ïÖú°´Å¥
	Button* helpbt = Button::create( "tips_normal_CN.png","tips_selected_CN.png");
	helpbt->setPosition(Vec2(270, 590));
	this->addChild(helpbt);
	helpbt->addClickEventListener([&](Ref* ref) {
		Director* director = Director::getInstance();
		HelpScene* heleScene = HelpScene::create();
		director->replaceScene(heleScene); });

	//¹ÖÎï°´Å¥
	Button* selected = Button::create("monster_normal_CN.png", "monster_selected_CN.png");
	selected->setPosition(Vec2(470, 590));
	this->addChild(selected);
	//Í¼Æ¬½éÉÜ
	Sprite* monster = Sprite::create("help_monster.png");
	monster->setPosition(480, 340);
	monster->setScale(0.8f);
	this->addChild(monster);

	//ÅÚËþ°´Å¥
	Button* tower = Button::create("tower_normal_CN.png", "tower_selected_CN.png");
	tower->setPosition(Vec2(670, 590));
	this->addChild(tower);
	tower->addClickEventListener([&](Ref* ref) {
		Director* director = Director::getInstance();
		HelpScene2* heleScene2 = HelpScene2::create();
		director->replaceScene(heleScene2); });

	//·µ»ØÖ÷Ò³°´Å¥
	Button* theme_home_normal = Button::create("theme_home_normal.png", "theme_home_pressed.png");
	theme_home_normal->setPosition(Vec2(30, 610));
	theme_home_normal->setPressedActionEnabled(true);
	this->addChild(theme_home_normal, 3);
	theme_home_normal->setScale(1.2f);
	theme_home_normal->addClickEventListener([&](Ref* ref)
	{
		Director* director = Director::getInstance();
		StartScene* StartScene = StartScene::create();
		director->replaceScene(StartScene);
	});

			return true;
}