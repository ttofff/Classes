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
	FileUtils::getInstance()->addSearchPath("Themes\\scene\\mainscene1-hd");

	//背景图
	Sprite* Background = Sprite::create("mainbg.png");
	Background->setPosition(Vec2(480, 320));
	this->addChild(Background,1);

	//中心萝卜
	Sprite* Carrot = Sprite::create("carrot.png");
	Carrot->setPosition(Vec2(480, 320));
	this->addChild(Carrot, 3);

	//第一片叶子
	Sprite* Leaf1 = Sprite::create("leaf-1.png");
	Leaf1->setPosition(Vec2(420, 410));
	this->addChild(Leaf1, 1);

	//第二片叶子
	Sprite* Leaf2 = Sprite::create("leaf-2.png");
	Leaf2->setPosition(Vec2(480, 430));
	this->addChild(Leaf2, 2);

	//第三片叶子
	Sprite* Leaf3 = Sprite::create("leaf-3.png");
	Leaf3->setPosition(Vec2(560, 420));
	this->addChild(Leaf3, 1);

	//标题
	Sprite* Tile = Sprite::create("mainbg_CN.png");
	Tile->setPosition(Vec2(480, 250));
	this->addChild(Tile, 4);

	//鸟
	Sprite* Bird = Sprite::create("bird.png");
	Bird->setPosition(Vec2(150, 500));
	this->addChild(Bird, 2);


	return true;
}
