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


//出现怪物
void GameScene::update(float dt)
{
	static float waittime = 1.0f;
	waittime = waittime - dt;
	if (waittime <= 0.f){
		waittime = 1.0f;
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music\\Items\\GO.mp3"); //播放音效
		Monster* newmonster = Monster::create((MonsterType)((rand() % 8) + 1));		//创建新的怪物
		newmonster->onMonsterInit(tiledMap->wayPoints);
		monster.pushBack(newmonster);				//加入怪物容器中
		this->addChild(monster.back());
	}

		for (int i = 0; i < monster.size(); i++)
		{
			Monster* pm = monster.at(i);
			if (!pm->onMonsterUpdate(dt)){					//怪物吃到萝卜
				Sprite* spBoom = Sprite::create();			//怪物消失动画
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
				//判断是否死亡
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
		// 遍历所有的塔：没有塔的时候，就不会发射子弹
		for (Tower* tower : towers)
		{
			// 判断射击的时间是否满足条件
			if (tower->onTowerUpdate(dt))
			{
				for (Monster* monster : monster)
				{
					// 如果在范围之内，产生子弹
					if (tower->shoot(monster))
					{
						SetTowerAnim(tower);
						// 创建子弹
						Bullet* bullet = Bullet::create(tower->type);
						// 设置子弹位置与 当前 塔坐标相同
						bullet->setPosition(tower->getPosition());
						// 初始化子弹
						bullet->onBulletInit(monster);
						// 将子弹添加到层上
						this->addChild(bullet);
						// 将子弹添加到子弹链表中
						bullets.pushBack(bullet);
						
						break;    // 很重要
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
				bullets.eraseObject(bullet); // 内存：从容器移除
				bullet->removeFromParent();        // 图层：从场景移除
				continue;
			}
			bool isCrash = Targetmonster->getBoundingBox().containsPoint(bullet->getPosition());
			if (isCrash)
			{
				// 怪物随机掉血
				Targetmonster->hp -= Damage;
				Targetmonster->SetSpeed(SlowSpeed);
				// 检测怪物是否被消灭
				if (Targetmonster->hp <= 0)
				{
					Targetmonster->hp = 0;
					// 创建新精灵来播放怪物死亡帧动画
					Sprite* spBoom = Sprite::create("Map\\MonsterDead\\Dead_01.png");
					this->addChild(spBoom);
					// 设置位置（怪物的位置）
					spBoom->setPosition(Vec2(Targetmonster->getPositionX(), Targetmonster->getPositionY()+20.f));
					Animation* monsterdead = Animation::create();
					for (int i = 1; i < 15; ++i) {
						__String* str = __String::createWithFormat("Map\\MonsterDead\\Dead_%02d.png", i);
						monsterdead->addSpriteFrameWithFile(str->getCString());
					}
					monsterdead->setDelayPerUnit(0.1f);
					monsterdead->setLoops(1);
					Animate* animate = Animate::create(monsterdead);
					// 移除动作
					RemoveSelf* removeSelf = RemoveSelf::create();
					// 序列动作
					Sequence* seq = Sequence::create(animate, removeSelf, nullptr);
					spBoom->runAction(seq);
					// 移除怪物
					monster.eraseObject(Targetmonster);
					this->removeChild(Targetmonster);
					// 怪物死亡数量+1(后续可以添加)

					// 打怪随机获得金币
					money += rand() % 21 + 10;// 80 - 180
					// 修改金币文本
					char text[10];
					sprintf(text, "%d", money);
					moneyT->setString(text);
				}


				// 将子弹容器中和场景中移除
				bullets.eraseObject(bullet);
				bullet->removeFromParent();
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			Bullet* bullet = bullets.at(i);
			bool isDie = true;    // 当前子弹 的 攻击目标 的 存活状态
			// 遍历怪物链表，如果没有找到该子弹的攻击目标，表示怪物已经死亡
			for (Monster* monster : monster)
			{
				if (monster == bullet->target)
				{
					isDie = false;
					break;
				}
			}
			// 如果攻击目标死亡,则将子弹从容器中和层上移除
			if (isDie)
			{
				bullets.eraseObject(bullet); // 内存：从容器移除
				bullet->removeFromParent();        // 图层：从场景移除
				continue;
			}
			bullet->onBulletUpdate(dt);// 控制子弹移动
		}
}


//萝卜死亡
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


	//暂停菜单
	Gamepause* gamepause = Gamepause::create();
	this->addChild(gamepause, 5);
	gamepause->setVisible(false);

	//失败界面
	gameEnd = GameEnd::create();
	this->addChild(gameEnd, 5);
	gameEnd->setVisible(false);

	// 生成关卡图
	__String *str;
	if (AdventureFirstScene::bigcheck==1)
		str = __String::createWithFormat("Map\\FirstKind\\Environment\\Level%02d\\Level.tmx",index);
	else if (AdventureFirstScene::bigcheck==2)
		str = __String::createWithFormat("Map\\SecondKind\\Environment\\Level%02d\\Level.tmx", index);
	else str = __String::createWithFormat("Map\\ThirdKind\\Environment\\Level%02d\\Level.tmx", index);
	tiledMap = GameMap::create(str->getCString());
	tiledMap->setPosition(Vec2::ZERO);
	this->addChild(tiledMap, 0);
	
	

	


	//怪物
	tiledMap->getWayPoints("PATH"); //获取怪物移动路径
	tiledMap->getTowerArea("OBJ");		//获取炮塔生成区域

	//萝卜
	ca = Sprite::create("wei.jpg");
	
	ca->setPosition(tiledMap->wayPoints.back());
	this->addChild(ca, 2);
	ca->getPosition();

	scheduleUpdate();


	// 菜单栏背景
	Sprite* menuBG = Sprite::create("Themes\\Items\\touming-hd\\MenuBG.png");
	menuBG->setAnchorPoint(Vec2(0.5, 1));
	menuBG->setPosition(Vec2(480, 640));
	this->addChild(menuBG, 1);

	// 金币数量
	__String* s = __String::createWithFormat("%d", money);
	moneyT = TextAtlas::create(s->getCString(), "Themes\\Items\\numwhite-hd.png", 20, 40, ".");
	moneyT->setPosition(Vec2(120, 610));
	this->addChild(moneyT, 2);

	// 显示当前波数和总波数精灵
	Sprite* menuCenter = Sprite::create("Themes\\Items\\Items02-hd\\MenuCenter_01_CN.png");
	menuCenter->setPosition(Vec2(463, 45));
	menuBG->addChild(menuCenter, 1);

	//当前波数
	__String* SWaveNumber = __String::createWithFormat("%02d", Wave_Number);
	TextAtlas*curWaveText = TextAtlas::create(SWaveNumber->getCString(), "Themes\\Items\\numyellow-hd.png", 44, 40, ".");
	curWaveText->setPosition(Vec2(390, 45));
	menuBG->addChild(curWaveText, 2);

	//总波数
	TextAtlas*totalWaveText = TextAtlas::create("15", "Themes\\Items\\numwhite-hd.png", 20, 40, ".");
	totalWaveText->setPosition(Vec2(480, 45));
	menuBG->addChild(totalWaveText, 2);

	// 全局速度变量
	CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
	pScheduler->setTimeScale(1.f);

	// 1倍速按钮
	Button* btn_speed = Button::create("Themes\\Items\\touming-hd\\speed11.png", "Themes\\Items\\touming-hd\\speed12.png");
	btn_speed->setPosition(Vec2(725, 605));
	this->addChild(btn_speed, 2);

	// 2倍速按钮
	Button* btn_speed_two = Button::create("Themes\\Items\\touming-hd\\speed21.png", "Themes\\Items\\touming-hd\\speed22.png");
	btn_speed_two->setPosition(Vec2(725, 605));
	this->addChild(btn_speed_two, 2);
	btn_speed_two->setVisible(false);

	// 倍速按钮点击事件
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

	//暂停中
	Sprite* btn_stop = Sprite::create("Themes\\Items\\Items02-hd\\MenuCenter_02_CN.png");
	btn_stop->setPosition(Vec2(480, 320));
	btn_stop->setVisible(false);
	this->addChild(btn_stop, 2);

	// 暂停按钮
	Button* btn_pause = Button::create("Themes\\Items\\touming-hd\\pause11.png", "Themes\\Items\\touming-hd\\pause12.png");
	btn_pause->setPosition(Vec2(825, 605));
	btn_pause->setVisible(false);
	this->addChild(btn_pause, 2);

	// 开始按钮
	Button* btn_go = Button::create("Themes\\Items\\touming-hd\\pause01.png", "Themes\\Items\\touming-hd\\pause02.png");
	btn_go->setPosition(Vec2(825, 605));
	btn_go->setVisible(true);
	this->addChild(btn_go, 2);


	// 菜单按钮
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

	// 暂停、开始点击事件
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

	createBuildTool();		//创建建塔工具

	EventListenerTouchOneByOne* eventListenerTouchOneByOne = EventListenerTouchOneByOne::create();
	eventListenerTouchOneByOne->onTouchBegan = [this](Touch* touch,Event *event)
	{
		//建塔工具是否可见
		if (select->isVisible())
		{
			select->setVisible(false);
			return true;
		}
		//获取当前点击的路径点
		Vec2 touchPoint = touch->getLocation();
		float x = (int)touchPoint.x / 80 * 80 + 40;
		float y = (int)touchPoint.y / 80 * 80 + 40;
		//是否有塔
		for (Tower* tower : towers)
		{
			if (fabs(tower->getPositionX() - x) < 0.000001 &&
				fabs(tower->getPositionY() - y) < 0.000001)
			{
				return true;
			}
		}
		//书否再=在建塔区域内
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

	
	
	// 萝卜图像
	
	
	// 萝卜抖动动画
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




// 创建建塔选择工具
void GameScene::createBuildTool()
{
	// 创建选择工具,暂时隐藏
	select = Sprite::create("Themes\\Items\\Items02-hd\\select_01.png");
	select->setVisible(false);
	this->addChild(select);
	select->setLocalZOrder(2);// 设置zOrder

	// 创建塔图标：如果在Tomer中，添加了新的塔的类型，在这里添加
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

	// 点击不同的塔图标，创建不同的塔
	bottle->addClickEventListener([this](Ref*)
	{
		// 如果金币不够，则不能建塔
		if (money < 100)
		{
			select->setVisible(false);
			return;
		}
		// 创建Bottle塔,并隐藏选择工具
		Tower* bottle = Tower::create(BOTTLE);
		bottle->setPosition(select->getPosition());
		this->addChild(bottle);
		select->setVisible(false);
		// 调用init方法
		bottle->onTowerInit();
		// 将塔添加到链表中
		towers.push_back(bottle);
		// 建塔消耗金币
		money -= 100;
		// 修改金币文本
		char text[10];
		sprintf(text, "%d", money);
		moneyT->setString(text);
	});

	shit->addClickEventListener([this](Ref*)
	{
		// 如果金币不够，则不能建塔
		if (money < 120)
		{
			select->setVisible(false);
			return;
		}
		// 创建Bottle塔,并隐藏选择工具
		Tower* shit = Tower::create(SHIT);
		shit->setPosition(select->getPosition());
		this->addChild(shit);
		select->setVisible(false);
		// 调用init方法
		shit->onTowerInit();
		//// 将塔添加到链表中
		towers.push_back(shit);
		// 建塔消耗金币
		money -= 120;
		// 修改金币文本
		char text[10];
		sprintf(text, "%d", money);
		moneyT->setString(text);
	});
}
void GameScene::SetTowerAnim(Tower* tower)
{
	//射击动画
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