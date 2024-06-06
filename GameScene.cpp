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

GameScene* GameScene::create(int i, int size, int kind)
{
	GameScene* ret = new GameScene();
	ret->money = 300;
	ret->index = i;
	ret->hp = 10;
	ret->Wave_Number = 1;
	ret->TowerAllSelect = { {1},{ 1, 2 }, { 1, 2, 3 }, { 1, 2, 4 }, { 2, 4 }, { 2, 3 }, { 1, 2, 3, 4 } };
	ret->TowerSelect = ret->TowerAllSelect[ret->index - 1];
	ret->blockSize = size;
	ret->monsterNum = (rand() % (15 + ret->index + ret->Wave_Number)) + (5 + ret->index + ret->Wave_Number);
	ret->monsterKind = kind;
	
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
	if (monsterNum > 0)
	{
		if (waittime <= 0.f)
		{
			waittime = 1.0f;
			monsterNum--;
			Monster* newmonster = Monster::create((MonsterType)((rand() % 8) + 1), monsterKind);		//�����µĹ���
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music\\Items\\GO.mp3"); //������Ч
			if (Wave_Number == 15 && monsterNum == 1)
			{
				newmonster->setScale(2.f);
				newmonster->hp = newmonster->hp * 50;
			}
			newmonster->onMonsterInit(tiledMap->wayPoints);
			if (monsterKind == 2)
			{
				newmonster->setScale(2.f);
				newmonster->setAnchorPoint(Vec2(0.5, 0.5));
			}
			monster.pushBack(newmonster);				//�������������
			this->addChild(monster.back());
		}
	}
	else if (monster.empty())
	{
		waittime = 5.f;
		if (Wave_Number < 15)
		{
			Wave_Number++;
		}
		else
		{
			CarrotWin();
		}
		monsterNum = (rand() % (15 + index + Wave_Number)) + (5 + index + Wave_Number);

		menuBG->removeChild(curWaveText, 0);
		__String* SWaveNumber = __String::createWithFormat("%02d", Wave_Number);
		curWaveText = TextAtlas::create(SWaveNumber->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
		curWaveText->setPosition(Vec2(390, 45));
		menuBG->addChild(curWaveText, 2);
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
		//int Damage = 20;
		// �������е�����û������ʱ�򣬾Ͳ��ᷢ���ӵ�
		for (Tower* tower : towers)
		{
			// �ж������ʱ���Ƿ���������
			if (tower->onTowerUpdate(dt))
			{
				if (!isselect)
					for (Monster* monster : monster)
					{
					
						// ����ڷ�Χ֮�ڣ������ӵ�
						if (tower->shoot(monster))
						{
							SetTowerAnim(tower);
							// �����ӵ�
							Bullet* bullet = Bullet::create(tower->type,tower->Uptime);
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
				else 
					for (Monster* monster : monster)
					{
						if (monster == monsterselect)
						// ����ڷ�Χ֮�ڣ������ӵ�
						if (tower->shoot(monster))
						{
							SetTowerAnim(tower);
							// �����ӵ�
							Bullet* bullet = Bullet::create(tower->type, tower->Uptime);
							// �����ӵ�λ���� ��ǰ ��������ͬ
							bullet->setPosition(Vec2(tower->getPositionX(), tower->getPositionY() + 10));
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
			//Monster* Targetmonster = bullet->target;
			bool IsHave = false;
			
			switch (bullet->type)
			{
			case BOTTLE:
				SlowSpeed = 150.f;
				//Damage = 20;
				break;
			case SHIT:
				SlowSpeed = 50.f;
				//Damage = 10;
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
				if (bullet->type != FAN)
				{
					bullets.eraseObject(bullet);
					bullet->removeFromParent();
					continue;
				}
				Vec2 pos = bullet->getPosition();
				if (pos.x > 1000 || pos.x < -1000 || pos.y>1000 || pos.y < -1000)
				{
					bullets.eraseObject(bullet);
					bullet->removeFromParent();
					continue;
				}
				
			}
			for (int i = 0; i < monster.size(); ++i)
			{
				Monster* Targetmonster = monster.at(i);
				bool isCrash = Targetmonster->getBoundingBox().containsPoint(bullet->getPosition());
				if (isCrash)
				{
					// �����Ѫ
					if (bullet->damage && isCrash)
					{
						SetHitAnim(Vec2(Targetmonster->getPositionX(), Targetmonster->getPositionY() + 20), bullet);
					}
					Targetmonster->hp -= bullet->damage;
					Targetmonster->SetSpeed(SlowSpeed);
					switch (bullet->type)
					{
					case FAN: bullet->damage = 0;
						this->scheduleOnce([bullet](float dt){
							bullet->damage = 15 * (bullet->bulletlevel + 1);
						}, 0.05f, "delayed_key");
						break;
					}
					// �������Ƿ�����
					if (Targetmonster->hp <= 0)
					{
						Targetmonster->hp = 0;
						// �����¾��������Ź�������֡����
						if (monsterselect == Targetmonster)
							isselect = false;
						Sprite* spBoom = Sprite::create("Map\\MonsterDead\\Dead_01.png");
						this->addChild(spBoom);
						// ����λ�ã������λ�ã�
						spBoom->setPosition(Vec2(Targetmonster->getPositionX(), Targetmonster->getPositionY() + 30.f));
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
					if (bullet->type != FAN)
					{
					bullets.eraseObject(bullet);
					bullet->removeFromParent();
					break;
					}
					Vec2 pos = bullet->getPosition();
					if (pos.x > 1000 || pos.x < -1000 || pos.y>1000 || pos.y < -1000)
					{
						bullets.eraseObject(bullet);
						bullet->removeFromParent();
						break;
					}
				
				}
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
				if (bullet->type != FAN)
				{
					bullets.eraseObject(bullet);
					bullet->removeFromParent();
					continue;
				}
			}
			Vec2 pos = bullet->getPosition();
			if (pos.x > 1000 || pos.x < -1000 || pos.y>1000 || pos.y < -1000)
			{
				bullets.eraseObject(bullet);
				bullet->removeFromParent();	
				continue;
			}
			bullet->onBulletUpdate(dt);// �����ӵ��ƶ�
		}
}

void GameScene::CarrotWin()
{
	Director* director = Director::getInstance();
	gameEnd->SetWinInterface();
	gameEnd->SetWave(Wave_Number);
	gameEnd->SetNextIndex(index);
	gameEnd->setVisible(true);

	this->scheduleOnce([director](float dt){
		director->stopAnimation();
	}, 0.1f, "delayed_key");

}

//�ܲ�����
void GameScene::CarrotDead()
{
	Director* director = Director::getInstance();
	gameEnd->SetLoseInterface();
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
	gamepause = Gamepause::create();
	gamepause->SetBlockSize(blockSize);
	gamepause->SetMonsterKind(monsterKind);
	this->addChild(gamepause, 5);
	gamepause->setVisible(false);

	//��������
	gameEnd = GameEnd::create();
	gameEnd->SetBlockSize(blockSize);
	gameEnd->SetMonsterKind(monsterKind);
	gameEnd->SetTotalWave();
	gameEnd->SetCurrIndex(index);
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
	menuBG = Sprite::create("Themes\\Items\\touming-hd\\MenuBG.png");
	menuBG->setAnchorPoint(Vec2(0.5, 1));
	menuBG->setPosition(Vec2(480, 640));
	this->addChild(menuBG, 1);

	// �������
	__String* s = __String::createWithFormat("%d", money);
	moneyT = TextAtlas::create(s->getCString(), "Themes\\Items\\numwhite-hd.png", 20, 40, ".");
	moneyT->setPosition(Vec2(130, 610));
	this->addChild(moneyT, 2);

	// ��ʾ��ǰ�������ܲ�������
	Sprite* menuCenter = Sprite::create("Themes\\Items\\Items02-hd\\MenuCenter_01_CN.png");
	menuCenter->setPosition(Vec2(463, 45));
	menuBG->addChild(menuCenter, 1);

	//��ǰ����
	__String* SWaveNumber = __String::createWithFormat("%02d", Wave_Number);
	curWaveText = TextAtlas::create(SWaveNumber->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(390, 45));
	menuBG->addChild(curWaveText, 2);

	//�ܲ���
	totalWaveText = TextAtlas::create("15", "Themes\\Items\\numwhite-hd.png", 20, 40, ".");
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
	btn_menu->addClickEventListener([this, btn_speed, btn_menu](Ref* ref) 
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
	Upselect = Sprite::create("Themes\\Items\\Items02-hd\\select_00.png");
	Upselect->setVisible(false);
	this->addChild(Upselect);


	EventListenerTouchOneByOne* eventListenerTouchOneByOne = EventListenerTouchOneByOne::create();
	eventListenerTouchOneByOne->onTouchBegan = [this](Touch* touch,Event *event)
	{
		isselect = false;
		//���������Ƿ�ɼ�
		if (select->isVisible())
		{
			select->setVisible(false);
			return true;
		}
		if (Upselect->isVisible())
		{
			Upselect->setVisible(false);
			return true;
		}
		//��ȡ��ǰ�����·����
		Vec2 touchPoint = touch->getLocation();
		float x = (int)touchPoint.x / blockSize * blockSize + blockSize / 2;
		float y = (int)touchPoint.y / blockSize * blockSize + blockSize / 2;
		float dx = (int)touchPoint.x / 80 * 80 + 80 / 2;
		float dy = (int)touchPoint.y / 80 * 80 + 80 / 2;
		//�Ƿ�����
		for (Tower* tower : towers)
		{
			if (fabs(tower->getPositionX() - x) < 0.000001 &&
				fabs(tower->getPositionY() - y) < 0.000001)
			{
				create_UpTool(tower, tower->Uptime);
				Upselect->setVisible(true);
				Upselect->setPosition(Vec2(x, y));
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
		for (Monster* m : monster)
		{
			bool is;
			is=m->getBoundingBox().containsPoint(touch->getLocation());
			if (is)
			{
				isselect = true;
				monsterselect = m;
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

void GameScene::create_UpTool(Tower* tower, int time)
{
	Upselect = Sprite::create("Themes\\Items\\Items02-hd\\select_00.png");
	Upselect->setVisible(false);
	this->addChild(Upselect);
	Upselect->setLocalZOrder(2);// ����zOrder,ͼ�����ȼ�
	if (tower->type==TowerType::BOTTLE)
	{
		if (time == 0)  //ƿ����������Ϊ0
		{
			Button *bottle;
			if (money >= 180)
				bottle = Button::create("Themes\\Items\\Items02-hd\\upgrade_180.png");
			else bottle = Button::create("Themes\\Items\\Items02-hd\\upgrade_-180.png");
			bottle->setPosition(Vec2(-10, 110));
			Upselect->addChild(bottle);
			bottle->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 180)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* bottle = Tower::create(BOTTLE, 1);
				bottle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				bottle->setPosition(Upselect->getPosition());
				bottle->dzsp = Sprite::create(bottle->dz->getCString());
				bottle->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				bottle->dzsp->setPosition(Vec2(bottle->getPositionX(), bottle->getPositionY() - 10));
				this->addChild(bottle->dzsp, 1);
				this->addChild(bottle, 2);
				Upselect->setVisible(false);
				// ����init����
				bottle->onTowerInit();
				// ������ӵ�������
				towers.pushBack(bottle);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 180;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_80.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 80;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   if(time==1)//��������Ϊ1
		{
			Button *bottle;
			if (money >= 320)
				bottle = Button::create("Themes\\Items\\Items02-hd\\upgrade_320.png");
			else bottle = Button::create("Themes\\Items\\Items02-hd\\upgrade_-320.png");
			bottle->setPosition(Vec2(-10, 110));
			Upselect->addChild(bottle);
			bottle->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 320)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* bottle = Tower::create(BOTTLE, 2);
				bottle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				bottle->setPosition(Upselect->getPosition());
				bottle->dzsp = Sprite::create(bottle->dz->getCString());
				bottle->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				bottle->dzsp->setPosition(Vec2(bottle->getPositionX(), bottle->getPositionY() - 10));
				this->addChild(bottle->dzsp, 1);
				this->addChild(bottle, 2);
				Upselect->setVisible(false);
				// ����init����
				bottle->onTowerInit();
				// ������ӵ�������
				towers.pushBack(bottle);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 320;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_144.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 144;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   //��������Ϊ2
		{
			Sprite *bottle;
			bottle = Sprite::create("Themes\\Items\\Items02-hd\\upgrade_0_CN.png");
			bottle->setPosition(Vec2(-10, 110));
			Upselect->addChild(bottle);
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_272.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 272;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
	}
	else if (tower->type == TowerType::SHIT)
	{
		if (time == 0)  //shit��������Ϊ0
		{
			Button *shit;
			if (money >= 220)
				shit = Button::create("Themes\\Items\\Items02-hd\\upgrade_220.png");
			else shit = Button::create("Themes\\Items\\Items02-hd\\upgrade_-220.png");
			shit->setPosition(Vec2(-10, 110));
			Upselect->addChild(shit);
			shit->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 220)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* shit = Tower::create(SHIT, 1);
				shit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				shit->setPosition(Upselect->getPosition());
				shit->dzsp = Sprite::create(shit->dz->getCString());
				shit->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				shit->dzsp->setPosition(Vec2(shit->getPositionX(), shit->getPositionY() - 20));
				this->addChild(shit->dzsp, 1);
				this->addChild(shit, 2);
				Upselect->setVisible(false);
				// ����init����
				shit->onTowerInit();
				// ������ӵ�������
				towers.pushBack(shit);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 220;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_96.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 96;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   if (time == 1)//��������Ϊ1
		{
			Button *shit;
			if (money >= 380)
				shit = Button::create("Themes\\Items\\Items02-hd\\upgrade_380.png");
			else shit = Button::create("Themes\\Items\\Items02-hd\\upgrade_-380.png");
			shit->setPosition(Vec2(-10, 110));
			Upselect->addChild(shit);
			shit->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 380)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* shit = Tower::create(SHIT, 2);
				shit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				shit->setPosition(Upselect->getPosition());
				shit->dzsp = Sprite::create(shit->dz->getCString());
				shit->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				shit->dzsp->setPosition(Vec2(shit->getPositionX(), shit->getPositionY() - 20));
				this->addChild(shit->dzsp, 1);
				this->addChild(shit, 2);
				Upselect->setVisible(false);
				// ����init����
				shit->onTowerInit();
				// ������ӵ�������
				towers.pushBack(shit);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 380;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_176.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 176;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   //��������Ϊ2
		{
			Sprite *bottle;
			bottle = Sprite::create("Themes\\Items\\Items02-hd\\upgrade_0_CN.png");
			bottle->setPosition(Vec2(-10, 110));
			Upselect->addChild(bottle);
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_304.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 304;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
	}
	//Button* 
	else if (tower->type == TowerType::FAN)
	{
		if (time == 0)  //������������Ϊ0
		{
			Button *fan;
			if (money >= 260)
				fan = Button::create("Themes\\Items\\Items02-hd\\upgrade_260.png");
			else fan = Button::create("Themes\\Items\\Items02-hd\\upgrade_-260.png");
			fan->setPosition(Vec2(-10, 110));
			Upselect->addChild(fan);
			fan->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 260)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* fan = Tower::create(FAN, 1);
				fan->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				fan->setPosition(Upselect->getPosition());
				fan->dzsp = Sprite::create(fan->dz->getCString());
				fan->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				fan->dzsp->setPosition(Vec2(fan->getPositionX(), fan->getPositionY() - 20));
				this->addChild(fan->dzsp, 1);
				this->addChild(fan, 2);
				Upselect->setVisible(false);
				// ����init����
				fan->onTowerInit();
				// ������ӵ�������
				towers.pushBack(fan);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 260;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_144.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 144;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   if (time == 1)//��������Ϊ1
		{
			Button *fan;
			if (money >= 380)
				fan = Button::create("Themes\\Items\\Items02-hd\\upgrade_380.png");
			else fan = Button::create("Themes\\Items\\Items02-hd\\upgrade_-380.png");
			fan->setPosition(Vec2(-10, 110));
			Upselect->addChild(fan);
			fan->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 380)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* fan = Tower::create(FAN, 2);
				fan->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				fan->setPosition(Upselect->getPosition());
				fan->dzsp = Sprite::create(fan->dz->getCString());
				fan->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				fan->dzsp->setPosition(Vec2(fan->getPositionX(), fan->getPositionY() - 20));
				this->addChild(fan->dzsp, 1);
				this->addChild(fan, 2);
				Upselect->setVisible(false);
				// ����init����
				fan->onTowerInit();
				// ������ӵ�������
				towers.pushBack(fan);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 380;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_224.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 432;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   //��������Ϊ2
		{
			Sprite *fan;
			fan = Sprite::create("Themes\\Items\\Items02-hd\\upgrade_0_CN.png");
			fan->setPosition(Vec2(-10, 110));
			Upselect->addChild(fan);
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_352.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 272;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
	}
	else if (tower->type == TowerType::STAR)
	{
		if (time == 0)  //������������Ϊ0
		{
			Button *star;
			if (money >= 260)
				star = Button::create("Themes\\Items\\Items02-hd\\upgrade_260.png");
			else star = Button::create("Themes\\Items\\Items02-hd\\upgrade_-260.png");
			star->setPosition(Vec2(-10, 110));
			Upselect->addChild(star);
			star->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 260)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* star = Tower::create(STAR, 1);
				star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				star->setPosition(Upselect->getPosition());
				star->dzsp = Sprite::create(star->dz->getCString());
				star->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				star->dzsp->setPosition(Vec2(star->getPositionX(), star->getPositionY() - 10));
				this->addChild(star->dzsp, 1);
				this->addChild(star, 2);
				Upselect->setVisible(false);
				// ����init����
				star->onTowerInit();
				// ������ӵ�������
				towers.pushBack(star);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 260;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_144.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 144;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   if (time == 1)//��������Ϊ1
		{
			Button *star;
			if (money >= 380)
				star = Button::create("Themes\\Items\\Items02-hd\\upgrade_380.png");
			else star = Button::create("Themes\\Items\\Items02-hd\\upgrade_-380.png");
			star->setPosition(Vec2(-10, 110));
			Upselect->addChild(star);
			star->addClickEventListener([this, tower](Ref*)
			{

				// �����Ҳ��������ܽ���
				if (money < 380)
				{
					Upselect->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				tower->dzsp->removeFromParent();
				Tower* star = Tower::create(STAR, 2);
				star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				star->setPosition(Upselect->getPosition());
				star->dzsp = Sprite::create(star->dz->getCString());
				star->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				star->dzsp->setPosition(Vec2(star->getPositionX(), star->getPositionY() - 10));
				this->addChild(star->dzsp, 1);
				this->addChild(star, 2);
				Upselect->setVisible(false);
				// ����init����
				star->onTowerInit();
				// ������ӵ�������
				towers.pushBack(star);
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money -= 380;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_224.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 432;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
		else   //��������Ϊ2
		{
			Sprite *star;
			star = Sprite::create("Themes\\Items\\Items02-hd\\upgrade_0_CN.png");
			star->setPosition(Vec2(-10, 110));
			Upselect->addChild(star);
			//ɾ����ť
			Button* deletetower = Button::create("Themes\\Items\\Items02-hd\\sell_352.png");
			deletetower->setPosition(Vec2(82, 110));
			Upselect->addChild(deletetower);
			deletetower->addClickEventListener([this, tower](Ref*)
			{
				Upselect->setVisible(false);
				tower->dzsp->removeFromParent();
				tower->removeFromParent();        // ͼ�㣺�ӳ����Ƴ�
				towers.eraseObject(tower);
				// �������Ľ��
				money += 272;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
		}
	}
}


// ��������ѡ�񹤾�
void GameScene::createBuildTool()
{
	// ����ѡ�񹤾�,��ʱ����
	select = Sprite::create("Themes\\Items\\Items02-hd\\select_01.png");
	select->setVisible(false);
	this->addChild(select);
	select->setLocalZOrder(2);// ����zOrder,ͼ�����ȼ�

	// ������ͼ�꣺�����Tomer�У�������µ��������ͣ����������
	// ������ͼ�꣺�����Tomer�У�������µ��������ͣ����������
	Button* bottle;
	Button* shit;
	Button* fan;
	Button* star;
	for (int i = 0; i < TowerSelect.size(); ++i)
	{
		
		switch (TowerSelect[i])
		{
		case 1:
			if (money >= 100)
				bottle = Button::create("Themes\\Towers\\TBottle-hd\\Bottle01.png");
			else  bottle = Button::create("Themes\\Towers\\TBottle-hd\\Bottle00.png");
			bottle->setPosition(Vec2(92 * i, 110));
			select->addChild(bottle);
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
				bottle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				bottle->setPosition(select->getPosition());
				bottle->dzsp = Sprite::create(bottle->dz->getCString());
				bottle->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				bottle->dzsp->setPosition(Vec2(bottle->getPositionX(), bottle->getPositionY() - 10));
				this->addChild(bottle->dzsp, 1);
				this->addChild(bottle,2);
				select->setVisible(false);
				// ����init����
				bottle->onTowerInit();
				// ������ӵ�������
				towers.pushBack(bottle);
				// �������Ľ��
				money -= 100;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			break;
		case 2:
			if (money >= 120)
				shit = Button::create("Themes\\Towers\\TShit-hd\\Shit01.png");
			else  shit = Button::create("Themes\\Towers\\TShit-hd\\Shit00.png");
			shit->setPosition(Vec2(92 * i, 110));
			select->addChild(shit);
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
				shit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				shit->setPosition(select->getPosition());
				shit->dzsp = Sprite::create(shit->dz->getCString());
				shit->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				shit->dzsp->setPosition(Vec2(shit->getPositionX(), shit->getPositionY() - 20));
				this->addChild(shit->dzsp, 1);
				this->addChild(shit, 2);
				select->setVisible(false);
				// ����init����
				shit->onTowerInit();
				//// ������ӵ�������
				towers.pushBack(shit);
				// �������Ľ��
				money -= 120;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			break;
		case 3:
			if (money >= 160)
				fan = Button::create("Themes\\Towers\\TFan-hd\\Fan01.png");
			else  fan = Button::create("Themes\\Towers\\TFan-hd\\Fan00.png");
			fan->setPosition(Vec2(92 * i, 110));
			select->addChild(fan);
			fan->addClickEventListener([this](Ref*)
			{
				// �����Ҳ��������ܽ���
				if (money < 160)
				{
					select->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				Tower* fan = Tower::create(FAN);
				fan->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				fan->setPosition(select->getPosition());
				fan->dzsp = Sprite::create(fan->dz->getCString());
				fan->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				fan->dzsp->setPosition(Vec2(fan->getPositionX(), fan->getPositionY() - 20));
				this->addChild(fan->dzsp, 1);
				this->addChild(fan, 2);
				select->setVisible(false);
				// ����init����
				fan->onTowerInit();
				//// ������ӵ�������
				towers.pushBack(fan);
				// �������Ľ��
				money -= 120;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			break;
		case 4:
			log("%d", TowerSelect[i]);
			if (money >= 160)
				star = Button::create("Themes\\Towers\\TStar-hd\\Star01.png");
			else  star = Button::create("Themes\\Towers\\TStar-hd\\Star00.png");
			star->setPosition(Vec2(92 * i, 110));
			select->addChild(star);
			star->addClickEventListener([this](Ref*)
			{
				// �����Ҳ��������ܽ���
				if (money < 160)
				{
					select->setVisible(false);
					return;
				}
				// ����Bottle��,������ѡ�񹤾�
				Tower* star = Tower::create(STAR);
				star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				star->setPosition(select->getPosition());
				star->dzsp = Sprite::create(star->dz->getCString());
				star->dzsp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				star->dzsp->setPosition(Vec2(star->getPositionX(), star->getPositionY()));
				this->addChild(star->dzsp, 1);
				this->addChild(star, 2);
				select->setVisible(false);
				// ����init����
				star->onTowerInit();
				//// ������ӵ�������
				towers.pushBack(star);
				// �������Ľ��
				money -= 120;
				// �޸Ľ���ı�
				char text[10];
				sprintf(text, "%d", money);
				moneyT->setString(text);
			});
			break;
		}
	}
	
	
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

		TowerAnim = __String::createWithFormat("Themes\\Towers\\TBottle-hd\\Bottle");
		break;
	case SHIT:
		TowerAnim = __String::createWithFormat("Themes\\Towers\\TShit-hd\\Shit");
		break;
	case FAN:
		TowerAnim = __String::createWithFormat("Themes\\Towers\\TFan-hd\\Fan");
		break;
	case STAR:
		TowerAnim = __String::createWithFormat("Themes\\Towers\\TStar-hd\\Star");
		break;
	}
	
	for (int i = 0; i < 4; ++i) {
		__String* str = __String::createWithFormat("%s%d%d.png", TowerAnim->getCString(),tower->Uptime+1, i%3 + 1);
		pAnimation->addSpriteFrameWithFile(str->getCString());
	}
	pAnimation->setLoops(1);
	pAnimation->setDelayPerUnit(0.1f);
	tower->runAction(Sequence::create(Animate::create(pAnimation), nullptr));

}
void GameScene::SetHitAnim(Vec2 Position, Bullet* bullet)
{
	//���ж���
	Sprite* hitsp = Sprite::create();
	this->addChild(hitsp);
	hitsp->setPosition(Position);
	Animation* pAnimation = Animation::create();
	__String* HitAnim;
	int animzhen = 0;
	switch (bullet->type)
	{
	case BOTTLE:
		HitAnim = __String::createWithFormat("Themes\\Towers\\TBottle-hd\\PBottle0");
		animzhen = 3;
		break;
	case SHIT:
		HitAnim = __String::createWithFormat("Themes\\Towers\\TShit-hd\\PShit0");
		animzhen = 3;
		break;
	case FAN:
		HitAnim = __String::createWithFormat("Themes\\Towers\\TFan-hd\\PFan0");
		animzhen = 3;
		break;
	case STAR:
		HitAnim = __String::createWithFormat("Themes\\Towers\\TStar-hd\\PStar-1");
		animzhen = 7;
		break;
	}

	for (int i = 1; i < animzhen; ++i) {
		__String* str = __String::createWithFormat("%s%d.png", HitAnim->getCString(), i);
		pAnimation->addSpriteFrameWithFile(str->getCString());
	}
	pAnimation->setLoops(1);
	pAnimation->setDelayPerUnit(0.1f);
	hitsp->runAction(Sequence::create(Animate::create(pAnimation), RemoveSelf::create(), nullptr));
	if (bullet->type == STAR)
	for (int i = 0; i < monster.size(); ++i)
	{
		Monster* Targetmonster = monster.at(i);
		float isBulletJianShe = bullet->getPosition().getDistance(Targetmonster->getPosition());
		if (isBulletJianShe > 100 && isBulletJianShe < 214)
		{
			// �����Ѫ
			Targetmonster->hp -= bullet->damage/2;
			// �������Ƿ�����
			if (Targetmonster->hp <= 0)
			{
				Targetmonster->hp = 0;
				// �����¾��������Ź�������֡����
				if (monsterselect == Targetmonster)
					isselect = false;
				Sprite* spBoom = Sprite::create("Map\\MonsterDead\\Dead_01.png");
				this->addChild(spBoom);
				// ����λ�ã������λ�ã�
				spBoom->setPosition(Vec2(Targetmonster->getPositionX(), Targetmonster->getPositionY() + 30.f));
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
		}
	}
}
