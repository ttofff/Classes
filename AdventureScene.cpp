#include "AdventureScene.h"
#include"ui\CocosGUI.h"
#include "AdventureFirstScene.h"
#include "StartScene.h"
#include"HelpScene.h"

using namespace cocos2d::ui;


int AdventureScene::n = 1;

bool AdventureScene::init()
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
	ss_cloud->setAnchorPoint(Vec2(0.5, 0));
	ss_cloud->setPosition(Vec2(480, 0));
	this->addChild(ss_cloud, 0);

	//进入选择关卡按钮
	__String * str = __String::createWithFormat("Themes\\scene\\themescene2-hd\\theme_pack%02d.png", n);
	Button* theme_pack01 = Button::create(str->getCString());
	theme_pack01->setPosition(Vec2(480, 320));
	theme_pack01->setPressedActionEnabled(true);
	this->addChild(theme_pack01, 1);
	theme_pack01->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		AdventureFirstScene* adventureFirstScene = AdventureFirstScene::create(n);
		director->replaceScene(adventureFirstScene);
	});

		//左移按钮
	if (this->n > 1)
	{
		Button* theme_pointleft_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointleft_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointleft_pressed.png");
		theme_pointleft_normal->setPosition(Vec2(100, 320));
		theme_pointleft_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointleft_normal, 3);
		theme_pointleft_normal->addClickEventListener([&](Ref* ref)
		{
			this->n = this->n - 1 < 1 ? 1 : n - 1;
			Director* director = Director::getInstance();
			AdventureScene* adventureScene = AdventureScene::create();
			TransitionCrossFade* Cross = TransitionCrossFade::create(.5f, adventureScene);
			director->replaceScene(Cross);
		});

	}
		
		//右移按钮
	if (this->n < Max)
	{
		Button* theme_pointright_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointright_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointright_pressed.png");
		theme_pointright_normal->setPosition(Vec2(860, 320));
		theme_pointright_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointright_normal, 3);
		theme_pointright_normal->addClickEventListener([&](Ref* ref)
		{
			this->n = this->n + 1 > Max ? Max : n + 1;
			Director* director = Director::getInstance();
			AdventureScene* adventureScene = AdventureScene::create();
			TransitionCrossFade* Cross = TransitionCrossFade::create(.5f, adventureScene);
			director->replaceScene(Cross);
		});
	}

		//返回主页按钮
		Button* theme_home_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_home_normal.png", "Themes\\scene\\themescene1-hd\\theme_home_pressed.png");
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

		//帮助按钮
		Button* ss_help_normal = Button::create("Themes\\scene\\themescene1-hd\\ss_help_normal.png", "Themes\\scene\\themescene1-hd\\ss_help_pressed.png");
		ss_help_normal->setPosition(Vec2(930, 610));
		ss_help_normal->setPressedActionEnabled(true);
		this->addChild(ss_help_normal, 3);
		ss_help_normal->addClickEventListener([&](Ref* ref){
			Director* director = Director::getInstance();
			HelpScene* heleScene = HelpScene::create();
			director->replaceScene(heleScene); 
});



		//选择关卡标题
		Sprite* theme_bg_CN = Sprite::create("Themes\\scene\\themescene1-hd\\theme_bg_CN.png");
		//theme_bg_CN->setAnchorPoint(Vec2(0.5, 0));
		theme_bg_CN->setPosition(Vec2(480, 610));
		this->addChild(theme_bg_CN, 1);

		return true;
}