#pragma warning(disable:4996)
#include"LoadingScene.h"
#include "GameScene.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;

LoadingScene* LoadingScene::create(int i)
{
	LoadingScene* ret = new LoadingScene();
	ret->index = i;
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

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Sprite* loadingBG = Sprite::create("loading\\loading.jpeg");
	loadingBG->setAnchorPoint(Vec2(0, 0));
	addChild(loadingBG, 0);

	Sprite* loadingTop = Sprite::create("loading\\fight_blood_top.png");
	loadingTop->setPosition(Vec2(480, 160));
	loadingTop->setScale(3.f);
	addChild(loadingTop, 1);

	loadingBar = ProgressTimer::create(Sprite::create("loading\\fight_blood_bg.png"));
	loadingBar->setPosition(Vec2(480, 160));
	loadingBar->setScale(3.f);
	loadingBar->setType(ProgressTimer::Type::BAR); // ��������
	loadingBar->setBarChangeRate(ccp(1, 0)); // ���ý������İ���x�����ƶ�
	loadingBar->setMidpoint(Point(0, 1)); // ���ý��ȵĽ��з���
	loadingBar->setPercentage(0);
	addChild(loadingBar, 2);

	// ������ʱ����ÿ0.1�����һ�ε���
	schedule(schedule_selector(LoadingScene::onScheduleCallBack), 0.1f);

	return true;
}

void LoadingScene::onScheduleCallBack(float dt)
{
	loadingBar->setPercentage(loadingBar->getPercentage() + 2.f);

	if (loadingBar->getPercentage() >= 100.f)
	{
		Director* director = Director::getInstance();
		GameScene* gameScene = GameScene::create(index);
		director->replaceScene(gameScene);
	}
}