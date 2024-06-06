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
	ret->Uptime = 0;

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

Tower* Tower::create(TowerType type,int i)// 通过类型创建不同的塔
{
	Tower* ret = new Tower(type);
	ret->Uptime = i;
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
		if (Uptime == 0)
		{
			strcpy(filename, "Themes\\Towers\\TBottle-hd\\Bottle11.png");
		}
		else if (Uptime == 1)
		{
			strcpy(filename, "Themes\\Towers\\TBottle-hd\\Bottle21.png");
		}
		else
		{
			strcpy(filename, "Themes\\Towers\\TBottle-hd\\Bottle31.png");
		}
		dz = __String::create("Themes\\Towers\\TBottle-hd\\Bottle-11.png");
		IsRotator = true;
		range = 150;
		break;
	case SHIT:
		if (Uptime == 0)
		{
			strcpy(filename, "Themes\\Towers\\TShit-hd\\Shit11.png");
			dz = __String::create("Themes\\Towers\\TShit-hd\\Shit-11.png");
		}
		else if (Uptime == 1)
		{
			strcpy(filename, "Themes\\Towers\\TShit-hd\\Shit21.png");
			dz = __String::create("Themes\\Towers\\TShit-hd\\Shit-12.png");
		}
		else 
		{ 
			strcpy(filename, "Themes\\Towers\\TShit-hd\\Shit31.png");
			dz = __String::create("Themes\\Towers\\TShit-hd\\Shit-13.png");
		}
		IsRotator = false;
		range = 150;
		break;
	case FAN:
		if (Uptime == 0)
		{
			strcpy(filename, "Themes\\Towers\\TFan-hd\\Fan11.png");
			dz = __String::create("Themes\\Towers\\TFan-hd\\Fan-11.png");
		}
		else if (Uptime == 1)
		{
			strcpy(filename, "Themes\\Towers\\TFan-hd\\Fan21.png");
			dz = __String::create("Themes\\Towers\\TFan-hd\\Fan-12.png");
		}
		else
		{
			strcpy(filename, "Themes\\Towers\\TFan-hd\\Fan31.png");
			dz = __String::create("Themes\\Towers\\TFan-hd\\Fan-13.png");
		}
		IsRotator = false;
		range = 200;
		break;
	case STAR:
		if (Uptime == 0)
		{
			strcpy(filename, "Themes\\Towers\\TStar-hd\\Star11.png");
			dz = __String::create("Themes\\Towers\\TStar-hd\\Star-11.png");
		}
		else if (Uptime == 1)
		{
			strcpy(filename, "Themes\\Towers\\TStar-hd\\Star21.png");
			dz = __String::create("Themes\\Towers\\TStar-hd\\Star-12.png");
		}
		else
		{
			strcpy(filename, "Themes\\Towers\\TStar-hd\\Star31.png");
			dz = __String::create("Themes\\Towers\\TStar-hd\\Star-13.png");
		}
		IsRotator = false;
		range = 200;
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
	range = range * (Uptime + 1);
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
	Vec2 targetPos = Vec2(monster->getPositionX(), monster->getPositionY());
	Vec2 offset = targetPos - getPosition();
	float radian = Vec2::angle(offset, Vec2(0, 1));
	float angle = radian * 180 / PI;
	angle = offset.x >= 0 ? angle : -angle;
	setRotation(angle);
}

