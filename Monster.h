#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"
#include <vector>
// 怪物类型
enum MonsterType
{
	Monster1=1,
	Monster2,
	Monster3,
	Monster4,
	Monster5,
	Monster6,
	Monster7,
	Monster8
};

// 怪物类
class Monster : public cocos2d::Sprite
{
public:
	Monster(MonsterType type);
	static Monster* create(MonsterType type, int kind);
	bool init() override;
	void onMonsterInit(std::vector<cocos2d::Vec2> wayPoints);// 怪物初始化
	bool onMonsterUpdate(float dt);// 怪物更新（移动）
	std::vector<cocos2d::Vec2> wayPoints; //移动路径点
private:
	float speed = 150.f;
	int curIndex;// 目前所在的路径点下标
	MonsterType type;
public:
	int monsterKind; // 怪物类型
	int hp;// 怪物血量
	float GetSpeed()const { return speed; }
	void SetSpeed(float s) { speed = s; }
};

#endif
