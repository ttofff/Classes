#include"HelpScene2.h"
#include "ui\CocosGUI.h"
#include "StartScene.h"
#include"HelpScene.h"
#include"HelpScene1.h"


using namespace cocos2d::ui;
int HelpScene2::a = 1;
HelpScene2* HelpScene2::create()
{
	HelpScene2* ret = new HelpScene2();
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


bool HelpScene2::init()
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
	Button* helpbt = Button::create("tips_normal_CN.png","tips_selected_CN.png");
	helpbt->setPosition(Vec2(270, 590));
	this->addChild(helpbt);
	helpbt->addClickEventListener([&](Ref* ref) {
		Director* director = Director::getInstance();
		HelpScene* heleScene = HelpScene::create();
		director->replaceScene(heleScene); });

		//¹ÖÎï°´Å¥
		Button* selected = Button::create("monster_normal_CN.png", "monster_selected_CN.png");
		selected->setPosition(Vec2(470, 590));
		selected->setVisible(true);
		this->addChild(selected);
		selected->addClickEventListener([&](Ref* ref) {
			Director* director = Director::getInstance();
			HelpScene1* heleScene1 = HelpScene1::create();
			director->replaceScene(heleScene1); });


		//ÅÚËþ°´Å¥
		Button* tower = Button::create("tower_normal_CN.png", "tower_selected_CN.png");
		tower->setPosition(Vec2(670, 590));
		this->addChild(tower);
		//Í¼Æ¬½éÉÜ
		__String* s1 = __String::createWithFormat("tower_%02d.png", a);
		Sprite* tips = Sprite::create(s1->getCString());
		tips->setAnchorPoint(Vec2(0.5, 0));
		tips->setScale(0.8f);
		tips->setPosition(Vec2(480, 100));
		this->addChild(tips, 2);

		//ÎÄ×Ö½éÉÜ
		__String* s2 = __String::createWithFormat("tower_%02d_CN.png", a);
		Sprite* word_02 = Sprite::create(s2->getCString());
		word_02->setAnchorPoint(Vec2(0.5, 0));
		word_02->setScale(0.8f);
		word_02->setPosition(Vec2(480, 135));
		this->addChild(word_02, 2);

		//×óÒÆ°´Å¥
		if ((this->a) > 1){
		Button* theme_pointleft_normal = Button::create("theme_pointleft_pressed.png", "theme_pointleft_normal.png");
		theme_pointleft_normal->setPosition(Vec2(100, 320));
		theme_pointleft_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointleft_normal, 3);
		theme_pointleft_normal->addClickEventListener([&](Ref* ref){

		this->a = this->a - 1;
		Director* director = Director::getInstance();
		HelpScene2 *helpscene = HelpScene2::create();

		TransitionCrossFade* cross = TransitionCrossFade::create(1.f, helpscene);
		director->replaceScene(cross);
		});
		}

		//ÓÒÒÆ°´Å¥
		if ((this->a) < MAX){
		Button* theme_pointright_normal = Button::create("theme_pointright_normal.png", "theme_pointright_pressed.png");
		theme_pointright_normal->setPosition(Vec2(860, 320));
		theme_pointright_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointright_normal, 3);
		theme_pointright_normal->addClickEventListener([&](Ref* ref){

		this->a = this->a + 1;
		Director* director = Director::getInstance();
		HelpScene2* helpscene = HelpScene2::create();

		TransitionCrossFade* cross = TransitionCrossFade::create(1.f, helpscene);
		director->replaceScene(cross);
		});
		}
			
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