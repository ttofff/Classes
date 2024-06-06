#include "Monster.h"
using namespace cocos2d;
using namespace std;
Monster::Monster(MonsterType type)
:type(type)
{
	// 根据不同类型初始化血量
	switch (type)
	{
	case Monster1:
		hp = 50;
		break;
	case Monster2:
		hp = 100;
		break;
	case Monster3:
		hp = 50;
		break;
	case Monster4:
		hp = 50;
		break;
	case Monster5:
		hp = 50;
		break;
	case Monster6:
		hp = 50;
		break;
	case Monster7:
		hp = 50;
		break;
	case Monster8:
		hp = 50;
		break;
	}
}

Monster* Monster::create(MonsterType type, int kind)
{
	Monster* ret = new Monster(type);
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

bool Monster::init()
{
	__String* s;

	// 创建动画
	Animation* ani = Animation::create();
	// 根据类型的到怪物图片路径
	switch (monsterKind)
	{
	case 1:
		s = __String::createWithFormat("Map\\FirstKind\\Monster\\%d\\1\\1.png", type);

		if (!Sprite::initWithFile(s->getCString()))
		{
			return false;
		}

		for (int i = 1; i <= 4; i++)
		{
			char file[100];
			sprintf(file, "Map\\FirstKind\\Monster\\%d\\1\\%d.png",(int)type, i);
			ani->addSpriteFrameWithFile(file);
		}
		break;
	case 2:
		s = __String::createWithFormat("Map\\SecondKind\\Monster\\%d\\1.png", type);

		if (!Sprite::initWithFile(s->getCString()))
		{
			return false;
		}

		for (int i = 1; i <= 6; i++)
		{
			char file[100];
			sprintf(file, "Map\\SecondKind\\Monster\\%d\\%d.png", (int)type, i);
			ani->addSpriteFrameWithFile(file);
		}
		break;
	case 3:
		s = __String::createWithFormat("Map\\ThirdKind\\Monster\\%d\\1.png", type);

		if (!Sprite::initWithFile(s->getCString()))
		{
			return false;
		}

		for (int i = 1; i <= 4; i++)
		{
			char file[100];
			sprintf(file, "Map\\ThirdKind\\Monster\\%d\\%d.png", (int)type, i);
			ani->addSpriteFrameWithFile(file);
		}
		break;
	default:
		break;
	}
	
	ani->setLoops(-1);
	ani->setDelayPerUnit(0.3);
	Animate* animate = Animate::create(ani);
	runAction(animate);

	// 设置锚点为中下
	setAnchorPoint(Vec2(0.5, 0));
	return true;
}

void Monster::onMonsterInit(vector<Vec2> wayPoints)// 怪物初始化
{
	// 初始化路径
	this->wayPoints = wayPoints;
	curIndex = 0;
	// 设置怪物在路径点的第一个位置
	setPosition(wayPoints.front());
}

bool Monster::onMonsterUpdate(float dt)// 怪物更新（移动）
{
	// 控制怪物在两个点之间移动
	// 如果返回为false,则表示到达最后一个点
	if (curIndex >= wayPoints.size())
	{
		return false;
	}
	// 获取当前怪物的坐标
	Vec2 pos = getPosition();
	// 得到当前移动的距离
	float moveDistance = dt * speed;// 速度假设为100
	// 获取当前位置与目标点之间的距离
	float maxDistance = pos.distance(wayPoints[curIndex]);
	// 如果移动的距离大于最大距离，则直接放在路径点上
	if (moveDistance > maxDistance)
	{
		setPosition(wayPoints[curIndex]);
		curIndex++;
		return true;
	}
	// 获取当前方向（单位向量）
	Vec2 dir = (wayPoints[curIndex] - wayPoints[curIndex - 1]).getNormalized();
	//设置怪物转向
	if (dir.x >0)
		this->setRotationY(0);
	else if(dir.x<0) this->setRotationY(180.f);
	// 得到当前移动的向量：方向*距离
	Vec2 delta = dir * moveDistance;
	setPosition(pos + delta);
	return true;
}
