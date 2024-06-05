#ifndef Bullet_h
#define Bullet_h

#include "cocos2d.h"
#include "Tower.h"
class Monster;

class Bullet : public cocos2d::Sprite
{
public:
	Bullet(TowerType type);
	static Bullet* create(TowerType type);
	static Bullet* create(TowerType type,int time);
	bool init() override;
	void onBulletInit(Monster* target);			// 子弹初始化
	void onBulletUpdate(float dt);				// 子弹移动
	void updateDirection();						// 转向
public:
	Monster* target;							// 子弹攻击目标
	TowerType type;								// 子弹的所属塔类型
	int damage;									//子弹攻击力
	int bulletlevel;
private:
	cocos2d::Vec2 dir;							// 子弹移动方向
};

#endif
