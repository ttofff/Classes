#include "GameEnd.h"
#include "GameScene.h"
#include "AdventureFirstScene.h"
#include "ui\CocosGUI.h"
#include "iostream"

using namespace cocos2d::ui;

bool GameEnd::init()
{

	if (!Scene::init())
	{
		return false;
	}

	FileUtils::getInstance()->addSearchPath("Themes\\Items");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\gameover-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\gameover0-hd");
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\gamemenu-hd");
	//空白图
	Button* BK = Button::create("empty.png", "empty.png");
	BK->setPosition(Vec2(480, 320));
	this->addChild(BK, 0);
	BK->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
	});


	//背景图
	Sprite* MenuBk = Sprite::create("lose_bg.png");
	MenuBk->setPosition(Vec2(480, 320));
	this->addChild(MenuBk, 1);

	//文字
	Sprite* GameOverText = Sprite::create("lose_bg_CN.png");
	GameOverText->setPosition(Vec2(460, 320));
	this->addChild(GameOverText, 1);

	//选择关卡
	Button* SelectGame = Button::create("select_normal_CN.png", "select_pressed_CN.png");
	SelectGame->setPosition(Vec2(570, 220));
	SelectGame->setScale(0.8f);
	this->addChild(SelectGame, 1);
	SelectGame->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		AdventureFirstScene* adventureFirstScene = AdventureFirstScene::create();
		director->replaceScene(adventureFirstScene);
	});

}

//显示波数
void GameEnd::SetWave(int SWaveNumber)
{
	//波数
	__String* str = __String::createWithFormat("%02d", SWaveNumber);
	TextAtlas*curWaveText = TextAtlas::create(str->getCString(), "numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(460, 345));
	this->addChild(curWaveText, 2);
}

void GameEnd::SetMapIndex(int index)
{
	//重新开始
	Button* RestartGame = Button::create("retry_normal_CN.png", "retry_pressed_CN.png");
	RestartGame->setPosition(Vec2(350, 220));
	RestartGame->setScale(0.8f);
	this->addChild(RestartGame, 1);
	RestartGame->addClickEventListener([this,index](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		GameScene* gameScene = GameScene::create(index);
		director->replaceScene(gameScene);
	});

}
