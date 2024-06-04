#include "Tower.h"
#include "Monster.h"
using namespace cocos2d;
using namespace cocos2d::ui;
#define PI 3.14159

Tower::Tower(TowerType type)
	:type(type)
{

}

Tower* Tower::create(TowerType type)// 通过类型创建不同的塔
{
	Tower* ret = new Tower(type);
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

bool Tower::init()
{
	char filename[50];
	// 根据不同塔类型初始化不同图片
	switch (type) {
	case BOTTLE:
		strcpy(filename, "Themes\\Towers\\TBottle-hd\\Bottle11.png");
		IsRotator = true;
		break;
	case SHIT:
		strcpy(filename, "Themes\\Towers\\TShit-hd\\Shit11.png");
		IsRotator = false;
		break;
	}
	// 初始化
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	return true;
}

void Tower::onTowerInit()// 塔初始化
{
	range = 150;
	shootDeltaTime = 0;
}

bool Tower::onTowerUpdate(float dt)// 塔更新
{
	// 间隔时间递减，如果时间<=0,返回true
	shootDeltaTime -= dt;
	return shootDeltaTime <= 0;
}

// 射击:判断怪物是否在范围内
bool Tower::shoot(Monster* monster)
{
	// 得到怪物的坐标
	Vec2 targetPos = monster->getPosition();
	// 得到与当前塔的向量差
	Vec2 offset = getPosition() - targetPos;
	// 求offset的长度是否在范围之内
	float dis = offset.length();
	bool result = dis <= range;
	// 如果在范围之内
	if (result)
	{
		// 重新恢复间隔时间
		shootDeltaTime = 0.5;
		updateDirection(monster);
		
	}
	return result;
}

void Tower::updateDirection(Monster* monster)
{
	if (!IsRotator) return;
	Vec2 targetPos = Vec2(monster->getPositionX() + 40, monster->getPositionY() + 40);
	Vec2 offset = targetPos - getPosition();
	float radian = Vec2::angle(offset, Vec2(0, 1));
	float angle = radian * 180 / PI;
	angle = offset.x >= 0 ? angle : -angle;
	setRotation(angle);
}

