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

	
	//空白图
	Button* BK = Button::create("empty.png", "empty.png");
	BK->setPosition(Vec2(480, 320));
	this->addChild(BK, 0);
	BK->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
	});


	//背景图
	Sprite* MenuBk = Sprite::create("Themes\\scene\\gameover0-hd\\lose_bg.png");
	MenuBk->setPosition(Vec2(480, 320));
	this->addChild(MenuBk, 1);

	//文字
	Sprite* GameOverText = Sprite::create("Themes\\scene\\gameover0-hd\\lose_bg_CN.png");
	GameOverText->setPosition(Vec2(460, 320));
	this->addChild(GameOverText, 1);

	//选择关卡
	Button* SelectGame = Button::create("Themes\\scene\\gameover-hd\\select_normal_CN.png", "Themes\\scene\\gameover-hd\\select_pressed_CN.png");
	SelectGame->setPosition(Vec2(570, 220));
	SelectGame->setScale(0.8f);
	this->addChild(SelectGame, 2);
	SelectGame->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		AdventureFirstScene* adventureFirstScene = AdventureFirstScene::create(AdventureFirstScene::bigcheck);
		director->replaceScene(adventureFirstScene);
	});

	return true;
}

//显示当前波数
void GameEnd::SetWave(int SWaveNumber)
{
	//波数
	__String* str = __String::createWithFormat("%02d", SWaveNumber);
	TextAtlas* curWaveText = TextAtlas::create(str->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(460, 345));
	this->addChild(curWaveText, 2);
}

//显示总波数
void GameEnd::SetTotalWave()
{
	//波数
	__String* str = __String::createWithFormat("%d", 15);
	TextAtlas* totalWaveText = TextAtlas::create(str->getCString(), "Themes\\scene\\gameover0-hd\\win_stagenum-hd.png", 16, 20, "0");
	totalWaveText->setPosition(Vec2(540, 345));
	this->addChild(totalWaveText, 2);
}

void GameEnd::SetMapIndex(int index)
{
	//显示当前关卡
	__String* str = __String::createWithFormat("%02d", index);
	TextAtlas* indexText = TextAtlas::create(str->getCString(), "Themes\\scene\\gameover0-hd\\win_stagenum-hd.png", 16, 20, "0");
	indexText->setPosition(Vec2(395, 290));
	this->addChild(indexText, 2);

	//重新开始
	Button* RestartGame = Button::create("Themes\\scene\\gameover-hd\\retry_normal_CN.png", "Themes\\scene\\gameover-hd\\retry_pressed_CN.png");
	RestartGame->setPosition(Vec2(360, 220));
	RestartGame->setScale(0.8f);
	this->addChild(RestartGame, 2);
	RestartGame->addClickEventListener([this,index](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		GameScene* gameScene = GameScene::create(index, blockSize);
		director->replaceScene(gameScene);
	});

}

void GameEnd::SetBlockSize(int size)
{
	this->blockSize = size;
}
