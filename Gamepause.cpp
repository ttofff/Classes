#include "Gamepause.h"
#include "GameScene.h"
#include "AdventureFirstScene.h"
#include "ui\CocosGUI.h"
#include "iostream"

using namespace cocos2d::ui;

bool Gamepause::init()
{

	if (!Scene::init())
	{
		return false;
	}
	
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\gamemenu-hd");

	//����ͼ
	Sprite* MenuBk = Sprite::create("menu_bg.png");
	MenuBk->setPosition(Vec2(480, 320));
	this->addChild(MenuBk, 0);

	//������Ϸ
	Button* ContinueGame = Button::create("menu_resume_normal_CN.png","menu_resume_pressed_CN");
	ContinueGame->setPosition(Vec2(468, 422));
	this->addChild(ContinueGame, 0);
	ContinueGame->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
	});
	
	//���¿�ʼ
	Button* RestartGame = Button::create("menu_restart_normal_CN.png","menu_restart_pressed_CN");
	RestartGame->setPosition(Vec2(468, 328));
	this->addChild(RestartGame, 1);
	RestartGame->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		GameScene* gameScene = GameScene::create(this->index);
		director->replaceScene(gameScene);
	});

	//ѡ��ؿ�
	Button* SelectGame = Button::create("menu_quit_normal_CN.png","menu_quit_pressed_CN");
	SelectGame->setPosition(Vec2(468, 234));
	this->addChild(SelectGame, 1);
	SelectGame->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		AdventureFirstScene* adventureFirstScene = AdventureFirstScene::create();
		director->replaceScene(adventureFirstScene);
	});

	return true;
}
