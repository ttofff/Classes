#include "AdventureScene.h"
#include"ui\CocosGUI.h"

using namespace cocos2d::ui;



bool AdventureScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 增加资源搜索路径
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\stages_bg-hd"); 
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\stages_theme1-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\themescene1-hd");

	//背景
	Sprite* mainbg = Sprite::create("ss_bg.png");
	mainbg->setPosition(Vec2(480, 320));
	this->addChild(mainbg, 0);
	//背景云
	Sprite* ss_cloud = Sprite::create("ss_cloud.png");
	ss_cloud->setAnchorPoint(Vec2(0.5,0));
	ss_cloud->setPosition(Vec2(480, 0));
	this->addChild(ss_cloud, 0);
	//关卡1
	Button* ss_map01 = Button::create("ss_map01.png");
	ss_map01->setPosition(Vec2(480, 320));
	ss_map01->setPressedActionEnabled(true);
	this->addChild(ss_map01);
	ss_map01->addClickEventListener([&](Ref* ref){});
	
	//左移按钮
	Button* theme_pointleft_normal = Button::create("theme_pointleft_normal.png", "theme_pointleft_pressed.png");
	theme_pointleft_normal->setPosition(Vec2(100, 320));
	theme_pointleft_normal->setPressedActionEnabled(true);
	this->addChild(theme_pointleft_normal,3);
	theme_pointleft_normal->addClickEventListener([&](Ref* ref){});
	//右移按钮
	Button* theme_pointright_normal = Button::create("theme_pointright_normal.png", "theme_pointright_pressed.png");
	theme_pointright_normal->setPosition(Vec2(860, 320));
	theme_pointright_normal->setPressedActionEnabled(true);
	this->addChild(theme_pointright_normal,3);
	theme_pointright_normal->addClickEventListener([&](Ref* ref){});
	//返回主页按钮
	Button* theme_home_normal = Button::create("theme_home_normal.png", "theme_home_normal.png");
	theme_home_normal->setPosition(Vec2(30, 610));
	theme_home_normal->setPressedActionEnabled(true);
	this->addChild(theme_home_normal, 3);
	theme_home_normal->addClickEventListener([&](Ref* ref){});
	//帮助按钮
	Button* ss_help_normal = Button::create("ss_help_normal.png", "ss_help_normal.png");
	ss_help_normal->setPosition(Vec2(930, 610));
	ss_help_normal->setPressedActionEnabled(true);
	this->addChild(ss_help_normal, 3);
	ss_help_normal->addClickEventListener([&](Ref* ref){});
	//关卡可用的炮塔
	Sprite* ss_towers_01 = Sprite::create("ss_towers_01.png");
	ss_towers_01->setAnchorPoint(Vec2(0.5, 0));
	ss_towers_01->setPosition(Vec2(480, 100));
	this->addChild(ss_towers_01, 1);

	//选择关卡图
	Sprite* theme_bg_CN = Sprite::create("theme_bg_CN.png");
	//theme_bg_CN->setAnchorPoint(Vec2(0.5, 0));
	theme_bg_CN->setPosition(Vec2(480, 610));
	this->addChild(theme_bg_CN, 1);

	return true;
}