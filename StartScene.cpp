#include "StartScene.h"

StartScene* StartScene::create()
{
	StartScene* ret = new StartScene();
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

bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 增加资源搜索路径
	FileUtils::getInstance()->addSearchPath("\\Themes\\scene\\mainscene1-hd");

	// 创建背景图
	Sprite* mainbg = Sprite::create("mainbg.png");
	mainbg->setPosition(Vec2(480, 320));
	this->addChild(mainbg, 0);

	// 创建开始界面——中心萝卜
	// 萝卜叶子1
	Sprite* mainCarrotLeaf_1 = Sprite::create("leaf-1.png");
	mainCarrotLeaf_1->setPosition(Vec2(420, 455));
	this->addChild(mainCarrotLeaf_1, 1);

	// 萝卜叶子3
	Sprite* mainCarrotLeaf_3 = Sprite::create("leaf-3.png");
	mainCarrotLeaf_3->setPosition(Vec2(560, 455));
	this->addChild(mainCarrotLeaf_3, 1);

	// 萝卜叶子2
	Sprite* mainCarrotLeaf_2 = Sprite::create("leaf-2.png");
	mainCarrotLeaf_2->setPosition(Vec2(490, 470));
	this->addChild(mainCarrotLeaf_2, 1);

	// 萝卜身体
	Sprite* mainCarrot = Sprite::create("carrot.png");
	mainCarrot->setPosition(Vec2(480, 360));
	this->addChild(mainCarrot, 1);

	// 创建开始界面——标题
	Sprite* mainTitle = Sprite::create("mainbg_CN.png");
	mainTitle->setPosition(Vec2(465, 265));
	this->addChild(mainTitle, 2);

	// 创建开始界面——精灵
	Sprite* mainBird = Sprite::create("bird.png");
	mainBird->setPosition(Vec2(180, 520));
	this->addChild(mainBird, 3);

	// 创建开始界面——免费宝石
	Sprite* freeStone = Sprite::create("btn_freestone.png");
	//freeStone->setRotation(45.f);
	freeStone->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	freeStone->setPosition(Vec2(960, 640));
	freeStone->setScale(1.f);
	this->addChild(freeStone, 1);

	return true;
}