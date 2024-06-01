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
	
	//����ͼ
	Button* BK = Button::create("empty.png", "empty.png");
	BK->setPosition(Vec2(480, 320));
	this->addChild(BK, 0);
	BK->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
	});



	//����ͼ
	Sprite* MenuBk = Sprite::create("Themes\\scene\\gamemenu-hd\\menu_bg.png");
	MenuBk->setPosition(Vec2(480, 320));
	this->addChild(MenuBk, 1);

	//������Ϸ
	Button* ContinueGame = Button::create("Themes\\scene\\gamemenu-hd\\menu_resume_normal_CN.png","Themes\\scene\\gamemenu-hd\\menu_resume_pressed_CN");
	ContinueGame->setPosition(Vec2(468, 422));
	this->addChild(ContinueGame, 1);
	ContinueGame->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
	});
	

	//ѡ��ؿ�
	Button* SelectGame = Button::create("Themes\\scene\\gamemenu-hd\\menu_quit_normal_CN.png","Themes\\scene\\gamemenu-hd\\menu_quit_pressed_CN");
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

void Gamepause::RestartMap(int index)
{
	//���¿�ʼ
	Button* RestartGame = Button::create("Themes\\scene\\gamemenu-hd\\menu_restart_normal_CN.png", "Themes\\scene\\gamemenu-hd\\menu_restart_pressed_CN.png");
	RestartGame->setPosition(Vec2(468, 328));
	this->addChild(RestartGame, 1);
	RestartGame->addClickEventListener([this, index](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		GameScene* gameScene = GameScene::create(index);
		director->replaceScene(gameScene);
	});

}