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
	// 根据不同塔类型初始化不同子弹图片
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
	// 朝向Monster
	// 得到怪物的坐标
	Vec2 targetPos = target->getPosition();
	// 得到与当前子弹的向量差
	Vec2 offset = targetPos - getPosition();
	// 得到子弹移动方向（单位向量）
	dir = offset.getNormalized();
	// 求向量差与上方向之间的夹角
	float radian = Vec2::angle(offset, Vec2(0, 1));// 弧度
	// 弧度转角度
	float angle = radian * 180 / PI;
	angle = offset.x >= 0 ? angle : -angle;
	// 设置子弹的旋转
	setRotation(angle);
}

void Bullet::onBulletInit(Monster* target)// 子弹初始化
{
	// 初始化攻击目标
	this->target = target;
	// 设置旋转方向
	updateDirection();
}

void Bullet::onBulletUpdate(float dt)// 子弹移动
{
	// 设置旋转方向
	updateDirection();
	// 移动增量 = 方向 * 速度 * 时间
	setPosition(getPosition() + dir * 800 * dt);
}
