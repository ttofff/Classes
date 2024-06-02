#include "Monster.h"
using namespace cocos2d;
using namespace std;
Monster::Monster(MonsterType type)
:type(type)
{
	// ���ݲ�ͬ���ͳ�ʼ��Ѫ��
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

Monster* Monster::create(MonsterType type)
{
	Monster* ret = new Monster(type);
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
	// �������͵ĵ�����ͼƬ·��
	
	__String* s =__String::createWithFormat("Map\\FirstKind\\FirstKind\\Monster\\%d\\1\\1.jpg",type);
	

	if (!Sprite::initWithFile(s->getCString()))
	{
		return false;
	}

	// ��������
	Animation* ani = Animation::create();

	for (int i = 1; i <= 4; i++)
	{
		char file[100];
		sprintf(file, "Map\\FirstKind\\FirstKind\\Monster\\%d\\1\\%d.png",(int)type, i);
		ani->addSpriteFrameWithFile(file);
	}
		
	

	ani->setLoops(-1);
	ani->setDelayPerUnit(0.3);
	Animate* animate = Animate::create(ani);
	runAction(animate);

	// ����ê��Ϊ����
	setAnchorPoint(Vec2(0.5, 0));
	return true;
}

void Monster::onMonsterInit(vector<Vec2> wayPoints)// �����ʼ��
{
	// ��ʼ��·��
	this->wayPoints = wayPoints;
	curIndex = 0;
	// ���ù�����·����ĵ�һ��λ��
	setPosition(wayPoints.front());
}

bool Monster::onMonsterUpdate(float dt)// ������£��ƶ���
{
	// ���ƹ�����������֮���ƶ�
	// �������Ϊfalse,���ʾ�������һ����
	if (curIndex >= wayPoints.size())
	{
		return false;
	}
	// ��ȡ��ǰ���������
	Vec2 pos = getPosition();
	// �õ���ǰ�ƶ��ľ���
	float moveDistance = dt * 150;// �ٶȼ���Ϊ100
	// ��ȡ��ǰλ����Ŀ���֮��ľ���
	float maxDistance = pos.distance(wayPoints[curIndex]);
	// ����ƶ��ľ�����������룬��ֱ�ӷ���·������
	if (moveDistance > maxDistance)
	{
		setPosition(wayPoints[curIndex]);
		curIndex++;
		return true;
	}
	// ��ȡ��ǰ���򣨵�λ������
	Vec2 dir = (wayPoints[curIndex] - wayPoints[curIndex - 1]).getNormalized();
	// �õ���ǰ�ƶ�������������*����
	Vec2 delta = dir * moveDistance;
	setPosition(pos + delta);
	return true;
}
