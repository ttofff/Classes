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

	// ������Դ����·��
	FileUtils::getInstance()->addSearchPath("\\Themes\\scene\\mainscene1-hd");

	// ��������ͼ
	Sprite* mainbg = Sprite::create("mainbg.png");
	mainbg->setPosition(Vec2(480, 320));
	this->addChild(mainbg, 0);

	// ������ʼ���桪�������ܲ�
	// �ܲ�Ҷ��1
	Sprite* mainCarrotLeaf_1 = Sprite::create("leaf-1.png");
	mainCarrotLeaf_1->setPosition(Vec2(420, 455));
	this->addChild(mainCarrotLeaf_1, 1);

	// �ܲ�Ҷ��3
	Sprite* mainCarrotLeaf_3 = Sprite::create("leaf-3.png");
	mainCarrotLeaf_3->setPosition(Vec2(560, 455));
	this->addChild(mainCarrotLeaf_3, 1);

	// �ܲ�Ҷ��2
	Sprite* mainCarrotLeaf_2 = Sprite::create("leaf-2.png");
	mainCarrotLeaf_2->setPosition(Vec2(490, 470));
	this->addChild(mainCarrotLeaf_2, 1);

	// �ܲ�����
	Sprite* mainCarrot = Sprite::create("carrot.png");
	mainCarrot->setPosition(Vec2(480, 360));
	this->addChild(mainCarrot, 1);

	// ������ʼ���桪������
	Sprite* mainTitle = Sprite::create("mainbg_CN.png");
	mainTitle->setPosition(Vec2(465, 265));
	this->addChild(mainTitle, 2);

	// ������ʼ���桪������
	Sprite* mainBird = Sprite::create("bird.png");
	mainBird->setPosition(Vec2(180, 520));
	this->addChild(mainBird, 3);

	// ������ʼ���桪����ѱ�ʯ
	Sprite* freeStone = Sprite::create("btn_freestone.png");
	//freeStone->setRotation(45.f);
	freeStone->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	freeStone->setPosition(Vec2(960, 640));
	freeStone->setScale(1.f);
	this->addChild(freeStone, 1);

	return true;
}