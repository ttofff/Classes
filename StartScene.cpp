#include "StartScene.h"
#include"ui\CocosGUI.h"

using namespace cocos2d::ui;

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

	// 萝卜叶子旋转间隔时间
	DelayTime* leafDealyTime = DelayTime::create(2.5f);

	// 萝卜叶子1
	Sprite* mainCarrotLeaf_1 = Sprite::create("leaf-1.png");
	mainCarrotLeaf_1->setPosition(Vec2(420, 455));
	this->addChild(mainCarrotLeaf_1, 1);

	// 萝卜叶子3
	Sprite* mainCarrotLeaf_3 = Sprite::create("leaf-3.png");
	mainCarrotLeaf_3->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mainCarrotLeaf_3->setPosition(Vec2(560, 395));
	this->addChild(mainCarrotLeaf_3, 1);

	// 萝卜叶子3旋转
	RotateBy* leaf3Rotate = RotateBy::create(.06f, 30);
	RotateBy* leaf3ReturnRotate = RotateBy::create(.06f, -30);
	Sequence* Leaf3Seq = Sequence::create(leafDealyTime, leaf3Rotate, leaf3ReturnRotate, leaf3Rotate, leaf3ReturnRotate, nullptr);
	RepeatForever* leaf3RF = RepeatForever::create(Leaf3Seq);
	mainCarrotLeaf_3->runAction(leaf3RF->clone());

	// 萝卜叶子2
	Sprite* mainCarrotLeaf_2 = Sprite::create("leaf-2.png");
	mainCarrotLeaf_2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mainCarrotLeaf_2->setPosition(Vec2(490, 400));
	this->addChild(mainCarrotLeaf_2, 1);

	// 萝卜叶子2旋转
	RotateBy* leaf2Rotate = RotateBy::create(.06f, 30);
	RotateBy* leaf2ReturnRotate = RotateBy::create(.06f, -30);
	Sequence* Leaf2Seq = Sequence::create(leaf2Rotate, leaf2ReturnRotate, leaf2Rotate, leaf2ReturnRotate, leafDealyTime, nullptr);
	RepeatForever* leaf2RF = RepeatForever::create(Leaf2Seq);
	mainCarrotLeaf_2->runAction(leaf2RF->clone());

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

	// 精灵上下移动
	MoveBy* birdMove = MoveBy::create(.8f, Vec2(0, -90));
	MoveBy* birdRetrunMove = MoveBy::create(.8f, Vec2(0, 90));
	Sequence* birdSeq = Sequence::create(birdMove, birdRetrunMove, nullptr);
	RepeatForever* birdRepeat = RepeatForever::create(birdSeq);
	mainBird->runAction(birdRepeat->clone());

	// 创建开始界面——logo
	Sprite* carrotLogo = Sprite::create("CarrotLogo.png");
	//freeStone->setRotation(45.f);
	//carrotLogo->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	carrotLogo->setPosition(Vec2(860, 570));
	carrotLogo->setScale(.1f);
	this->addChild(carrotLogo, 1);

	//logo变大变小
	ScaleBy* logoScale = ScaleBy::create(.8f, .5f);
	ScaleBy* logoReturnScale = ScaleBy::create(.8f, 2.f);
	Sequence* LogoSeq = Sequence::create(logoReturnScale, logoScale, nullptr);
	RepeatForever* logoRF = RepeatForever::create(LogoSeq);
	carrotLogo->runAction(logoRF->clone());

	//开始界面的按钮--冒险模式
	Button* btn_Adventure = Button::create("btn_adventure_normal_CN.png", "btn_adventure_pressed_CN.png");
	btn_Adventure->setPosition(Vec2(200, 50));
	btn_Adventure->setPressedActionEnabled(true);
	this->addChild(btn_Adventure);
	btn_Adventure->addClickEventListener([&](Ref* ref) {

	});

	//开始界面的按钮--boss模式
	Button* btn_Boss = Button::create("btn_boss_normal_CN.png", "btn_boss_pressed_CN.png");
	btn_Boss->setPosition(Vec2(480, 60));
	btn_Boss->setPressedActionEnabled(true);
	this->addChild(btn_Boss);
	btn_Boss->addClickEventListener([&](Ref* ref) {

	});

	//开始界面的按钮--怪兽窝
	Button* btn_Monster = Button::create("btn_nest_normal_CN.png", "btn_nest_pressed_CN.png");
	btn_Monster->setPosition(Vec2(760, 50));
	btn_Monster->setPressedActionEnabled(true);
	this->addChild(btn_Monster);
	btn_Monster->addClickEventListener([&](Ref* ref) {

	});


	return true;
}