#include "Monster.h"
using namespace cocos2d;
using namespace std;
Monster::Monster(MonsterType type)
:type(type)
{
	// ���ݲ�ͬ���ͳ�ʼ��Ѫ��
	switch (type)
	{
	case fly_yellow:
		hp = 50;
		break;
	case fly_blue:
		hp = 100;
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
	char filename[50];
	// �������͵ĵ�����ͼƬ·��
	switch (type)
	{
	case fly_yellow:
		strcpy(filename, "Items/Monsters01-hd/fly_yellow01.png");
		break;
	case fly_blue:
		strcpy(filename, "Items/Monsters01-hd/fly_blue01.png");
		break;
	}

	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	// ��������
	Animation* ani = Animation::create();
	switch (type)
	{
	case fly_yellow:
		for (int i = 1; i <= 2; i++)
		{
			char file[50];
			sprintf(file, "Items/Monsters01-hd/fly_yellow0%d.png", i);
			ani->addSpriteFrameWithFile(file);
		}
		break;
	case fly_blue:
		for (int i = 1; i <= 2; i++)
		{
			char file[50];
			sprintf(file, "Items/Monsters01-hd/fly_blue0%d.png", i);
			ani->addSpriteFrameWithFile(file);
		}
		break;
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
