#include "Bullet.h"
#include "Monster.h"
using  namespace cocos2d;

#define PI 3.1415926

Bullet::Bullet(TowerType type)
	:type(type)
{

}

Bullet* Bullet::create(TowerType type)
{
	Bullet* ret = new Bullet(type);
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

bool Bullet::init()
{
	char filename[50];
	// ���ݲ�ͬ�����ͳ�ʼ����ͬ�ӵ�ͼƬ
	switch (type) {
	case BOTTLE:
		strcpy(filename, "Themes\\Towers\\TBottle-hd\\PBottle11.png");
		break;
	case SHIT:
		strcpy(filename, "Themes\\Towers\\TShit-hd\\PShit11.png");
		break;
	}

	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	return true;
}

void Bullet::updateDirection()
{
	// ����Monster
	// �õ����������
	Vec2 targetPos = target->getPosition();
	// �õ��뵱ǰ�ӵ���������
	Vec2 offset = targetPos - getPosition();
	// �õ��ӵ��ƶ����򣨵�λ������
	dir = offset.getNormalized();
	// �����������Ϸ���֮��ļн�
	float radian = Vec2::angle(offset, Vec2(0, 1));// ����
	// ����ת�Ƕ�
	float angle = radian * 180 / PI;
	angle = offset.x >= 0 ? angle : -angle;
	// �����ӵ�����ת
	setRotation(angle);
}

void Bullet::onBulletInit(Monster* target)// �ӵ���ʼ��
{
	// ��ʼ������Ŀ��
	this->target = target;
	// ������ת����
	updateDirection();
}

void Bullet::onBulletUpdate(float dt)// �ӵ��ƶ�
{
	// ������ת����
	updateDirection();
	// �ƶ����� = ���� * �ٶ� * ʱ��
	setPosition(getPosition() + dir * 800 * dt);
}
