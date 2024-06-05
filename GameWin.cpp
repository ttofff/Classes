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


	//�հ�ͼ
	Button* BK = Button::create("empty.png", "empty.png");
	BK->setPosition(Vec2(480, 320));
	this->addChild(BK, 0);
	BK->addClickEventListener([&](Ref* ref){
		Director* director = Director::getInstance();
	});


	//����ͼ
	Sprite* MenuBk = Sprite::create("Themes\\scene\\gameover0-hd\\win_bg.png");
	MenuBk->setPosition(Vec2(480, 320));
	this->addChild(MenuBk, 1);

	//����
	Sprite* GameOverText = Sprite::create("Themes\\scene\\gameover0-hd\\win_bg_CN.png");
	GameOverText->setPosition(Vec2(460, 320));
	this->addChild(GameOverText, 1);

	//ѡ��ؿ�
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

//��ʾ��ǰ����
void GameWin::SetWave(int SWaveNumber)
{
	//����
	__String* str = __String::createWithFormat("%02d", SWaveNumber);
	TextAtlas* curWaveText = TextAtlas::create(str->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(460, 345));
	this->addChild(curWaveText, 2);
}

//��ʾ�ܲ���
void GameWin::SetTotalWave()
{
	//����
	__String* str = __String::createWithFormat("%d", 15);
	TextAtlas* totalWaveText = TextAtlas::create(str->getCString(), "Themes\\scene\\gameover0-hd\\win_stagenum-hd.png", 16, 20, "0");
	totalWaveText->setPosition(Vec2(540, 345));
	this->addChild(totalWaveText, 2);
}

void GameWin::SetMapIndex(int index)
{
	//��ʾ��ǰ�ؿ�
	__String* str = __String::createWithFormat("%02d", index);
	TextAtlas* indexText = TextAtlas::create(str->getCString(), "Themes\\scene\\gameover0-hd\\win_stagenum-hd.png", 16, 20, "0");
	indexText->setPosition(Vec2(395, 290));
	this->addChild(indexText, 2);

	//���¿�ʼ
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
