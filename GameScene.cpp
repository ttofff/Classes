#pragma warning(disable:4996)
#include"Monster.h"
#include "GameScene.h"
#include "ui\CocosGUI.h"
#include "AdventureScene.h"
#include "Gamepause.h"
#include "GameEnd.h"
#include "SimpleAudioEngine.h"
#include "AdventureFirstScene.h"
#include "Tower.h"
#include "Bullet.h"

using namespace cocos2d::ui;



GameScene* GameScene::create(int i)
{
	GameScene* ret = new GameScene();
	ret->money = 300;
	ret->index = i;
	ret->hp = 10;
	ret->Wave_Number = 1;
	
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


//���ֹ���
void GameScene::update(float dt)
{
	static float waittime = 1.0f;
	waittime = waittime - dt;
	if (waittime <= 0.f){
		waittime = 1.0f;
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music\\Items\\GO.mp3"); //������Ч
		Monster* newmonster = Monster::create((MonsterType)((rand() % 8) + 1));		//�����µĹ���
		newmonster->onMonsterInit(tiledMap->wayPoints);
		monster.pushBack(newmonster);				//�������������
		this->addChild(monster.back());
	}

		for (int i = 0; i < monster.size(); i++)
		{
			Monster* pm = monster.at(i);
			if (!pm->onMonsterUpdate(dt)){					//����Ե��ܲ�
				Sprite* spBoom = Sprite::create();			//������ʧ����
				this->addChild(spBoom, 3);
				spBoom->setPosition(pm->getPosition());
				Animation* ani = Animation::create();
				ani->addSpriteFrameWithFile("Themes\\Items\\Items02-hd\\air01.png");
				ani->addSpriteFrameWithFile("Themes\\Items\\Items02-hd\\air02.png");
				ani->addSpriteFrameWithFile("Themes\\Items\\Items02-hd\\air03.png");
				ani->addSpriteFrameWithFile("Themes\\Items\\Items02-hd\\air04.png");
				ani->addSpriteFrameWithFile("Themes\\Items\\Items02-hd\\air05.png");
				ani->setLoops(1);
				ani->setDelayPerUnit(0.1f);
				spBoom->runAction(Sequence::create(Animate::create(ani), RemoveSelf::create(), nullptr));
				this->removeChild(pm);
				monster.erase(monster.begin() + i);
				hp--;
				//�ж��Ƿ�����
				if (hp >= 1)
				{
					__String* carrotlj = __String::createWithFormat("Themes\\Items\\Items01-hd\\hlb%d.png", hp);

					ca->setTexture(carrotlj->getCString());

				}
				else if (hp <= 0)
				{
					CarrotDead();
				}
			}
		}

		float SlowSpeed = 150.f;
		int Damage = 20;
		// �������е�����û������ʱ�򣬾Ͳ��ᷢ���ӵ�
		for (Tower* tower : towers)
		{
			// �ж������ʱ���Ƿ���������
			if (tower->onTowerUpdate(dt))
			{
				for (Monster* monster : monster)
				{
					// ����ڷ�Χ֮�ڣ������ӵ�
					if (tower->shoot(monster))
					{
						SetTowerAnim(tower);
						// �����ӵ�
						Bullet* bullet = Bullet::create(tower->type);
						// �����ӵ�λ���� ��ǰ ��������ͬ
						bullet->setPosition(tower->getPosition());
						// ��ʼ���ӵ�
						bullet->onBulletInit(monster);
						// ���ӵ���ӵ�����
						this->addChild(bullet);
						// ���ӵ���ӵ��ӵ�������
						bullets.pushBack(bullet);
						
						break;    // ����Ҫ
					}
				}
				
			}
		}
		for (int i = 0; i < bullets.size(); i++)
		{
			Bullet* bullet = bullets.at(i);
			Monster* Targetmonster = bullet->target;
			bool IsHave = false;
			switch (bullet->type)
			{
			case BOTTLE:
				SlowSpeed = 150.f;
				Damage = 20;
				break;
			case SHIT:
				SlowSpeed = 50.f;
				Damage = 10;
				break;
			}
			for (auto monster : monster)
			{
				if (monster == bullet->target)
				{
					IsHave = true;
					break;
				}
			}
			if (!IsHave)
			{
				bullets.eraseObject(bullet); // �ڴ棺�������Ƴ�
				bullet->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				continue;
			}
			bool isCrash = Targetmonster->getBoundingBox().containsPoint(bullet->getPosition());
			if (isCrash)
			{
				// ���������Ѫ
				Targetmonster->hp -= Damage;
				Targetmonster->SetSpeed(SlowSpeed);
				// �������Ƿ�����
				if (Targetmonster->hp <= 0)
				{
					Targetmonster->hp = 0;
					// �����¾��������Ź�������֡����
					Sprite* spBoom = Sprite::create("Map\\MonsterDead\\Dead_01.png");
					this->addChild(spBoom);
					// ����λ�ã������λ�ã�
					spBoom->setPosition(Vec2(Targetmonster->getPositionX(), Targetmonster->getPositionY()+20.f));
					Animation* monsterdead = Animation::create();
					for (int i = 1; i < 15; ++i) {
						__String* str = __String::createWithFormat("Map\\MonsterDead\\Dead_%02d.png", i);
						monsterdead->addSpriteFrameWithFile(str->getCString());
					}
					monsterdead->setDelayPerUnit(0.1f);
					monsterdead->setLoops(1);
					Animate* animate = Animate::create(monsterdead);
					// �Ƴ�����
					RemoveSelf* removeSelf = RemoveSelf::create();
					// ���ж���
					Sequence* seq = Sequence::create(animate, removeSelf, nullptr);
					spBoom->runAction(seq);
					// �Ƴ�����
					monster.eraseObject(Targetmonster);
					this->removeChild(Targetmonster);
					// ������������+1(�����������)

					// ��������ý��
					money += rand() % 21 + 10;// 80 - 180
					// �޸Ľ���ı�
					char text[10];
					sprintf(text, "%d", money);
					moneyT->setString(text);
				}


				// ���ӵ������кͳ������Ƴ�
				bullets.eraseObject(bullet);
				bullet->removeFromParent();
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			Bullet* bullet = bullets.at(i);
			bool isDie = true;    // ��ǰ�ӵ� �� ����Ŀ�� �� ���״̬
			// ���������������û���ҵ����ӵ��Ĺ���Ŀ�꣬��ʾ�����Ѿ�����
			for (Monster* monster : monster)
			{
				if (monster == bullet->target)
				{
					isDie = false;
					break;
				}
			}
			// �������Ŀ������,���ӵ��������кͲ����Ƴ�
			if (isDie)
			{
				bullets.eraseObject(bullet); // �ڴ棺�������Ƴ�
				bullet->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				continue;
			}
			bullet->onBulletUpdate(dt);// �����ӵ��ƶ�
		}
}


//�ܲ�����
void GameScene::CarrotDead()
{
	Director* director = Director::getInstance();
	gameEnd->SetWave(Wave_Number);
	gameEnd->SetMapIndex(index);
	gameEnd->setVisible(true);

	this->scheduleOnce([director](float dt){
		director->stopAnimation();
	}, 0.1f, "delayed_key");

}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}


	//��ͣ�˵�
	Gamepause* gamepause = Gamepause::create();
	this->addChild(gamepause, 5);
	gamepause->setVisible(false);

	//ʧ�ܽ���
	gameEnd = GameEnd::create();
	this->addChild(gameEnd, 5);
	gameEnd->setVisible(false);

	// ���ɹؿ�ͼ
	__String *str;
	if (AdventureFirstScene::bigcheck==1)
		str = __String::createWithFormat("Map\\FirstKind\\Environment\\Level%02d\\Level.tmx",index);
	else if (AdventureFirstScene::bigcheck==2)
		str = __String::createWithFormat("Map\\SecondKind\\Environment\\Level%02d\\Level.tmx", index);
	else str = __String::createWithFormat("Map\\ThirdKind\\Environment\\Level%02d\\Level.tmx", index);
	tiledMap = GameMap::create(str->getCString());
	tiledMap->setPosition(Vec2::ZERO);
	this->addChild(tiledMap, 0);
	
	

	


	//����
	tiledMap->getWayPoints("PATH"); //��ȡ�����ƶ�·��
	tiledMap->getTowerArea("OBJ");		//��ȡ������������

	//�ܲ�
	ca = Sprite::create("wei.jpg");
	
	ca->setPosition(tiledMap->wayPoints.back());
	this->addChild(ca, 2);
	ca->getPosition();

	scheduleUpdate();


	// �˵�������
	Sprite* menuBG = Sprite::create("Themes\\Items\\touming-hd\\MenuBG.png");
	menuBG->setAnchorPoint(Vec2(0.5, 1));
	menuBG->setPosition(Vec2(480, 640));
	this->addChild(menuBG, 1);

	// �������
	__String* s = __String::createWithFormat("%d", money);
	moneyT = TextAtlas::create(s->getCString(), "Themes\\Items\\numwhite-hd.png", 20, 40, ".");
	moneyT->setPosition(Vec2(120, 610));
	this->addChild(moneyT, 2);

	// ��ʾ��ǰ�������ܲ�������
	Sprite* menuCenter = Sprite::create("Themes\\Items\\Items02-hd\\MenuCenter_01_CN.png");
	menuCenter->setPosition(Vec2(463, 45));
	menuBG->addChild(menuCenter, 1);

	//��ǰ����
	__String* SWaveNumber = __String::createWithFormat("%02d", Wave_Number);
	TextAtlas*curWaveText = TextAtlas::create(SWaveNumber->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(390, 45));
	menuBG->addChild(curWaveText, 2);

	//�ܲ���
	TextAtlas*totalWaveText = TextAtlas::create("15", "Themes\\Items\\numwhite-hd.png", 20, 40, ".");
	totalWaveText->setPosition(Vec2(480, 45));
	menuBG->addChild(totalWaveText, 2);

	// ȫ���ٶȱ���
	CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
	pScheduler->setTimeScale(1.f);

	// 1���ٰ�ť
	Button* btn_speed = Button::create("Themes\\Items\\touming-hd\\speed11.png", "Themes\\Items\\touming-hd\\speed12.png");
	btn_speed->setPosition(Vec2(725, 605));
	this->addChild(btn_speed, 2);

	// 2���ٰ�ť
	Button* btn_speed_two = Button::create("Themes\\Items\\touming-hd\\speed21.png", "Themes\\Items\\touming-hd\\speed22.png");
	btn_speed_two->setPosition(Vec2(725, 605));
	this->addChild(btn_speed_two, 2);
	btn_speed_two->setVisible(false);

	// ���ٰ�ť����¼�
	btn_speed->addClickEventListener([pScheduler, btn_speed, btn_speed_two](Ref* ref) {
		pScheduler->setTimeScale(2.f);
		btn_speed->setVisible(false);
		btn_speed_two->setVisible(true);
	});
	btn_speed_two->addClickEventListener([pScheduler, btn_speed, btn_speed_two](Ref* ref) {
		pScheduler->setTimeScale(1.f);
		btn_speed->setVisible(true);
		btn_speed_two->setVisible(false);
	});

	//��ͣ��
	Sprite* btn_stop = Sprite::create("Themes\\Items\\Items02-hd\\MenuCenter_02_CN.png");
	btn_stop->setPosition(Vec2(480, 320));
	btn_stop->setVisible(false);
	this->addChild(btn_stop, 2);

	// ��ͣ��ť
	Button* btn_pause = Button::create("Themes\\Items\\touming-hd\\pause11.png", "Themes\\Items\\touming-hd\\pause12.png");
	btn_pause->setPosition(Vec2(825, 605));
	btn_pause->setVisible(false);
	this->addChild(btn_pause, 2);

	// ��ʼ��ť
	Button* btn_go = Button::create("Themes\\Items\\touming-hd\\pause01.png", "Themes\\Items\\touming-hd\\pause02.png");
	btn_go->setPosition(Vec2(825, 605));
	btn_go->setVisible(true);
	this->addChild(btn_go, 2);


	// �˵���ť
	Button* btn_menu = Button::create("Themes\\Items\\touming-hd\\menu01.png", "Themes\\Items\\touming-hd\\menu02.png");
	btn_menu->setPosition(Vec2(890, 605));
	this->addChild(btn_menu, 2);
	btn_menu->addClickEventListener([this,gamepause, btn_speed,btn_menu](Ref* ref) 
	{
		Director* director = Director::getInstance();
		gamepause->setVisible(true);
		gamepause->RestartMap(index);
		this->scheduleOnce([director](float dt){
			director->stopAnimation();
		}, 0.1f, "delayed_key");
		
	});

	// ��ͣ����ʼ����¼�
	btn_pause->addClickEventListener([ btn_go, btn_pause, btn_stop, btn_speed, btn_menu](Ref* ref) {
		btn_go->setVisible(true);
		btn_stop->setVisible(false);
		btn_pause->setVisible(false);
		Director::getInstance()->startAnimation();

		btn_speed->setTouchEnabled(true);
		btn_menu->setTouchEnabled(true);
	});
	btn_go->addClickEventListener([btn_go, btn_pause, btn_stop, btn_speed, btn_menu](Ref* ref) {
		btn_go->setVisible(false);
		btn_stop->setVisible(true);
		btn_pause->setVisible(true);
		Director::getInstance()->stopAnimation();

		btn_speed->setTouchEnabled(false);
		btn_menu->setTouchEnabled(false);
	});

	createBuildTool();		//������������

	EventListenerTouchOneByOne* eventListenerTouchOneByOne = EventListenerTouchOneByOne::create();
	eventListenerTouchOneByOne->onTouchBegan = [this](Touch* touch,Event *event)
	{
		//���������Ƿ�ɼ�
		if (select->isVisible())
		{
			select->setVisible(false);
			return true;
		}
		//��ȡ��ǰ�����·����
		Vec2 touchPoint = touch->getLocation();
		float x = (int)touchPoint.x / 80 * 80 + 40;
		float y = (int)touchPoint.y / 80 * 80 + 40;
		//�Ƿ�����
		for (Tower* tower : towers)
		{
			if (fabs(tower->getPositionX() - x) < 0.000001 &&
				fabs(tower->getPositionY() - y) < 0.000001)
			{
				return true;
			}
		}
		//�����=�ڽ���������
		for (Rect rect : tiledMap->towerArea)
		{
			if (rect.containsPoint(touchPoint))
			{
				createBuildTool();
				select->setVisible(true);
				select->setPosition(Vec2(x, y));
				return true;
			}
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListenerTouchOneByOne, this);

	
	
	// �ܲ�ͼ��
	
	
	// �ܲ���������
	/*
	Animation* carrotAnimation = Animation::create();
	carrotAnimation->addSpriteFrameWithFile("hlb11.png");
	carrotAnimation->addSpriteFrameWithFile("hlb12.png");
	carrotAnimation->addSpriteFrameWithFile("hlb13.png");
	carrotAnimation->addSpriteFrameWithFile("hlb14.png");
	carrotAnimation->addSpriteFrameWithFile("hlb15.png");
	carrotAnimation->addSpriteFrameWithFile("hlb16.png");
	carrotAnimation->addSpriteFrameWithFile("hlb17.png");
	carrotAnimation->addSpriteFrameWithFile("hlb18.png");
	carrotAnimation->setLoops(CC_REPEAT_FOREVER);
	carrotAnimation->setDelayPerUnit(0.1f);
	Animate* pAnimate = Animate::create(carrotAnimation);
	ca->runAction(pAnimate);
	*/
	return true;
}




// ��������ѡ�񹤾�
void GameScene::createBuildTool()
{
	// ����ѡ�񹤾�,��ʱ����
	select = Sprite::create("Themes\\Items\\Items02-hd\\select_01.png");
	select->setVisible(false);
	this->addChild(select);
	select->setLocalZOrder(2);// ����zOrder

	// ������ͼ�꣺�����Tomer�У�������µ��������ͣ����������
	Button* bottle;
	if (money>=100)
		bottle = Button::create("Themes\\Towers\\TBottle-hd\\Bottle01.png");
	else  bottle = Button::create("Themes\\Towers\\TBottle-hd\\Bottle00.png");
	bottle->setPosition(Vec2(-10, 110));
	select->addChild(bottle);

	Button* shit;
	if (money>=120)
		shit = Button::create("Themes\\Towers\\TShit-hd\\Shit01.png");
	else  shit = Button::create("Themes\\Towers\\TShit-hd\\Shit00.png");
	shit->setPosition(Vec2(82, 110));
	select->addChild(shit);

	// �����ͬ����ͼ�꣬������ͬ����
	bottle->addClickEventListener([this](Ref*)
	{
		// �����Ҳ��������ܽ���
		if (money < 100)
		{
			select->setVisible(false);
			return;
		}
		// ����Bottle��,������ѡ�񹤾�
		Tower* bottle = Tower::create(BOTTLE);
		bottle->setPosition(select->getPosition());
		this->addChild(bottle);
		select->setVisible(false);
		// ����init����
		bottle->onTowerInit();
		// ������ӵ�������
		towers.push_back(bottle);
		// �������Ľ��
		money -= 100;
		// �޸Ľ���ı�
		char text[10];
		sprintf(text, "%d", money);
		moneyT->setString(text);
	});

	shit->addClickEventListener([this](Ref*)
	{
		// �����Ҳ��������ܽ���
		if (money < 120)
		{
			select->setVisible(false);
			return;
		}
		// ����Bottle��,������ѡ�񹤾�
		Tower* shit = Tower::create(SHIT);
		shit->setPosition(select->getPosition());
		this->addChild(shit);
		select->setVisible(false);
		// ����init����
		shit->onTowerInit();
		//// ������ӵ�������
		towers.push_back(shit);
		// �������Ľ��
		money -= 120;
		// �޸Ľ���ı�
		char text[10];
		sprintf(text, "%d", money);
		moneyT->setString(text);
	});
}
void GameScene::SetTowerAnim(Tower* tower)
{
	//�������
	Sprite* shootsp = Sprite::create();
	this->addChild(shootsp);
	shootsp->setRotation(tower->getRotation());
	shootsp->setPosition(tower->getPosition());
	Animation* pAnimation = Animation::create();
	__String* TowerAnim;
	switch (tower->type)
	{
	case BOTTLE:
		TowerAnim = __String::createWithFormat("Themes\\Towers\\TBottle-hd\\Bottle1");
		break;
	case SHIT:
		TowerAnim = __String::createWithFormat("Themes\\Towers\\TShit-hd\\Shit1");
		break;
	}
	for (int i = 0; i < 4; ++i) {
		__String* str = __String::createWithFormat("%s%d.png", TowerAnim->getCString(), i%3 + 1);
		pAnimation->addSpriteFrameWithFile(str->getCString());
	}
	pAnimation->setLoops(1);
	pAnimation->setDelayPerUnit(0.1f);
	tower->runAction(Sequence::create(Animate::create(pAnimation), nullptr));

}