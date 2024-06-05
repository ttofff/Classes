#include "GameWin.h"
#include "GameScene.h"
#include "AdventureFirstScene.h"
#include "ui\CocosGUI.h"
#include "iostream"

using namespace cocos2d::ui;

bool GameWin::init()
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
	Sprite* MenuBk = Sprite::create("Themes\\scene\\gameover0-hd\\win_bg.png");
	MenuBk->setPosition(Vec2(480, 320));
	this->addChild(MenuBk, 1);

	//文字
	Sprite* GameOverText = Sprite::create("Themes\\scene\\gameover0-hd\\win_bg_CN.png");
	GameOverText->setPosition(Vec2(460, 320));
	this->addChild(GameOverText, 1);

	//选择关卡
	Button* SelectGame = Button::create("Themes\\scene\\gamemenu-hd\\menu_quit_normal_CN.png", "Themes\\scene\\gamemenu-hd\\menu_quit_pressed_CN.png");
	SelectGame->setPosition(Vec2(360, 220));
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
void GameWin::SetWave(int SWaveNumber)
{
	//波数
	__String* str = __String::createWithFormat("%02d", SWaveNumber);
	TextAtlas* curWaveText = TextAtlas::create(str->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(460, 345));
	this->addChild(curWaveText, 2);
}

//显示总波数
void GameWin::SetTotalWave()
{
	//波数
	__String* str = __String::createWithFormat("%d", 15);
	TextAtlas* totalWaveText = TextAtlas::create(str->getCString(), "Themes\\scene\\gameover0-hd\\win_stagenum-hd.png", 16, 20, "0");
	totalWaveText->setPosition(Vec2(540, 345));
	this->addChild(totalWaveText, 2);
}

void GameWin::SetMapIndex(int index)
{
	//显示当前关卡
	__String* str = __String::createWithFormat("%02d", index);
	TextAtlas* indexText = TextAtlas::create(str->getCString(), "Themes\\scene\\gameover0-hd\\win_stagenum-hd.png", 16, 20, "0");
	indexText->setPosition(Vec2(395, 290));
	this->addChild(indexText, 2);

	//重新开始
	Button* RestartGame = Button::create("Themes\\scene\\gamemenu-hd\\menu_resume_normal_CN.png", "Themes\\scene\\gamemenu-hd\\menu_resume_normal_CN.png");
	RestartGame->setPosition(Vec2(570, 220));
	RestartGame->setScale(0.8f);
	this->addChild(RestartGame, 2);
	RestartGame->addClickEventListener([this, index](Ref* ref){
		Director* director = Director::getInstance();
		this->setVisible(false);
		Director::getInstance()->startAnimation();
		GameScene* gameScene = GameScene::create(index + 1, blockSize);
		director->replaceScene(gameScene);
	});

}

void GameWin::SetBlockSize(int size)
{
	this->blockSize = size;
}
