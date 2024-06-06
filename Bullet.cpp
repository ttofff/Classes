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
	if (type == TowerType::BOTTLE)
	{
		ret->damage = 20;
		ret->bulletlevel = 0;
	}
	if (type == TowerType::SHIT)
	{
		ret->damage = 10;
		ret->bulletlevel = 0;
	}
	if (type == TowerType::FAN)
	{
		ret->damage = 15;
		ret->bulletlevel = 0;
	}
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
Bullet* Bullet::create(TowerType type, int time)
{
	Bullet* ret = new Bullet(type);
	if (type == TowerType::BOTTLE)
	{
		ret->damage = 20*(time+1);
		ret->bulletlevel = time;
	}
	if (type == TowerType::SHIT)
	{
		ret->damage = 10*(time+1);
		ret->bulletlevel = time;
	}
	if (type == TowerType::FAN)
	{
		ret->damage = 10 * (time + 1);
		ret->bulletlevel = time;
	}

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
	__String* filename;
	// ���ݲ�ͬ�����ͳ�ʼ����ͬ�ӵ�ͼƬ
	switch (type) {
	case BOTTLE:
		filename=__String::createWithFormat("Themes\\Towers\\TBottle-hd\\PBottle%d1.png",bulletlevel+1);
		break;
	case SHIT:
		filename = __String::createWithFormat("Themes\\Towers\\TShit-hd\\PShit%d1.png", bulletlevel+1);
		break;
	case FAN:
		filename = __String::createWithFormat("Themes\\Towers\\TFan-hd\\PFan%d1.png", bulletlevel + 1);
	}
	
	if (!Sprite::initWithFile(filename->getCString()))
	{
		return false;
	}

	return true;
}

void Bullet::updateDirection()
{
	// ����Monster
	// �õ����������
	Vec2 targetPos;
	if (Lasttarget == Vec2::ZERO)
	{
		Lasttarget = target->getPosition();
		LastBulletPosition = getPosition();
	}
	if (type == TowerType::FAN)
	{
		// �õ��뵱ǰ�ӵ���������
		Vec2 offset = Lasttarget - LastBulletPosition;
		// �õ��ӵ��ƶ����򣨵�λ������
		dir = offset.getNormalized();
		// �����������Ϸ���֮��ļн�
		float radian = Vec2::angle(offset, Vec2(0, 1));// ����
		// ����ת�Ƕ�
		float angle = radian * 180 / PI;
		angle = offset.x >= 0 ? angle : -angle;
		// �����ӵ�����ת
		setRotation(angle);
		RotateBy* ro = RotateBy::create(0.6f, 30);
		Sequence *Ros = Sequence::create(ro, nullptr);
		this->runAction(Ros->clone());
		return;
	}
		else targetPos = target->getPosition();
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
	setPosition(getPosition() + dir * 1000 * dt);
}
